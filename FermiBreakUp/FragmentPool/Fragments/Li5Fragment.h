//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSLI5FragmentH_
#define FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSLI5FragmentH_

#include "UnstableFragment.h"

namespace fermi {

  class Li5Fragment : public UnstableFragment {
  public:
    Li5Fragment(MassNumber massNumber, ChargeNumber chargeNumber, int polarization, FermiFloat excitationEnergy);

    Li5Fragment() = delete;

    Li5Fragment(const Li5Fragment&) = delete;

    Li5Fragment& operator=(const Li5Fragment&) = delete;
  };

}  // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSLI5FragmentH_
