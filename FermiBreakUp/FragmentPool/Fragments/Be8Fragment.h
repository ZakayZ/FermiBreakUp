//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSBE8FragmentH_
#define FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSBE8FragmentH_

#include "UnstableFragment.h"

namespace fermi {

  class Be8Fragment : public UnstableFragment {
  public:
    Be8Fragment(MassNumber massNumber, ChargeNumber chargeNumber, int polarization, FermiFloat excitationEnergy);

    Be8Fragment() = delete;

    Be8Fragment(const Be8Fragment&) = delete;

    Be8Fragment& operator=(const Be8Fragment&) = delete;
  };

}  // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSBE8FragmentH_
