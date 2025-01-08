//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPParticleSPLITICC_
#define FERMIBREAKUPMYFERMIBREAKUPParticleSPLITICC_

#include <vector>
#include <algorithm>

#include "fragment_pool/fragments/Fragment.h"
#include "utilities/IntegerPartition.h"

namespace fermi {

  using FragmentVector = std::vector<const Fragment*>;

  class Split : public std::vector<FragmentVector> {
  private:
    using Base = std::vector<FragmentVector>;

  public:
    Split(NucleiData nucleiData, uint32_t fragmentCount);

    using Base::iterator;
    using Base::const_iterator;
    using Base::begin;
    using Base::cbegin;
    using Base::end;
    using Base::cend;

  private:
    static std::string ValidateInputs(NucleiData nucleiData, uint32_t fragmentCount);

    static std::vector<size_t> FragmentVariations(const Partition& massPartition,
                                                  const Partition& chargePartition);

    static bool IsSplitPossible(const Partition& massPartition, const Partition& chargePartition);

    static std::vector<FragmentVector> GeneratePossibleSplits(const Partition& massPartition,
                                                              const Partition& chargePartition);

    void AddValidSplits(std::vector<FragmentVector>&& possibleSplits);
  };

}  // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPParticleSPLITICC_
