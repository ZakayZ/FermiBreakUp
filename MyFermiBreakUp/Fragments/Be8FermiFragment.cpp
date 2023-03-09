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
  NucleiProperties properties;
  FermiFloat alpha_mass = properties.GetNuclearMass(4_m, 2_c);

  decay_data_ = {DecayFragment{.mass_number = 4_m, .charge_number = 2_c, .mass = alpha_mass},
                 DecayFragment{.mass_number = 4_m, .charge_number = 2_c, .mass = alpha_mass}};

  FillMasses();
}
