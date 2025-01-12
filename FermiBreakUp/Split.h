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
    using Container = std::vector<FragmentVector>;

  public:
    Split(NucleiData nucleiData, FermiUInt fragmentCount);

    using Container::iterator;
    using Container::const_iterator;
    using Container::begin;
    using Container::cbegin;
    using Container::end;
    using Container::cend;

  private:
    void AddValidSplits(std::vector<FragmentVector>&& possibleSplits);
  };

}  // namespace fermi

#endif // FERMIBREAKUPMYFERMIBREAKUPParticleSPLITICC_
