//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// G4FermiBreakUp alternative de-excitation model
// by A. Novikov (January 2025)
//
//
// Created by Artem Novikov on 18.02.2024.
//

#include "G4FermiCSVNuclearMass.hh"

#include <fstream>

using namespace fbu;

G4FermiCSVNuclearMass::G4FermiCSVNuclearMass(const G4FermiStr& csvFilename,
                                             const G4FermiStr& massNumberName,
                                             const G4FermiStr& chargeNumberName,
                                             const G4FermiStr& massName)
{
  std::ifstream in(csvFilename);

  if (!in.is_open()) {
    throw std::runtime_error("invalid CSV file path");
  }

  int32_t massNumberIdx = -1, chargeNumberIdx = -1, massIdx = -1;

  G4FermiStr line;
  in >> line;
  line += ',';
  int32_t columnIdx = 0;
  uint32_t start = 0;
  size_t comma = line.find(',', start);
  while (comma != G4FermiStr::npos) {
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

  G4FermiAtomicMass m = 0_m;
  G4FermiChargeNumber c = 0_c;
  G4FermiFloat mass;
  while (in >> line) {
    line += ',';
    columnIdx = 0;
    start = 0;
    comma = line.find(',', start);
    while (comma != G4FermiStr::npos) {
      if (columnIdx == massNumberIdx) {
        m = G4FermiAtomicMass(std::stoi(line.substr(start, comma - start)));
      }

      if (columnIdx == chargeNumberIdx) {
        c = G4FermiChargeNumber(std::stoi(line.substr(start, comma - start)));
      }

      if (columnIdx == massIdx) {
        mass = G4FermiFloat(std::stod(line.substr(start, comma - start)));
      }

      ++columnIdx;
      start = comma + 1;
      comma = line.find(',', start);
    }

    if (columnsCount != columnIdx) {
      throw std::runtime_error("invalid row format: " + line);
    }

    emplace(G4FermiNucleiData{m, c}, mass);
  }
}
