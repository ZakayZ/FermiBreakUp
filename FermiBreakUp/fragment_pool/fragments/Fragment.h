//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_FRAGMENT_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_FRAGMENT_H

#include <vector>

#include "utilities/DataTypes.h"
#include "Particle.h"

namespace fermi {

  class Fragment {
  public:
    Fragment(AtomicMass atomicMass, ChargeNumber chargeNumber, int polarization, FermiFloat excitationEnergy);

    Fragment(const Fragment&) = delete;

    Fragment& operator=(const Fragment&) = delete;

    virtual ParticleVector GetFragments(const LorentzVector& momentum) const = 0;

    AtomicMass GetAtomicMass() const;

    ChargeNumber GetChargeNumber() const;

    FermiInt GetPolarization() const;

    FermiFloat GetExcitationEnergy() const;

    FermiFloat GetFragmentMass() const;

    FermiFloat GetTotalEnergy() const;

    virtual ~Fragment() = 0;

  protected:
    AtomicMass atomicMass_;  // A
    ChargeNumber chargeNumber_; // Z
    FermiInt polarization;
    FermiFloat excitationEnergy_;
  };

}  // namespace fermi

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_FRAGMENT_H
