//
// Created by Artem Novikov on 18.02.2023.
//

#include "He5Fragment.h"

using namespace fermi;

He5Fragment::He5Fragment(MassNumber massNumber,
                                   ChargeNumber chargeNumber,
                                   int polarization,
                                   FermiFloat excitationEnergy)
    : UnstableFragment(massNumber, chargeNumber, polarization, excitationEnergy) {
  // He5 ----> alpha + neutron

  Build({NucleiData{4_m, 2_c},
         NucleiData{1_m, 0_c}});
}
