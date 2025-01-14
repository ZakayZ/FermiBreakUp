//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_BE8FRAGMENT_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_BE8FRAGMENT_H

#include "UnstableFragment.h"

namespace fermi {

  class Be8Fragment : public UnstableFragment {
  public:
    Be8Fragment(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiInt polarization, FermiFloat excitationEnergy);

    Be8Fragment() = delete;

    Be8Fragment(const Be8Fragment&) = delete;

    Be8Fragment& operator=(const Be8Fragment&) = delete;
  };

}  // namespace fermi

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_BE8FRAGMENT_H
