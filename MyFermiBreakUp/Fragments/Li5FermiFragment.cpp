//
// Created by Artem Novikov on 18.02.2023.
//

#include "Li5FermiFragment.h"
#include "TableValues/ParticleTable.h"

Li5FermiFragment::Li5FermiFragment(uint32_t mass_number,
                                   uint32_t charge_number,
                                   int polarization,
                                   FermiFloat excitation_energy)
    : UnstableFermiFragment(mass_number, charge_number, polarization, excitation_energy) {
  // Li5 ----> alpha + proton
  FermiFloat alpha_mass = ParticleTable::GetParticleTable()->GetIonTable()->GetIonMass(4, 2);
  FermiFloat proton_mass = ParticleTable::GetParticleTable()->GetIonTable()->GetIonMass(1, 1);

  decay_data_ = {DecayFragment{.mass_number = 4, .charge_number = 2, .mass = alpha_mass},
                 DecayFragment{.mass_number = 1, .charge_number = 1, .mass = proton_mass}};

  FillMasses();  /// TODO have to be called from every derived class, should be automatic :(
}
