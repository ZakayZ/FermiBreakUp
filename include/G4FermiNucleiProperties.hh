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
// G4FermiBreakUpAN alternative de-excitation model
// by A. Novikov (January 2025)
//

#ifndef G4FERMINUCLEIPROPERTIES_HH
#define G4FERMINUCLEIPROPERTIES_HH

#include "G4FermiDataTypes.hh"

class G4FermiFastNucleiProperties
{
  public:
    G4FermiFastNucleiProperties();

    template<typename DataSource>
    G4FermiFastNucleiProperties(const DataSource& dataSource);

    template<typename Iter>
    G4FermiFastNucleiProperties(Iter begin, Iter end);

    G4FermiFloat GetNuclearMass(G4FermiAtomicMass atomicMass,
                                G4FermiChargeNumber chargeNumber) const;

    G4bool IsStable(G4FermiAtomicMass atomicMass,
                    G4FermiChargeNumber chargeNumber) const;

    void InsertNuclei(G4FermiAtomicMass atomicMass, G4FermiChargeNumber chargeNumber,
                      G4FermiFloat mass, G4bool isStable = true);

  private:
    struct G4FermiMassData
    {
        G4FermiFloat mass;

        G4bool isStable = false;  // is nuclei stable

        G4bool isCached = false;  // value has been inserted earlier
    };

    mutable std::vector<G4FermiMassData> nucleiMasses_;
};

using G4FermiNucleiProperties = G4FermiSingleton<G4FermiFastNucleiProperties>;

template<typename DataSource>
G4FermiFastNucleiProperties::G4FermiFastNucleiProperties(const DataSource& dataSource)
  : G4FermiFastNucleiProperties(dataSource.begin(), dataSource.end())
{}

template<typename Iter>
G4FermiFastNucleiProperties::G4FermiFastNucleiProperties(Iter begin, Iter end)
{
  static_assert(
    std::is_same_v<typename Iter::value_type, std::pair<const G4FermiNucleiData, G4FermiFloat>>, "invalid iterator");
  for (auto it = begin; it != end; ++it) {
    InsertNuclei(it->first.atomicMass, it->first.chargeNumber, it->second);
  }
}

#endif  // G4FERMINUCLEIPROPERTIES_HH
