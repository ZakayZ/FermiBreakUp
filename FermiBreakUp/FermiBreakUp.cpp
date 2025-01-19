//
// Created by Artem Novikov on 21.02.2023.
//

#include <algorithm>
#include <sstream>

#include "Split.h"
#include "util/DataTypes.h"
#include <CLHEP/Units/PhysicalConstants.h>

#include "fragment_pool/fragments/Fragment.h"
#include "phase_decay/FermiPhaseSpaceDecay.h"
#include "util/Logger.h"
#include "util/Particle.h"
#include "util/Randomizer.h"

#include "FermiBreakUp.h"

using namespace fermi;

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

  std::vector<Particle> SplitToParticle(const Particle& sourceParticle, const FragmentVector& split) {
    LOG_TRACE("Converting split to particles");

    std::vector<Particle> particleSplit;
    particleSplit.reserve(2 * split.size());

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
      LOG_ERROR(e.what() << " with split weight: " << DecayWeight(split, sourceParticle.GetAtomicMass(), sourceParticle.GetMomentum().m()));
      return {sourceParticle};
    }

    // Go back to the Lab Frame
    const auto boostVector = sourceParticle.GetMomentum().boostVector();
    for (size_t fragmentIdx = 0; fragmentIdx < split.size(); ++fragmentIdx) {
      const auto fragmentMomentum = ChangeFrameOfReference(particlesMomentum[fragmentIdx], boostVector);
      split[fragmentIdx]->AppendDecayFragments(fragmentMomentum, particleSplit);
    }

    LOG_DEBUG("Break up products: " << LogProducts(particleSplit));
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

  std::vector<Particle> SelectSplit(const Particle& particle, const FragmentSplits& splits) {
    LOG_TRACE("Selecting Split for " << particle << " from " << splits.size() << " splits");
    if (splits.empty()) {
      LOG_DEBUG("No splits found");
      return {particle};
    }

    // get phase space weights for every split
    std::vector<FermiFloat> weights(splits.size());
    std::transform(
      splits.begin(), splits.end(), 
      weights.begin(),
      [atomicMass=particle.GetAtomicMass(), totalEnergy=particle.GetMomentum().m()](const auto& split) {
        return DecayWeight(split, atomicMass, totalEnergy);
      });

    if (std::all_of(weights.begin(), weights.end(), [](auto weight) { return weight == 0.; })) {
      LOG_WARN("Every split has zero weight");
      return {particle};
    }

    const auto& chosenSplit = splits[Randomizer::SampleDistribution(weights)];
    LOG_DEBUG("From " << splits.size() << " splits chosen split: " << LogSplit(chosenSplit));

    return SplitToParticle(particle, chosenSplit);
  }
} // namespace

FermiBreakUp::FermiBreakUp(std::unique_ptr<SplitCache>&& cache)
  : cache_(std::move(cache))
{
}

std::vector<Particle> FermiBreakUp::BreakItUp(const Particle& particle) const {
  LOG_TRACE("Breaking up particle: " << particle);

  if (particle.GetExcitationEnergy() < 0.) {
    LOG_DEBUG("Particle is stable with excitation energy = " << particle.GetExcitationEnergy());
    return {particle};
  }

  if (cache_) {
    auto splitsPtr = cache_->Get(particle.GetNucleiData());
    if (splitsPtr == nullptr) {
      LOG_DEBUG("Particle is stable with excitation energy = " << particle.GetExcitationEnergy() / CLHEP::MeV << " MeV");
      auto splits = GenerateSplits(particle.GetNucleiData());
      splitsPtr = cache_->Insert(particle.GetNucleiData(), std::move(splits));

      ASSERT_MSG(splitsPtr != nullptr, "");
    } else {
      LOG_DEBUG("Splits taken from cache");
    }

    return SelectSplit(particle, *splitsPtr);
  } else {
    const auto splits = GenerateSplits(particle.GetNucleiData());
    return SelectSplit(particle, splits);
  }
}
