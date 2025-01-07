//
// Created by Artem Novikov on 18.02.2023.
//

#include "B9Fragment.h"

using namespace fermi;

B9Fragment::B9Fragment(MassNumber massNumber,
                                 ChargeNumber chargeNumber,
                                 int polarization,
                                 FermiFloat excitationEnergy)
    : UnstableFragment(massNumber, chargeNumber, polarization, excitationEnergy) {
  // B9 ----> alpha + alpha + proton

  Build({NucleiData{4_m, 2_c},
         NucleiData{4_m, 2_c},
         NucleiData{1_m, 1_c}});
}
