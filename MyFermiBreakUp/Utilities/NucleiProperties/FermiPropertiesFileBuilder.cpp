//
// Created by Artem Novikov on 11.03.2023.
//

#include <fstream>

#include "FermiPropertiesFileBuilder.h"

FermiPropertiesFileBuilder::FermiPropertiesFileBuilder(const std::string& source) : source_(source) {}

void FermiPropertiesFileBuilder::BuildTable(FermiNucleiProperties::MassMap& data) const {
  std::ifstream in(source_);
  if(!in.is_open()) {
    throw std::runtime_error("invalid file path");
  }
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
