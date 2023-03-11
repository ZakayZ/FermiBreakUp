//
// Created by Artem Novikov on 09.03.2023.
//

#include <fstream>

#include "FermiNucleiProperties.h"
#include "FermiPropertiesBuilder.h"

FermiNucleiProperties::MassMap* FermiNucleiProperties::nuclei_mass_ = nullptr;

FermiNucleiProperties::FermiNucleiProperties() {
  if (nuclei_mass_ == nullptr) {
    nuclei_mass_ = new MassMap();
    PropertiesBuilder builder;
    builder.BuildTable(*nuclei_mass_);
  }
}

FermiFloat FermiNucleiProperties::GetNuclearMass(MassNumber mass_number, ChargeNumber charge_number) const {
  auto it = nuclei_mass_->find(NucleiData{mass_number, charge_number});
  if (it != nuclei_mass_->end()) {
    return it->second;
  }
  return NuclearMass(mass_number, charge_number);
}

bool FermiNucleiProperties::IsStable(MassNumber mass_number, ChargeNumber charge_number) const {
  if (IsInvalidNuclei(mass_number, charge_number)) {
    std::cerr << "NucleiProperties::IsInStableTable: Wrong values for A = "
              << mass_number << " and Z = " << charge_number << std::endl;
    return false;
  }

  return nuclei_mass_->find(NucleiData{mass_number, charge_number}) != nuclei_mass_->end();
}
