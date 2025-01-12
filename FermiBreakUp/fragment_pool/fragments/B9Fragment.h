//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSB9FragmentH_
#define FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSB9FragmentH_

#include "UnstableFragment.h"

namespace fermi {

  class B9Fragment : public UnstableFragment {
  public:
    B9Fragment(AtomicMass atomicMass, ChargeNumber chargeNumber, int polarization, FermiFloat excitationEnergy);

    B9Fragment() = delete;

    B9Fragment(const B9Fragment&) = delete;

    B9Fragment& operator=(const B9Fragment&) = delete;
  };

}  // namespace fermi

#endif // FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSB9FragmentH_
