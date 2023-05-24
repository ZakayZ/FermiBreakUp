//
// Created by Artem Novikov on 18.02.2023.
//

#include "B9FermiFragment.h"

B9FermiFragment::B9FermiFragment(MassNumber mass_number,
                                 ChargeNumber charge_number,
                                 int polarization,
                                 FermiFloat excitation_energy)
    : UnstableFermiFragment(mass_number, charge_number, polarization, excitation_energy) {
  // B9 ----> alpha + alpha + proton

  Build({NucleiData{.mass_number = 4_m, .charge_number = 2_c},
         NucleiData{.mass_number = 4_m, .charge_number = 2_c},
         NucleiData{.mass_number = 1_m, .charge_number = 1_c}});
}
