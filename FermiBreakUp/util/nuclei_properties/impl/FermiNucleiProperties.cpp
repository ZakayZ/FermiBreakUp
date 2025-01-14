//
// Created by Artem Novikov on 09.03.2023.
//

#include "FermiNucleiProperties.h"
#include "util/nuclei_properties/data_storage/DefaultNuclearMass.h"

using namespace fermi;

FermiNucleiProperties::FermiNucleiProperties()
  : FermiNucleiProperties(DefaultNuclearMass())
{
}

FermiFloat FermiNucleiProperties::GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  auto it = nucleiMass_.find(NucleiData{atomicMass, chargeNumber});
  if (it != nucleiMass_.end()) {
    return it->second;
  }

  #ifdef DEBUG
  std::cerr << "Unknown particle A = " + std::to_string(atomicMass) + ", Z = " + std::to_string(chargeNumber) << '\n';
  #endif
  return NuclearMass(atomicMass, chargeNumber);
}

bool FermiNucleiProperties::IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (IsInvalidNuclei(atomicMass, chargeNumber)) {
    PrintInvalidNuclei(atomicMass, chargeNumber);
    return false;
  }

  return nucleiMass_.find(NucleiData{atomicMass, chargeNumber}) != nucleiMass_.end();
}

void FermiNucleiProperties::AddMass(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiFloat mass) {
  return AddMass(NucleiData{atomicMass, chargeNumber}, mass);
}

void FermiNucleiProperties::AddMass(NucleiData nucleiData, FermiFloat mass) {
  nucleiMass_[nucleiData] = mass;
}
