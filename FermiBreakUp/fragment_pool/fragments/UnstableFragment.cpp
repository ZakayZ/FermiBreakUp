//
// Created by Artem Novikov on 17.02.2023.
//

#include "UnstableFragment.h"
#include "phase_decay/FermiPhaseSpaceDecay.h"
#include "util/nuclei_properties/NucleiProperties.h"

using namespace fermi;

ParticleVector UnstableFragment::GetFragments(const LorentzVector& momentum) const {
  ParticleVector fragments_;
  fragments_.reserve(masses_.size());

  FermiPhaseSpaceDecay phaseDecay;

  auto fragmentsMomentum = phaseDecay.CalculateDecay(momentum, masses_);

  auto boostVector = momentum.boostVector();

  for (size_t i = 0; i < decayData_.size(); ++i) {
    fragments_.emplace_back(decayData_[i].atomicMass,
                            decayData_[i].chargeNumber,
                            fragmentsMomentum[i].boost(boostVector));
  }

  return fragments_;
}

void UnstableFragment::BuildDecay(std::vector<NucleiData>&& decayData) {
  decayData_ = std::move(decayData);

  FillMasses();
}

void UnstableFragment::BuildDecay(const std::vector<NucleiData>& decayData) {
  auto copy = decayData;
  BuildDecay(std::move(copy));
}

void UnstableFragment::FillMasses() {
  properties::NucleiProperties properties;
  masses_.reserve(decayData_.size());
  for (const auto& decayFragment : decayData_) {
    masses_.push_back(properties->GetNuclearMass(decayFragment.atomicMass, decayFragment.chargeNumber));
  }
}
