//
// Created by Artem Novikov on 17.02.2023.
//

#include "FermiFragment.h"

FermiFragment::FermiFragment(uint32_t mass_number,
                             uint32_t proton_number,
                             int polarization,
                             FermiFloat excitation_energy) {

}

uint32_t FermiFragment::GetA() const {
  return GetMassNumber();
}

uint32_t FermiFragment::GetMassNumber() const {
  return mass_number_;
}

uint32_t FermiFragment::GetZ() const {
  return GetProtonNumber();
}

uint32_t FermiFragment::GetProtonNumber() const {
  return proton_number_;
}

int32_t FermiFragment::GetPolarization() const {
  return polarization;
}

FermiFloat FermiFragment::GetExcitationEnergy() const {
  return excitation_energy_;
}

FermiFloat FermiFragment::GetFragmentMass() const {
  return G4ParticleTable::GetParticleTable()->GetIonTable()->GetIonMass(mass_number_, proton_number_);  /// TODO Table
}

FermiFloat FermiFragment::GetTotalEnergy() const {
  return GetFragmentMass() + GetExcitationEnergy();
}

FermiFragment::~FermiFragment() = default;
