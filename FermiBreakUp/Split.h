//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_ParticleSPLIT_ICC_
#define FERMIBREAKUP_MYFERMIBREAKUP_ParticleSPLIT_ICC_

#include <vector>
#include <algorithm>

#include "FragmentPool/Fragments/Fragment.h"
#include "Utilities/IntegerPartition.h"

namespace fermi {

  using FragmentVector = std::vector<const Fragment*>;

  class Split {
  public:
    using iterator = std::vector<FragmentVector>::iterator;
    using const_iterator = std::vector<FragmentVector>::const_iterator;

    Split(NucleiData nuclei_data, uint32_t fragment_count);

    iterator begin();
    [[nodiscard]] const_iterator begin() const;
    [[nodiscard]] const_iterator cbegin() const;

    iterator end();
    [[nodiscard]] const_iterator end() const;
    [[nodiscard]] const_iterator cend() const;

    [[nodiscard]] const std::vector<FragmentVector>& GetSplits() const;

  private:
    static std::string ValidateInputs(NucleiData nuclei_data, uint32_t fragment_count);

    static std::vector<size_t> FragmentVariations(const Partition& mass_partition,
                                                  const Partition& charge_partition);

    static bool IsSplitPossible(const Partition& mass_partition, const Partition& charge_partition);

    static std::vector<FragmentVector> GeneratePossibleSplits(const Partition& mass_partition,
                                                              const Partition& charge_partition);

    void AddValidSplits(std::vector<FragmentVector>&& possible_splits);

    std::vector<FragmentVector> splits_;
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_ParticleSPLIT_ICC_
