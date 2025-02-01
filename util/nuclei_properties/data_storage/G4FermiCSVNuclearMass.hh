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

#ifndef FERMIBREAKUP_UTIL_NUCLEI_PROPERTIES_DATA_STORAGE_G4FERMICSVNUCLEARMASS_HH
#define FERMIBREAKUP_UTIL_NUCLEI_PROPERTIES_DATA_STORAGE_G4FERMICSVNUCLEARMASS_HH

#include <unordered_map>

#include "util/G4FermiDataTypes.hh"

namespace fbu {

  class G4FermiCSVNuclearMass : private std::unordered_map<G4FermiNucleiData, G4FermiFloat> {
  private:
    using Container = std::unordered_map<G4FermiNucleiData, G4FermiFloat>;

  public:
    G4FermiCSVNuclearMass(
      const G4FermiStr& csvFilename,
      const G4FermiStr& massNumberName = "A",
      const G4FermiStr& chargeNumberName = "Z",
      const G4FermiStr& massName = "mass"
    );

    using Container::iterator;
    using Container::const_iterator;
    using Container::begin;
    using Container::cbegin;
    using Container::end;
    using Container::cend;
  };

} // namespace fbu

#endif // FERMIBREAKUP_UTIL_NUCLEI_PROPERTIES_DATA_STORAGE_G4FERMICSVNUCLEARMASS_HH
