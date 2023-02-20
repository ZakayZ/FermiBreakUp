//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FERMIPARTICLESPLIT_ICC_
#define FERMIBREAKUP_MYFERMIBREAKUP_FERMIPARTICLESPLIT_ICC_

#include <vector>

#include "FermiFragment.h"
#include "IntegerPartition.h"

using FragmentSplit = std::vector<const FermiFragment*>;

class FermiSplit {
 public:
  using iterator = std::vector<FragmentSplit>::iterator;
  using const_iterator = std::vector<FragmentSplit>::const_iterator;

  FermiSplit(uint32_t mass_number, uint32_t charge_number, uint32_t fragment_count);

  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;

  iterator end();
  const_iterator end() const;
  const_iterator cend() const;

  const std::vector<FragmentSplit>& GetSplits() const;

 private:
  void AddValidSplits(const std::vector<FragmentSplit>& possible_splits);

  static std::vector<size_t> FragmentVariations(const Partition& mass_partition, const Partition& charge_partition);

  static std::vector<FragmentSplit> GeneratePossibleSplits(const Partition& mass_partition,
                                                           const Partition& charge_partition,
                                                           const std::vector<size_t>& fragment_variation);

  std::vector<FragmentSplit> splits_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FERMIPARTICLESPLIT_ICC_
