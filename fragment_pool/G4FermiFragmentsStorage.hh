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
// Created by Artem Novikov on 30.01.2024.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_G4FERMIFRAGMENTSSTORAGE_HH
#define FERMIBREAKUP_FRAGMENT_POOL_G4FERMIFRAGMENTSSTORAGE_HH

#include <vector>

#include "util/G4FermiDataTypes.hh"
#include "fragments/G4FermiFragment.hh"

namespace fbu {

  class G4FermiFragmentsStorage {
  private:
    using Container = std::vector<const G4FermiFragment*>;

  public:
    class G4FermiIteratorRange {
    public:
      using const_iterator = Container::const_iterator;

      G4FermiIteratorRange(const_iterator begin, const_iterator end)
        : begin_(begin)
        , end_(end)
      {
      }

      const_iterator begin() const { return begin_; }
      const_iterator end() const { return end_; }

    private:
      const_iterator begin_;
      const_iterator end_;
    };

    G4FermiFragmentsStorage();

    template <typename DataSource>
    G4FermiFragmentsStorage(const DataSource& dataSource);

    template <typename Iter>
    G4FermiFragmentsStorage(Iter begin, Iter end);

    [[nodiscard]] size_t Count(G4FermiAtomicMass atomicMass, G4FermiChargeNumber chargeNumber) const;

    [[nodiscard]] size_t Count(G4FermiNucleiData nuclei) const;

    [[nodiscard]] G4FermiIteratorRange GetFragments(G4FermiAtomicMass atomicMass, G4FermiChargeNumber chargeNumber) const;

    [[nodiscard]] G4FermiIteratorRange GetFragments(G4FermiNucleiData nuclei) const;

    void AddFragment(const G4FermiFragment& fragment);

  private:
    static inline const Container EmptyContainer_ = {};

    std::vector<Container> fragments_;
  };

} // namespace fbu

#endif // FERMIBREAKUP_FRAGMENT_POOL_G4FERMIFRAGMENTSSTORAGE_HH
