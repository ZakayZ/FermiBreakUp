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

#ifndef FERMIBREAKUP_PHASE_DECAY_G4FERMIPHASESPACEDECAY_HH
#define FERMIBREAKUP_PHASE_DECAY_G4FERMIPHASESPACEDECAY_HH

#include "G4FermiKopylovDecay.hh"
#include "G4FermiVDecay.hh"

namespace fbu
{

using G4FermiPhaseSpaceDecay = G4FermiKopylovDecay;  // or just Decay

static_assert(std::is_base_of<G4FermiVDecay, G4FermiPhaseSpaceDecay>::value,
              "Invalid phase sampler");

}  // namespace fbu

#endif  // FERMIBREAKUP_PHASE_DECAY_G4FERMIPHASESPACEDECAY_HH
