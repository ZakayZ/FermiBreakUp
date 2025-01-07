//
// Created by Artem Novikov on 17.02.2023.
//

#include "Fragment.h"
#include "Utilities/NucleiProperties/NucleiProperties.h"

using namespace fermi;

Fragment::Fragment(MassNumber massNumber, ChargeNumber chargeNumber,
                             int polarization, FermiFloat excitationEnergy)
    : massNumber_(massNumber), chargeNumber_(chargeNumber),
      polarization(polarization), excitationEnergy_(excitationEnergy) {}

MassNumber Fragment::GetA() const {
  return GetMassNumber();
}

MassNumber Fragment::GetMassNumber() const {
  return massNumber_;
}

ChargeNumber Fragment::GetZ() const {
  return GetChargeNumber();
}

ChargeNumber Fragment::GetChargeNumber() const {
  return chargeNumber_;
}

int32_t Fragment::GetPolarization() const {
  return polarization;
}

FermiFloat Fragment::GetExcitationEnergy() const {
  return excitationEnergy_;
}

FermiFloat Fragment::GetFragmentMass() const {
  return properties::NucleiProperties()->GetNuclearMass(massNumber_, chargeNumber_);
}

FermiFloat Fragment::GetTotalEnergy() const {
  return GetFragmentMass() + GetExcitationEnergy();
}

Fragment::~Fragment() = default;
