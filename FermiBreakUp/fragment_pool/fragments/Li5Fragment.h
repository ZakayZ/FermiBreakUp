//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_LI5FRAGMENT_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_LI5FRAGMENT_H

#include "UnstableFragment.h"

namespace fermi {

  class Li5Fragment : public UnstableFragment {
  public:
    Li5Fragment(AtomicMass atomicMass, ChargeNumber chargeNumber, int polarization, FermiFloat excitationEnergy);

    Li5Fragment() = delete;

    Li5Fragment(const Li5Fragment&) = delete;

    Li5Fragment& operator=(const Li5Fragment&) = delete;
  };

}  // namespace fermi

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_LI5FRAGMENT_H
