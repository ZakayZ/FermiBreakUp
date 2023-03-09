//
// Created by Artem Novikov on 09.03.2023.
//

#include <fstream>

#include "FermiNucleiProperties.h"

std::map<NucleiData, FermiFloat>* FermiNucleiProperties::nuclei_mass_ = nullptr;

FermiNucleiProperties::FermiNucleiProperties() {
  if (nuclei_mass_ == nullptr) {
    nuclei_mass_ = new std::map<NucleiData, FermiFloat>();
    /// TODO do it with python modifying this file
    std::ifstream in("../small_nuclei_data.csv");
    std::string names;
    in >> names;

    size_t idx;
    MassNumber m;
    ChargeNumber c;
    FermiFloat mass;
    while(in >> idx) {
      char del;
      in >> del >> m >> del >> c >> del >> mass;
      nuclei_mass_->emplace(NucleiData{m, c}, mass);
    }
  }
}

FermiFloat FermiNucleiProperties::GetNuclearMass(MassNumber mass_number, ChargeNumber charge_number) const {
  return nuclei_mass_->at(NucleiData{mass_number, charge_number});
}

bool FermiNucleiProperties::IsStable(MassNumber mass_number, ChargeNumber charge_number) const {
  if (IsInvalidNuclei(mass_number, charge_number)) {
    std::cerr << "NucleiProperties::IsInStableTable: Wrong values for A = "
              << mass_number << " and Z = " << charge_number << std::endl;
    return false;
  }

  return nuclei_mass_->find(NucleiData{mass_number, charge_number}) != nuclei_mass_->end();
}

bool FermiNucleiProperties::IsInvalidNuclei(MassNumber mass_number, ChargeNumber charge_number) {
  return mass_number < 1_m || charge_number < 0_c || FermiUInt(charge_number) > FermiUInt(mass_number);
}

