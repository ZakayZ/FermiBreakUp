//
// Created by Artem Novikov on 17.02.2023.
//

#include "UnstableFragment.h"
#include "PhaseDecay/FermiPhaseSpaceDecay.h"
#include "Utilities/NucleiProperties/NucleiProperties.h"

using namespace fermi;

ParticleVector UnstableFragment::GetFragments(const LorentzVector& momentum) const {
  ParticleVector fragments_;
  FermiPhaseSpaceDecay phase_decay;

  std::vector<LorentzVector> fragments_momentum = phase_decay.CalculateDecay(momentum, masses_);

  auto boost_vector = momentum.boostVector();

  for (size_t i = 0; i < decay_data_.size(); ++i) {
    fragments_.emplace_back(decay_data_[i].mass_number, decay_data_[i].charge_number,
                            fragments_momentum[i].boost(boost_vector));
  }

  return fragments_;
}

void UnstableFragment::Build(const std::vector<NucleiData>& decay_data) {
  decay_data_ = decay_data;

  FillMasses();
}

void UnstableFragment::Build(std::vector<NucleiData>&& decay_data) {
  decay_data_ = std::move(decay_data);

  FillMasses();
}

void UnstableFragment::FillMasses() {
  properties::NucleiProperties properties;
  masses_.reserve(decay_data_.size());
  for (const auto& decay_fragment : decay_data_) {
    masses_.push_back(properties->GetNuclearMass(decay_fragment.mass_number, decay_fragment.charge_number));
  }
}
