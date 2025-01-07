//
// Created by Artem Novikov on 09.03.2023.
//

#include "FermiNucleiProperties.h"
#include "Utilities/NucleiProperties/DataStorage/DefaultNuclearMass.h"

namespace properties {

FermiNucleiProperties::FermiNucleiProperties() : FermiNucleiProperties(DefaultNuclearMass()) {}

FermiFloat FermiNucleiProperties::GetNuclearMass(MassNumber massNumber, ChargeNumber chargeNumber) const {
  auto it = nucleiMass_.find(NucleiData{massNumber, chargeNumber});
  if (it != nucleiMass_.end()) {
    return it->second;
  }

  #ifdef DEBUG
  std::cerr << "Unknown particle A = " + std::to_string(massNumber) + ", Z = " + std::to_string(chargeNumber) << '\n';
  #endif
  return NuclearMass(massNumber, chargeNumber);
}

bool FermiNucleiProperties::IsStable(MassNumber massNumber, ChargeNumber chargeNumber) const {
  if (IsInvalidNuclei(massNumber, chargeNumber)) {
    PrintInvalidNuclei(massNumber, chargeNumber);
    return false;
  }

  return nucleiMass_.contains(NucleiData{massNumber, chargeNumber});
}

void FermiNucleiProperties::AddMass(MassNumber massNumber, ChargeNumber chargeNumber, FermiFloat mass) {
  return AddMass(NucleiData{massNumber, chargeNumber}, mass);
}

void FermiNucleiProperties::AddMass(NucleiData nucleiData, FermiFloat mass) {
  nucleiMass_[nucleiData] = mass;
}

} // namespace properties
