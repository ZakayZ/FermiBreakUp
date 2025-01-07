//
// Created by Artem Novikov on 18.02.2024.
//

#include <fstream>

#include "CSVNuclearMass.h"

namespace properties {

CSVNuclearMass::CSVNuclearMass(const std::string& csvFilename,
                               const std::string& massNumberName,
                               const std::string& chargeNumberName,
                               const std::string& massName) {
  std::ifstream in(csvFilename);

  if (!in.is_open()) {
    throw std::runtime_error("invalid CSV file path");
  }

  int massNumberIdx = -1, chargeNumberIdx = -1, massIdx = -1;

  std::string line;
  in >> line;
  line += ',';
  int columnIdx = 0;
  uint start = 0;
  auto comma = line.find(',', start);
  while (comma != std::string::npos) {
    if (line.substr(start, comma - start) == massNumberName) {
      massNumberIdx = columnIdx;
    }

    if (line.substr(start, comma - start) == chargeNumberName) {
      chargeNumberIdx = columnIdx;
    }

    if (line.substr(start, comma - start) == massName) {
      massIdx = columnIdx;
    }

    ++columnIdx;
    start = comma + 1;
    comma = line.find(',', start);
  }
  int columnsCount = columnIdx;

  if (massNumberIdx == -1) {
    throw std::runtime_error("no mass number found");
  }

  if (chargeNumberIdx == -1) {
    throw std::runtime_error("no charge number found");
  }

  if (massIdx == -1) {
    throw std::runtime_error("no nuclei mass found");
  }

  MassNumber m = 0_m;
  ChargeNumber c = 0_c;
  FermiFloat mass;
  while (in >> line) {
    line += ',';
    columnIdx = 0;
    start = 0;
    comma = line.find(',', start);
    while (comma != std::string::npos) {
      if (columnIdx == massNumberIdx) {
        m = MassNumber(std::stoi(line.substr(start, comma - start)));
      }

      if (columnIdx == chargeNumberIdx) {
        c = ChargeNumber(std::stoi(line.substr(start, comma - start)));
      }

      if (columnIdx == massIdx) {
        mass = FermiFloat(std::stod(line.substr(start, comma - start)));
      }

      ++columnIdx;
      start = comma + 1;
      comma = line.find(',', start);
    }

    if (columnsCount != columnIdx) {
      throw std::runtime_error("invalid row format: " + line);
    }

    masses_.emplace(NucleiData{m, c}, mass);
  }
}

} // namespace properties
