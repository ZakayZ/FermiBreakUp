//
// Created by Artem Novikov on 18.02.2023.
//

#include "He5Fragment.h"

using namespace fermi;

He5Fragment::He5Fragment(MassNumber mass_number,
                                   ChargeNumber charge_number,
                                   int polarization,
                                   FermiFloat excitation_energy)
    : UnstableFragment(mass_number, charge_number, polarization, excitation_energy) {
  // He5 ----> alpha + neutron

  Build({NucleiData{4_m, 2_c},
         NucleiData{1_m, 0_c}});
}
