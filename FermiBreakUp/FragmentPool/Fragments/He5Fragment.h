//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_HE5Fragment_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_HE5Fragment_H_

#include "UnstableFragment.h"

namespace fermi {

  class He5Fragment : public UnstableFragment {
  public:
    He5Fragment(MassNumber mass_number, ChargeNumber charge_number, int polarization, FermiFloat excitation_energy);

    He5Fragment() = delete;

    He5Fragment(const He5Fragment&) = delete;

    He5Fragment& operator=(const He5Fragment&) = delete;
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_HE5Fragment_H_
