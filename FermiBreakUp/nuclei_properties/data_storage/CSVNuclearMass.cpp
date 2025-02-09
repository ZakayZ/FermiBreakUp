//
// Created by Artem Novikov on 18.02.2024.
//

#include <fstream>

#include "CSVNuclearMass.h"

using namespace fbu;

CSVNuclearMass::CSVNuclearMass(
  const FermiStr& csvFilename,
  const FermiStr& massNumberName,
  const FermiStr& chargeNumberName,
  const FermiStr& massName)
{
  std::ifstream in(csvFilename);

  if (!in.is_open()) {
    throw std::runtime_error("invalid CSV file path");
  }

  int32_t massNumberIdx = -1, chargeNumberIdx = -1, massIdx = -1;

  FermiStr line;
  in >> line;
  line += ',';
  int32_t columnIdx = 0;
  uint32_t start = 0;
  size_t commaPos = line.find(',', start);
  while (commaPos != FermiStr::npos) {
    if (line.substr(start, commaPos - start) == massNumberName) {
      massNumberIdx = columnIdx;
    }

    if (line.substr(start, commaPos - start) == chargeNumberName) {
      chargeNumberIdx = columnIdx;
    }

    if (line.substr(start, commaPos - start) == massName) {
      massIdx = columnIdx;
    }

    ++columnIdx;
    start = commaPos + 1;
    commaPos = line.find(',', start);
  }
  int32_t columnsCount = columnIdx;

  if (massNumberIdx == -1) {
    throw std::runtime_error("no mass number found");
  }

  if (chargeNumberIdx == -1) {
    throw std::runtime_error("no charge number found");
  }

  if (massIdx == -1) {
    throw std::runtime_error("no nuclei mass found");
  }

  AtomicMass m = 0_m;
  ChargeNumber c = 0_c;
  FermiFloat mass = 0.;
  while (in >> line) {
    line += ',';
    columnIdx = 0;
    start = 0;
    commaPos = line.find(',', start);
    while (commaPos != FermiStr::npos) {
      if (columnIdx == massNumberIdx) {
        m = AtomicMass(std::stoi(line.substr(start, commaPos - start)));
      } else if (columnIdx == chargeNumberIdx) {
        c = ChargeNumber(std::stoi(line.substr(start, commaPos - start)));
      } else if (columnIdx == massIdx) {
        mass = FermiFloat(std::stod(line.substr(start, commaPos - start)));
      }

      ++columnIdx;
      start = commaPos + 1;
      commaPos = line.find(',', start);
    }

    if (columnsCount != columnIdx) {
      throw std::runtime_error("invalid row format: " + line);
    }

    emplace(NucleiData{m, c}, mass);
  }
}
