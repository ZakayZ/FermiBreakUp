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
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_G4FERMISTABLEFRAGMENT_HH
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_G4FERMISTABLEFRAGMENT_HH

#include "G4FermiFragment.hh"

namespace fbu
{

class G4FermiStableFragment : public G4FermiFragment
{
  public:
    using G4FermiFragment::G4FermiFragment;

    void AppendDecayFragments(const G4FermiLorentzVector& momentum,
                              std::vector<G4FermiParticle>& fragments) const override;
};

}  // namespace fbu

#endif  // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_G4FERMISTABLEFRAGMENT_HH
