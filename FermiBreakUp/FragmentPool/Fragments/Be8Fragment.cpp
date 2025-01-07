//
// Created by Artem Novikov on 18.02.2023.
//

#include "Be8Fragment.h"

using namespace fermi;

Be8Fragment::Be8Fragment(MassNumber massNumber,
                                   ChargeNumber chargeNumber,
                                   int polarization,
                                   FermiFloat excitationEnergy)
    : UnstableFragment(massNumber, chargeNumber, polarization, excitationEnergy) {
  // Be8 ----> alpha + alpha

  Build({NucleiData{4_m, 2_c},
         NucleiData{4_m, 2_c}});
}
