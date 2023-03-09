//
// Created by Artem Novikov on 18.02.2023.
//

#include "B9FermiFragment.h"
#include "Utilities/NucleiProperties/NucleiProperties.h"

B9FermiFragment::B9FermiFragment(MassNumber mass_number,
                                 ChargeNumber charge_number,
                                 int polarization,
                                 FermiFloat excitation_energy)
    : UnstableFermiFragment(mass_number, charge_number, polarization, excitation_energy) {
  // B9 ----> alpha + alpha + proton
  NucleiProperties properties;
  FermiFloat alpha_mass = properties.GetNuclearMass(4_m, 2_c);
  FermiFloat proton_mass = properties.GetNuclearMass(1_m, 1_c);

  decay_data_ = {DecayFragment{.mass_number = 4_m, .charge_number = 2_c, .mass = alpha_mass},
                 DecayFragment{.mass_number = 4_m, .charge_number = 2_c, .mass = alpha_mass},
                 DecayFragment{.mass_number = 1_m, .charge_number = 1_c, .mass = proton_mass}};

  FillMasses();
}
