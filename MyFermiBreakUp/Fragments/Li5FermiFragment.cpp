//
// Created by Artem Novikov on 18.02.2023.
//

#include "Li5FermiFragment.h"
#include "Utilities/NucleiProperties/NucleiProperties.h"

Li5FermiFragment::Li5FermiFragment(MassNumber mass_number,
                                   ChargeNumber charge_number,
                                   int polarization,
                                   FermiFloat excitation_energy)
    : UnstableFermiFragment(mass_number, charge_number, polarization, excitation_energy) {
  // Li5 ----> alpha + proton

  Build({NucleiData{.mass_number = 4_m, .charge_number = 2_c},
         NucleiData{.mass_number = 1_m, .charge_number = 1_c}});
}
