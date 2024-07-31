//
// Created by Artem Novikov on 18.02.2023.
//

#include "Be8Fragment.h"

using namespace fermi;

Be8Fragment::Be8Fragment(MassNumber mass_number,
                                   ChargeNumber charge_number,
                                   int polarization,
                                   FermiFloat excitation_energy)
    : UnstableFragment(mass_number, charge_number, polarization, excitation_energy) {
  // Be8 ----> alpha + alpha

  Build({NucleiData{4_m, 2_c},
         NucleiData{4_m, 2_c}});
}
