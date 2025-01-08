//
// Created by Artem Novikov on 18.02.2023.
//

#include "Li5Fragment.h"

using namespace fermi;

Li5Fragment::Li5Fragment(AtomicMass atomicMass,
                                   ChargeNumber chargeNumber,
                                   int polarization,
                                   FermiFloat excitationEnergy)
    : UnstableFragment(atomicMass, chargeNumber, polarization, excitationEnergy) {
  // Li5 ----> alpha + proton

  Build({NucleiData{4_m, 2_c},
         NucleiData{1_m, 1_c}});
}
