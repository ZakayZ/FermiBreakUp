//
// Created by Artem Novikov on 17.02.2023.
//

#include "UnstableFermiFragment.h"
#include "Utilities/PhaseDecay/FermiPhaseSpaceDecay.h"

ParticleVector UnstableFermiFragment::GetFragment(const LorentzVector& momentum) const {
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

void UnstableFermiFragment::FillMasses() {
  masses_.reserve(decay_data_.size());
  for (auto& decay_fragment_data : decay_data_) {
    masses_.push_back(decay_fragment_data.mass);
  }
}
