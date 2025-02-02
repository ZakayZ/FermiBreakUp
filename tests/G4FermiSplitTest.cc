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
// Created by Artem Novikov on 19.03.2023.
//

#include "G4FermiSplitter.hh"

#include "util/G4FermiDataTypes.hh"
#include <CLHEP/Units/PhysicalConstants.h>
#include <gtest/gtest.h>

#include <exception>
#include <numeric>

using namespace fbu;

TEST(SplitTest, NoDuplicates)
{
  G4FermiFragmentSplits splits;  // speeds up test
  for (G4FermiUInt a = 1; a < 18; ++a) {
    for (G4FermiUInt z = 0; z <= a; ++z) {
      const auto mass = G4FermiAtomicMass(a);
      const auto charge = G4FermiChargeNumber(z);
      splits.clear();
      G4FermiSplitter::GenerateSplits({mass, charge}, splits);

      for (auto& split : splits) {
        std::sort(split.begin(), split.end());
      }
      for (size_t i = 0; i < splits.size(); ++i) {
        for (size_t j = i + 1; j < splits.size(); ++j) {
          ASSERT_NE(splits[i], splits[j])
            << "Some of splits the same for A = " << mass << ", Z = " << charge;
        }
      }
    }
  }
}
