//
// Created by Artem Novikov on 19.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FERMICONFIGURATIONS_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FERMICONFIGURATIONS_H_

#include <vector>

#include "FermiSplit.h"

class FermiConfigurations {
 public:
  FermiConfigurations(MassNumber mass_number, ChargeNumber charge_number, FermiFloat total_energy);

  bool IsSplitPossible() const;

  const FragmentSplit& ChooseSplit() const;

 private:

  std::vector<FragmentSplit> configurations_;
  std::vector<FermiFloat> weights_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FERMICONFIGURATIONS_H_
