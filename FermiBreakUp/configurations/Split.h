//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_SPLIT_H
#define FERMIBREAKUP_SPLIT_H

#include <vector>
#include <algorithm>

#include "fragment_pool/fragments/Fragment.h"
#include "util/IntegerPartition.h"
#include "util/DataTypes.h"

namespace fermi {
  using FragmentSplits = std::vector<FragmentVector>;

  FragmentSplits PossibleSplits(NucleiData nucleiData, FermiUInt fragmentCount);

  FermiFloat DecayProbability(const FragmentVector& split,
                              FermiUInt atomicWeight,
                              FermiFloat totalEnergy);
} // namespace fermi

#endif // FERMIBREAKUP_SPLIT_H
