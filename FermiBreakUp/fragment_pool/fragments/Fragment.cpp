//
// Created by Artem Novikov on 17.02.2023.
//

#include "Fragment.h"
#include "utilities/nuclei_properties/NucleiProperties.h"

using namespace fermi;

Fragment::Fragment(AtomicMass atomicMass, ChargeNumber chargeNumber,
                             int polarization, FermiFloat excitationEnergy)
    : atomicMass_(atomicMass), chargeNumber_(chargeNumber),
      polarization(polarization), excitationEnergy_(excitationEnergy) {}

AtomicMass Fragment::GetA() const {
  return GetAtomicMass();
}

AtomicMass Fragment::GetAtomicMass() const {
  return atomicMass_;
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
  return properties::nuclei_properties()->GetNuclearMass(atomicMass_, chargeNumber_);
}

FermiFloat Fragment::GetTotalEnergy() const {
  return GetFragmentMass() + GetExcitationEnergy();
}

Fragment::~Fragment() = default;
