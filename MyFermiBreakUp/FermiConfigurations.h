//
// Created by Artem Novikov on 19.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FERMICONFIGURATIONS_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FERMICONFIGURATIONS_H_

#include <vector>

#include "FermiSplit.h"

class FermiConfigurations {
 public:
  FermiConfigurations(uint32_t mass_number, uint32_t charge_number, FermiFloat total_energy);

  bool IsSplitPossible() const;

  const FragmentSplit& ChooseSplit() const;

 private:
  static const size_t MaxNumberOfFragments;

  std::vector<FragmentSplit> configurations_;
  std::vector<FermiFloat> weights_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FERMICONFIGURATIONS_H_
