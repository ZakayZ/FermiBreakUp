//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_SPLIT_H
#define FERMIBREAKUP_SPLIT_H

#include "fragment_pool/fragments/Fragment.h"
#include "util/DataTypes.h"

namespace fbu {
  using FragmentSplits = std::vector<FragmentVector>;

  class Splitter {
  public:
    static FermiFloat DecayWeight(const FragmentVector& split, AtomicMass atomicMass, FermiFloat totalEnergy);

    static FermiFloat SplitFactor(const FragmentVector& split, AtomicMass atomicMass);

    static FermiFloat KineticFactor(const FragmentVector& split, FermiFloat totalEnergy);

    static void GenerateSplits(NucleiData nucleiData, std::vector<FragmentVector>& splits);

    static std::vector<FragmentVector> GenerateSplits(NucleiData nucleiData);
  };
} // namespace fbu

#endif // FERMIBREAKUP_SPLIT_H
