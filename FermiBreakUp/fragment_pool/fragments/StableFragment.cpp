//
// Created by Artem Novikov on 17.02.2023.
//

#include "StableFragment.h"

using namespace fbu;

void StableFragment::AppendDecayFragments(const LorentzVector& momentum, std::vector<Particle>& fragments) const {
  fragments.emplace_back(
    Particle(GetAtomicMass(), GetChargeNumber(), momentum)
  );
}
