//
// Created by Artem Novikov on 17.02.2023.
//

#include "UnstableFragment.h"
#include "PhaseDecay/FermiPhaseSpaceDecay.h"
#include "Utilities/NucleiProperties/NucleiProperties.h"

using namespace fermi;

ParticleVector UnstableFragment::GetFragments(const LorentzVector& momentum) const {
  ParticleVector fragments_;
  FermiPhaseSpaceDecay phaseDecay;

  std::vector<LorentzVector> fragmentsMomentum = phaseDecay.CalculateDecay(momentum, masses_);

  auto boostVector = momentum.boostVector();

  for (size_t i = 0; i < decayData_.size(); ++i) {
    fragments_.emplace_back(decayData_[i].massNumber, decayData_[i].chargeNumber,
                            fragmentsMomentum[i].boost(boostVector));
  }

  return fragments_;
}

void UnstableFragment::Build(const std::vector<NucleiData>& decayData) {
  decayData_ = decayData;

  FillMasses();
}

void UnstableFragment::Build(std::vector<NucleiData>&& decayData) {
  decayData_ = std::move(decayData);

  FillMasses();
}

void UnstableFragment::FillMasses() {
  properties::NucleiProperties properties;
  masses_.reserve(decayData_.size());
  for (const auto& decayFragment : decayData_) {
    masses_.push_back(properties->GetNuclearMass(decayFragment.massNumber, decayFragment.chargeNumber));
  }
}
