//
// Created by Artem Novikov on 17.02.2023.
//

#include "Fragment.h"
#include "Utilities/NucleiProperties/NucleiProperties.h"

using namespace fermi;

Fragment::Fragment(MassNumber mass_number, ChargeNumber charge_number,
                             int polarization, FermiFloat excitation_energy)
    : mass_number_(mass_number), charge_number_(charge_number),
      polarization(polarization), excitation_energy_(excitation_energy) {}

MassNumber Fragment::GetA() const {
  return GetMassNumber();
}

MassNumber Fragment::GetMassNumber() const {
  return mass_number_;
}

ChargeNumber Fragment::GetZ() const {
  return GetChargeNumber();
}

ChargeNumber Fragment::GetChargeNumber() const {
  return charge_number_;
}

int32_t Fragment::GetPolarization() const {
  return polarization;
}

FermiFloat Fragment::GetExcitationEnergy() const {
  return excitation_energy_;
}

FermiFloat Fragment::GetFragmentMass() const {
  return properties::NucleiProperties()->GetNuclearMass(mass_number_, charge_number_);
}

FermiFloat Fragment::GetTotalEnergy() const {
  return GetFragmentMass() + GetExcitationEnergy();
}

Fragment::~Fragment() = default;
