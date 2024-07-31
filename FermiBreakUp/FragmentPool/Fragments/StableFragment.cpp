//
// Created by Artem Novikov on 17.02.2023.
//

#include "StableFragment.h"

using namespace fermi;

ParticleVector StableFragment::GetFragments(const LorentzVector& momentum) const {
  return {Particle(GetMassNumber(), GetChargeNumber(), momentum)};
}
