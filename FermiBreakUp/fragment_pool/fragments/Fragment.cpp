//
// Created by Artem Novikov on 17.02.2023.
//

#include "Fragment.h"
#include "util/nuclei_properties/NucleiProperties.h"

using namespace fermi;

Fragment::Fragment(AtomicMass atomicMass,
                   ChargeNumber chargeNumber,
                   FermiInt polarization,
                   FermiFloat excitationEnergy)
    : atomicMass_(atomicMass)
    , chargeNumber_(chargeNumber)
    , polarization_(polarization)
    , excitationEnergy_(excitationEnergy)
{
}

AtomicMass Fragment::GetAtomicMass() const {
  return atomicMass_;
}

ChargeNumber Fragment::GetChargeNumber() const {
  return chargeNumber_;
}

FermiInt Fragment::GetPolarization() const {
  return polarization_;
}

FermiFloat Fragment::GetExcitationEnergy() const {
  return excitationEnergy_;
}

FermiFloat Fragment::GetMass() const {
  return properties::NucleiProperties()->GetNuclearMass(atomicMass_, chargeNumber_);
}

FermiFloat Fragment::GetTotalEnergy() const {
  return GetMass() + GetExcitationEnergy();
}
