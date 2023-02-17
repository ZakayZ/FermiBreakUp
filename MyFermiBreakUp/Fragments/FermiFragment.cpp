//
// Created by Artem Novikov on 17.02.2023.
//

#include "FermiFragment.h"
#include "TableValues/ParticleTable.h"

FermiFragment::FermiFragment(uint32_t mass_number, uint32_t charge_number,
                             int polarization, FermiFloat excitation_energy)
    : mass_number_(mass_number), charge_number_(charge_number),
      polarization(polarization), excitation_energy_(excitation_energy) {}

uint32_t FermiFragment::GetA() const {
  return GetMassNumber();
}

uint32_t FermiFragment::GetMassNumber() const {
  return mass_number_;
}

uint32_t FermiFragment::GetZ() const {
  return GetChargeNumber();
}

uint32_t FermiFragment::GetChargeNumber() const {
  return charge_number_;
}

int32_t FermiFragment::GetPolarization() const {
  return polarization;
}

FermiFloat FermiFragment::GetExcitationEnergy() const {
  return excitation_energy_;
}

FermiFloat FermiFragment::GetFragmentMass() const {
  return ParticleTable::GetParticleTable()->GetIonTable()->GetIonMass(mass_number_, charge_number_);
}

FermiFloat FermiFragment::GetTotalEnergy() const {
  return GetFragmentMass() + GetExcitationEnergy();
}

FermiFragment::~FermiFragment() = default;
