//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSHE5FragmentH_
#define FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSHE5FragmentH_

#include "UnstableFragment.h"

namespace fermi {

  class He5Fragment : public UnstableFragment {
  public:
    He5Fragment(AtomicMass atomicMass, ChargeNumber chargeNumber, int polarization, FermiFloat excitationEnergy);

    He5Fragment() = delete;

    He5Fragment(const He5Fragment&) = delete;

    He5Fragment& operator=(const He5Fragment&) = delete;
  };

}  // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSHE5FragmentH_
