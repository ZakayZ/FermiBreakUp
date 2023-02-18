//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FERMIPARTICLESPLIT_ICC_
#define FERMIBREAKUP_MYFERMIBREAKUP_FERMIPARTICLESPLIT_ICC_

#include <vector>

#include "FermiFragment.h"
#include "IntegerPartition.h"

class FermiSplit {
 private:
  using FragmentSplits = std::vector<std::vector<const FermiFragment*>>;
 public:
  FermiSplit(uint32_t mass_number, uint32_t charge_number, uint32_t fragment_count);

  const FragmentSplits& GetSplits() const;

 private:
  void AddValidSplits(const FragmentSplits& possible_splits);

  static std::vector<size_t> FragmentVariations(const Partition& mass_partition, const Partition& charge_partition);

  static FragmentSplits GeneratePossibleSplits(const Partition& mass_partition,
                                               const Partition& charge_partition,
                                               const std::vector<size_t>& fragment_variation);

  FragmentSplits splits_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FERMIPARTICLESPLIT_ICC_
