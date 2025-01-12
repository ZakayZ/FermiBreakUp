//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_B9FRAGMENT_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_B9FRAGMENT_H

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

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_B9FRAGMENT_H
