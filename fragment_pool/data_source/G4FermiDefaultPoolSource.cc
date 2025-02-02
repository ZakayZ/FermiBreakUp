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
// Created by Artem Novikov on 17.02.2024.
//

#include "G4FermiDefaultPoolSource.hh"

#include "fragment_pool/fragments/G4FermiStableFragment.hh"
#include "fragment_pool/fragments/G4FermiUnstableFragment.hh"
#include <CLHEP/Units/PhysicalConstants.h>

using CLHEP::MeV;

using namespace fbu;

G4FermiDefaultPoolSource::G4FermiDefaultPoolSource()
{
#define INSTANTIATE_MACRO(x, y) __CONCAT(x, y)

#define ADD_FRAGMENT_IMPL(NAME, VALUE) \
  static const auto NAME = VALUE;      \
  push_back(&NAME);

// automatic unique names are added
#define ADD_FRAGMENT(VALUE) \
  ADD_FRAGMENT_IMPL(INSTANTIATE_MACRO(G4FermiFragment, __COUNTER__), VALUE)

  ADD_FRAGMENT(G4FermiStableFragment(1_m, 0_c, 2, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(1_m, 1_c, 2, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(2_m, 1_c, 3, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(3_m, 1_c, 2, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(3_m, 2_c, 2, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(4_m, 2_c, 1, 0.00 * MeV));
  ADD_FRAGMENT(He5Fragment(5_m, 2_c, 4, 16.76 * MeV));
  ADD_FRAGMENT(Li5Fragment(5_m, 3_c, 4, 16.66 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(6_m, 2_c, 1, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(6_m, 3_c, 3, 0.00 * MeV));

  ADD_FRAGMENT(G4FermiStableFragment(6_m, 3_c, 1, 3.56 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(7_m, 3_c, 4, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(7_m, 3_c, 2, 0.48 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(7_m, 4_c, 4, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(7_m, 4_c, 2, 0.43 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(8_m, 3_c, 5, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(8_m, 3_c, 3, 0.98 * MeV));
  ADD_FRAGMENT(Be8Fragment(8_m, 4_c, 1, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(9_m, 4_c, 4, 0.00 * MeV));
  ADD_FRAGMENT(B9Fragment(9_m, 5_c, 4, 0.00 * MeV));

  ADD_FRAGMENT(G4FermiStableFragment(10_m, 4_c, 1, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(10_m, 4_c, 5, 3.37 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(10_m, 4_c, 8, 5.96 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(10_m, 4_c, 1, 6.18 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(10_m, 4_c, 5, 6.26 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(10_m, 5_c, 7, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(10_m, 5_c, 3, 0.72 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(10_m, 5_c, 1, 1.74 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(10_m, 5_c, 3, 2.15 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(10_m, 5_c, 5, 3.59 * MeV));

  ADD_FRAGMENT(G4FermiStableFragment(10_m, 6_c, 3, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(10_m, 6_c, 5, 3.35 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 5_c, 4, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 5_c, 2, 2.13 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 5_c, 6, 4.44 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 5_c, 4, 5.02 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 5_c, 10, 6.76 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 5_c, 6, 7.29 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 5_c, 4, 7.98 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 5_c, 6, 8.56 * MeV));

  ADD_FRAGMENT(G4FermiStableFragment(11_m, 6_c, 4, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 6_c, 2, 2.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 6_c, 6, 4.32 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 6_c, 4, 4.80 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 6_c, 2, 6.34 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 6_c, 8, 6.48 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 6_c, 6, 6.90 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 6_c, 4, 7.50 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 6_c, 4, 8.10 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(11_m, 6_c, 6, 8.42 * MeV));

  ADD_FRAGMENT(G4FermiStableFragment(11_m, 6_c, 8, 8.66 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(12_m, 5_c, 3, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(12_m, 5_c, 5, 0.95 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(12_m, 5_c, 5, 1.67 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(12_m, 5_c, 4, 2.65 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(12_m, 6_c, 1, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(12_m, 6_c, 5, 4.44 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(13_m, 6_c, 2, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(13_m, 6_c, 2, 3.09 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(13_m, 6_c, 4, 3.68 * MeV));

  ADD_FRAGMENT(G4FermiStableFragment(13_m, 6_c, 6, 3.85 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(13_m, 7_c, 2, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 6_c, 1, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 6_c, 3, 6.09 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 6_c, 8, 6.69 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 6_c, 6, 6.96 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 6_c, 5, 7.34 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 7_c, 3, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 7_c, 1, 2.31 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 7_c, 3, 3.95 * MeV));

  ADD_FRAGMENT(G4FermiStableFragment(14_m, 7_c, 1, 4.92 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 7_c, 5, 5.11 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 7_c, 3, 5.69 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 7_c, 7, 5.83 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 7_c, 3, 6.20 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 7_c, 7, 6.44 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(14_m, 7_c, 5, 7.03 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 7_c, 2, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 7_c, 8, 5.28 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 7_c, 4, 6.32 * MeV));

  ADD_FRAGMENT(G4FermiStableFragment(15_m, 7_c, 10, 7.22 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 7_c, 8, 7.57 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 7_c, 2, 8.31 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 7_c, 4, 8.57 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 7_c, 14, 9.15 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 7_c, 14, 9.79 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 7_c, 8, 10.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 8_c, 2, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 8_c, 8, 5.22 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 8_c, 4, 6.18 * MeV));

  ADD_FRAGMENT(G4FermiStableFragment(15_m, 8_c, 10, 6.83 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(15_m, 8_c, 8, 7.28 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(16_m, 7_c, 5, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(16_m, 7_c, 1, 0.12 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(16_m, 7_c, 7, 0.30 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(16_m, 7_c, 3, 0.40 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(16_m, 8_c, 1, 0.00 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(16_m, 8_c, 8, 6.10 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(16_m, 8_c, 5, 6.92 * MeV));
  ADD_FRAGMENT(G4FermiStableFragment(16_m, 8_c, 3, 7.12 * MeV));

#undef ADD_FRAGMENT
#undef ADD_FRAGMENT_IMPL
#undef INSTANTIATE_MACRO
}
