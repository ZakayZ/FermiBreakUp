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
// Created by Artem Novikov on 08.03.2023.
//

#include "util/nuclei_properties/G4FermiNucleiProperties.hh"
#include "util/nuclei_properties/data_storage/G4FermiCSVNuclearMass.hh"
#include <gtest/gtest.h>

#include <fstream>

using namespace fbu;

TEST(TableTest, DefaultProperties)
{
  std::ifstream tableData("./small_nuclei_data.csv");
  ASSERT_TRUE(tableData.is_open());

  G4FermiStr headers;
  tableData >> headers;

  int idx;
  G4FermiNucleiProperties fbu;
  while (tableData >> idx) {
    char s;
    G4FermiAtomicMass m;
    G4FermiChargeNumber c;
    G4FermiFloat mass;
    tableData >> s >> m >> s >> c >> s >> mass;

    ASSERT_TRUE(fbu->IsStable(m, c));
    ASSERT_EQ(mass, fbu->GetNuclearMass(m, c));
  }
}

TEST(TableTest, FileProperties)
{
  std::ifstream tableData("./small_nuclei_data.csv");
  ASSERT_TRUE(tableData.is_open());

  G4FermiStr headers;
  tableData >> headers;

  int idx;
  G4FermiNucleiProperties fbu(G4FermiCSVNuclearMass("./small_nuclei_data.csv"));
  while (tableData >> idx) {
    char s;
    G4FermiAtomicMass m;
    G4FermiChargeNumber c;
    G4FermiFloat mass;
    tableData >> s >> m >> s >> c >> s >> mass;

    ASSERT_TRUE(fbu->IsStable(m, c));
    ASSERT_EQ(mass, fbu->GetNuclearMass(m, c));
  }
}
