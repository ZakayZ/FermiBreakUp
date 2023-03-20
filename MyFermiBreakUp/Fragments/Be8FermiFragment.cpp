//
// Created by Artem Novikov on 18.02.2023.
//

#include "Be8FermiFragment.h"
#include "Utilities/NucleiProperties/NucleiProperties.h"

Be8FermiFragment::Be8FermiFragment(MassNumber mass_number,
                                   ChargeNumber charge_number,
                                   int polarization,
                                   FermiFloat excitation_energy)
    : UnstableFermiFragment(mass_number, charge_number, polarization, excitation_energy) {
  // Be8 ----> alpha + alpha

  Build({NucleiData{.mass_number = 4_m, .charge_number = 2_c},
         NucleiData{.mass_number = 4_m, .charge_number = 2_c}});
}
