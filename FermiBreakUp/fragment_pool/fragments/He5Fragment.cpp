//
// Created by Artem Novikov on 18.02.2023.
//

#include "He5Fragment.h"

using namespace fermi;

He5Fragment::He5Fragment(AtomicMass atomicMass,
                         ChargeNumber chargeNumber,
                         FermiInt polarization,
                         FermiFloat excitationEnergy)
  : UnstableFragment(atomicMass, chargeNumber, polarization, excitationEnergy)
{
  // He5 ----> alpha + neutron

  BuildDecay({
    NucleiData{4_m, 2_c},
    NucleiData{1_m, 0_c},
  });
}
