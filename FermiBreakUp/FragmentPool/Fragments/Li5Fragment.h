//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_LI5Fragment_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_LI5Fragment_H_

#include "UnstableFragment.h"

namespace fermi {

  class Li5Fragment : public UnstableFragment {
  public:
    Li5Fragment(MassNumber mass_number, ChargeNumber charge_number, int polarization, FermiFloat excitation_energy);

    Li5Fragment() = delete;

    Li5Fragment(const Li5Fragment&) = delete;

    Li5Fragment& operator=(const Li5Fragment&) = delete;
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_LI5Fragment_H_
