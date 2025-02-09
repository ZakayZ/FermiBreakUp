//
// Created by Artem Novikov on 21.02.2023.
//

#include <algorithm>
#include <sstream>

#include "Splitter.h"
#include "util/DataTypes.h"
#include <CLHEP/Units/PhysicalConstants.h>

#include "fragment_pool/fragments/Fragment.h"
#include "phase_decay/FermiPhaseSpaceDecay.h"
#include "util/Logger.h"
#include "util/Particle.h"
#include "util/Randomizer.h"

#include "FermiBreakUp.h"

using namespace fbu;

namespace {
  constexpr char SPACES_OFFSET[] = "   ";

  FermiStr LogProducts(const std::vector<Particle>& particles) {
    std::ostringstream out;

    out << "[\n";
    for (const auto& particle: particles) {
      out << SPACES_OFFSET << particle << ";\n";
    }
    out << "]";

    return std::move(out).str();
  }

  const LorentzVector ChangeFrameOfReference(const LorentzVector& vec, const Vector3& boost) {
    auto copy = vec;
    copy.boost(boost);
    return copy;
  }

  std::vector<Particle> SplitToParticles(const Particle& sourceParticle, const FragmentVector& split) {
    FERMI_LOG_TRACE("Converting split to particles");

    std::vector<FermiFloat> splitMasses(split.size());
    std::transform(
      split.begin(), split.end(),
      splitMasses.begin(),
      std::mem_fn(&Fragment::GetTotalEnergy));

    FermiPhaseSpaceDecay phaseSampler;
    std::vector<LorentzVector> particlesMomentum;
    try {
      particlesMomentum = phaseSampler.CalculateDecay(sourceParticle.GetMomentum(), splitMasses);
    } catch (std::exception& e) {
      FERMI_LOG_ERROR(e.what() 
        << " with split weight: "
        << Splitter::DecayWeight(split, sourceParticle.GetAtomicMass(), sourceParticle.GetMomentum().m()));
      return {sourceParticle};
    }

    // Go back to the Lab Frame
    std::vector<Particle> particleSplit;
    particleSplit.reserve(2 * split.size());
    const auto boostVector = sourceParticle.GetMomentum().boostVector();
    for (size_t fragmentIdx = 0; fragmentIdx < split.size(); ++fragmentIdx) {
      const auto fragmentMomentum = ChangeFrameOfReference(particlesMomentum[fragmentIdx], boostVector);
      split[fragmentIdx]->AppendDecayFragments(fragmentMomentum, particleSplit);
    }

    FERMI_LOG_DEBUG("Break up products: " << LogProducts(particleSplit));
    return particleSplit;
  }

  FermiStr LogSplit(const FragmentVector& split) {
    std::ostringstream out;

    out << "[\n";
    for (const auto fragmentPtr: split) {
      out << SPACES_OFFSET << *fragmentPtr << ";\n";
    }
    out << "]";

    return std::move(out).str();
  }
} // namespace

FermiBreakUp::FermiBreakUp(std::unique_ptr<SplitCache>&& cache)
  : cache_(std::move(cache))
{
}

std::vector<Particle> FermiBreakUp::SelectSplit(const Particle& particle, const FragmentSplits& splits) const {
  FERMI_LOG_TRACE("Selecting Split for " << particle << " from " << splits.size() << " splits");
  if (splits.empty()) {
    FERMI_LOG_DEBUG("No splits found");
    return {particle};
  }

  // get phase space weights for every split
  // we can't cache them, because calculations is probabilistic
  weights_.resize(splits.size());
  std::transform(
    splits.begin(), splits.end(), 
    weights_.begin(),
    [atomicMass=particle.GetAtomicMass(), totalEnergy=particle.GetMomentum().m()](const auto& split) {
      return Splitter::DecayWeight(split, atomicMass, totalEnergy);
    });

  if (std::all_of(weights_.begin(), weights_.end(), [](auto weight) { return weight == 0.; })) {
    FERMI_LOG_WARN("Every split has zero weight");
    return {particle};
  }

  const auto& chosenSplit = splits[Randomizer::SampleDistribution(weights_)];
  FERMI_LOG_DEBUG("From " << splits.size() << " splits chosen split: " << LogSplit(chosenSplit));

  return SplitToParticles(particle, chosenSplit);
}

std::vector<Particle> FermiBreakUp::BreakItUp(const Particle& particle) const {
  FERMI_LOG_TRACE("Breaking up particle: " << particle);

  if (particle.GetExcitationEnergy() < 0.) {
    FERMI_LOG_DEBUG("Particle is stable with excitation energy = " << particle.GetExcitationEnergy());
    return {particle};
  }

  if (cache_) {
    auto splitsPtr = cache_->Get(particle.GetNucleiData());
    if (splitsPtr == nullptr) {
      FERMI_LOG_DEBUG("Particle is stable with excitation energy = " << particle.GetExcitationEnergy() / CLHEP::MeV << " MeV");
      auto splits = Splitter::GenerateSplits(particle.GetNucleiData());
      splitsPtr = cache_->Insert(particle.GetNucleiData(), std::move(splits));
    } else {
      FERMI_LOG_DEBUG("Splits taken from cache");
    }

    return SelectSplit(particle, *splitsPtr);
  } else {
    splits_.clear();
    Splitter::GenerateSplits(particle.GetNucleiData(), splits_);
    return SelectSplit(particle, splits_);
  }
}
