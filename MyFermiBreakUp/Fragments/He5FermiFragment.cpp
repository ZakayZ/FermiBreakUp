//
// Created by Artem Novikov on 18.02.2023.
//

#include "He5FermiFragment.h"
#include "Utilities/NucleiProperties/NucleiProperties.h"

He5FermiFragment::He5FermiFragment(MassNumber mass_number,
                                   ChargeNumber charge_number,
                                   int polarization,
                                   FermiFloat excitation_energy)
    : UnstableFermiFragment(mass_number, charge_number, polarization, excitation_energy) {
  // He5 ----> alpha + neutron
  NucleiProperties properties;
  FermiFloat alpha_mass = properties.GetNuclearMass(4_m, 2_c);
  FermiFloat neutron_mass = properties.GetNuclearMass(1_m, 0_c);

  decay_data_ = {DecayFragment{.mass_number = 4_m, .charge_number = 2_c, .mass = alpha_mass},
                 DecayFragment{.mass_number = 1_m, .charge_number = 0_c, .mass = neutron_mass}};

  FillMasses();
}
