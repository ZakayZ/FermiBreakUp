//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_HE5FRAGMENT_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_HE5FRAGMENT_H

#include "UnstableFragment.h"

namespace fermi {

  class He5Fragment : public UnstableFragment {
  public:
    He5Fragment(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiInt polarization, FermiFloat excitationEnergy);

    He5Fragment() = delete;

    He5Fragment(const He5Fragment&) = delete;

    He5Fragment& operator=(const He5Fragment&) = delete;
  };

}  // namespace fermi

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_HE5FRAGMENT_H
