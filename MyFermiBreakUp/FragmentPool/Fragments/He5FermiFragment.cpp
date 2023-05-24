//
// Created by Artem Novikov on 18.02.2023.
//

#include "He5FermiFragment.h"

He5FermiFragment::He5FermiFragment(MassNumber mass_number,
                                   ChargeNumber charge_number,
                                   int polarization,
                                   FermiFloat excitation_energy)
    : UnstableFermiFragment(mass_number, charge_number, polarization, excitation_energy) {
  // He5 ----> alpha + neutron

  Build({NucleiData{.mass_number = 4_m, .charge_number = 2_c},
         NucleiData{.mass_number = 1_m, .charge_number = 0_c}});
}
