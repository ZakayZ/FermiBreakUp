//
// Created by Artem Novikov on 11.03.2023.
//

#include <fstream>

#include "FermiPropertiesFileBuilder.h"


void FermiPropertiesFileBuilder::BuildTable(FermiNucleiProperties::MassMap& data) const {
  std::ifstream in("../small_nuclei_data.csv");
  std::string names;
  in >> names;

  size_t idx;
  MassNumber m;
  ChargeNumber c;
  FermiFloat mass;
  while (in >> idx) {
    char del;
    in >> del >> m >> del >> c >> del >> mass;
    data.emplace(NucleiData{m, c}, mass);
  }
}
