//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_SPLIT_H
#define FERMIBREAKUP_SPLIT_H

#include "fragment_pool/fragments/Fragment.h"
#include "util/IntegerPartition.h"
#include "util/DataTypes.h"

namespace fermi {
  using FragmentSplits = std::vector<FragmentVector>;

  FermiFloat DecayWeight(const FragmentVector& split, AtomicMass atomicMass, FermiFloat totalEnergy);

  FragmentSplits GenerateSplits(NucleiData nucleiData);

} // namespace fermi

#endif // FERMIBREAKUP_SPLIT_H
