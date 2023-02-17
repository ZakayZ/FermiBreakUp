//
// Created by Artem Novikov on 17.02.2023.
//

#include "StableFermiFragment.h"

FragmentVector StableFermiFragment::GetFragment(const LorentzVector& momentum) const {
  return {FermiParticle(GetMassNumber(), GetChargeNumber(), momentum)}; /// TODO avoid new, or change for value types
}
