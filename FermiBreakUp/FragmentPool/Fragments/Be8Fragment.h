//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_BE8Fragment_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_BE8Fragment_H_

#include "UnstableFragment.h"

namespace fermi {

  class Be8Fragment : public UnstableFragment {
  public:
    Be8Fragment(MassNumber mass_number, ChargeNumber charge_number, int polarization, FermiFloat excitation_energy);

    Be8Fragment() = delete;

    Be8Fragment(const Be8Fragment&) = delete;

    Be8Fragment& operator=(const Be8Fragment&) = delete;
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_BE8Fragment_H_
