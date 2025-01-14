//
// Created by Artem Novikov on 18.02.2023.
//

#include "Be8Fragment.h"

using namespace fermi;

Be8Fragment::Be8Fragment(AtomicMass atomicMass,
                         ChargeNumber chargeNumber,
                         FermiInt polarization,
                         FermiFloat excitationEnergy)
  : UnstableFragment(atomicMass, chargeNumber, polarization, excitationEnergy)
{
  // Be8 ----> alpha + alpha

  BuildDecay({
    NucleiData{4_m, 2_c},
    NucleiData{4_m, 2_c},
  });
}
