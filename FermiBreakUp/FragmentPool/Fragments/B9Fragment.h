//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_B9Fragment_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_B9Fragment_H_

#include "UnstableFragment.h"

namespace fermi {

  class B9Fragment : public UnstableFragment {
  public:
    B9Fragment(MassNumber mass_number, ChargeNumber charge_number, int polarization, FermiFloat excitation_energy);

    B9Fragment() = delete;

    B9Fragment(const B9Fragment&) = delete;

    B9Fragment& operator=(const B9Fragment&) = delete;
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_B9Fragment_H_
