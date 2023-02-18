//
// Created by Artem Novikov on 18.02.2023.
//

#include "He5FermiFragment.h"
#include "TableValues/ParticleTable.h"

He5FermiFragment::He5FermiFragment(uint32_t mass_number,
                                   uint32_t charge_number,
                                   int polarization,
                                   FermiFloat excitation_energy)
    : UnstableFermiFragment(mass_number, charge_number, polarization, excitation_energy) {
  // He5 ----> alpha + neutron
  FermiFloat alpha_mass = ParticleTable::GetParticleTable()->GetIonTable()->GetIonMass(4, 2);
  FermiFloat neutron_mass = ParticleTable::GetParticleTable()->GetIonTable()->GetIonMass(1, 0);

  decay_data_ = {DecayFragment{.mass_number = 4, .charge_number = 2, .mass = alpha_mass},
                 DecayFragment{.mass_number = 1, .charge_number = 0, .mass = neutron_mass}};
}
