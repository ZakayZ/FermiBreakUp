//
// Created by Artem Novikov on 17.02.2023.
//

#include "UnstableFermiFragment.h"

FragmentVector UnstableFermiFragment::GetFragment(const LorentzVector& momentum) const {
  FragmentVector fragments_;

  /// TODO better pipeline!!!!!!!!!!!! without additional vectors and loop
  std::vector<FermiFloat> masses;
  masses.reserve(decay_data_.size());
  for (auto& decay_fragment_data : decay_data_) {
    masses.push_back(decay_fragment_data.mass);
  }

  FermiPhaseSpaceDecay thePhaseSpace;

  std::vector<LorentzVector> fragments_momentum = thePhaseSpace.Decay(momentum.m(), masses);

  auto beta = momentum.boostVector();

  for (size_t i = 0; i < decay_data_.size(); ++i) {
    fragments_.emplace_back(FermiParticle(decay_data_[i].mass_number,
                                           decay_data_[i].charge_number,
                                           fragments_momentum[i].boost(beta)));
  }

  return fragments_;
}
