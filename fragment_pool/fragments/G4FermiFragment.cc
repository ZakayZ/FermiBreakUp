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

#include <iomanip>
#include <CLHEP/Units/PhysicalConstants.h>

#include "G4FermiFragment.hh"
#include "util/nuclei_properties/G4FermiNucleiProperties.hh"

using namespace fbu;

G4FermiFragment::G4FermiFragment(
  G4FermiAtomicMass atomicMass,
  G4FermiChargeNumber chargeNumber,
  G4FermiInt polarization,
  G4FermiFloat excitationEnergy
)
  : atomicMass_(atomicMass)
  , chargeNumber_(chargeNumber)
  , polarization_(polarization)
  , excitationEnergy_(excitationEnergy)
{
}

std::vector<G4FermiParticle> G4FermiFragment::GetDecayFragments(const G4FermiLorentzVector& momentum) const {
  std::vector<G4FermiParticle> result;
  AppendDecayFragments(momentum, result);
  return result;
}

G4FermiAtomicMass G4FermiFragment::GetAtomicMass() const {
  return atomicMass_;
}

G4FermiChargeNumber G4FermiFragment::GetChargeNumber() const {
  return chargeNumber_;
}

G4FermiInt G4FermiFragment::GetPolarization() const {
  return polarization_;
}

G4FermiFloat G4FermiFragment::GetExcitationEnergy() const {
  return excitationEnergy_;
}

G4FermiFloat G4FermiFragment::GetMass() const {
  return G4FermiNucleiProperties()->GetNuclearMass(atomicMass_, chargeNumber_);
}

G4FermiFloat G4FermiFragment::GetTotalEnergy() const {
  return GetMass() + GetExcitationEnergy();
}

std::ostream& std::operator<<(std::ostream& out, const G4FermiFragment& fragment) {
  const auto oldFlags = out.flags();
  const auto oldUserPrecision = out.precision();

  out.setf(std::ios::floatfield);
  out << "FermiFragment: { A = " << fragment.GetAtomicMass()
      << ", Z = " << fragment.GetChargeNumber()
      << ", pol = " << fragment.GetPolarization();

  out.setf(std::ios::scientific, std::ios::floatfield);
  out << std::setprecision(3)
      << ", U = " << fragment.GetExcitationEnergy() / CLHEP::MeV
      << " }";

  out.setf(oldFlags, std::ios::floatfield);
  out.precision(oldUserPrecision);

  return out;
}
