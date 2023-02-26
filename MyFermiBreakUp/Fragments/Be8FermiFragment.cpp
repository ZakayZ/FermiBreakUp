//
// Created by Artem Novikov on 18.02.2023.
//

#include "Be8FermiFragment.h"
#include "NucleiProperties.h"

Be8FermiFragment::Be8FermiFragment(uint32_t mass_number,
                                   uint32_t charge_number,
                                   int polarization,
                                   FermiFloat excitation_energy)
    : UnstableFermiFragment(mass_number, charge_number, polarization, excitation_energy) {
  // Be8 ----> alpha + alpha
  FermiFloat alpha_mass = NucleiProperties::GetNuclearMass(4, 2);

  decay_data_ = {DecayFragment{.mass_number = 4, .charge_number = 2, .mass = alpha_mass},
                 DecayFragment{.mass_number = 4, .charge_number = 2, .mass = alpha_mass}};

  FillMasses();
}
