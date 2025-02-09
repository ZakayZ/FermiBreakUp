//
// Created by Artem Novikov on 17.02.2023.
//

#include "FermiBreakUp/nuclei_properties/NucleiProperties.h"
#include "FermiBreakUp/phase_decay/FermiPhaseSpaceDecay.h"

#include "UnstableFragment.h"

using namespace fbu;

UnstableFragment::UnstableFragment(
  AtomicMass atomicMass,
  ChargeNumber chargeNumber,
  FermiInt polarization,
  FermiFloat excitationEnergy,
  std::vector<NucleiData>&& decayData
)
  : Fragment(atomicMass, chargeNumber, polarization, excitationEnergy)
  , decayData_(std::move(decayData))
{
  NucleiProperties properties;
  masses_.reserve(decayData_.size());
  for (const auto& decayFragment : decayData_) {
    masses_.emplace_back(properties->GetNuclearMass(decayFragment.atomicMass, decayFragment.chargeNumber));
  }
}

void UnstableFragment::AppendDecayFragments(const LorentzVector& momentum, std::vector<Particle>& fragments) const {
  FermiPhaseSpaceDecay phaseDecay;

  auto fragmentsMomentum = phaseDecay.CalculateDecay(momentum, masses_);

  const auto boostVector = momentum.boostVector();

  for (size_t i = 0; i < decayData_.size(); ++i) {
    fragments.emplace_back(
      decayData_[i].atomicMass,
      decayData_[i].chargeNumber,
      fragmentsMomentum[i].boost(boostVector));
  }
}
