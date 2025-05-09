//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_FRAGMENT_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_FRAGMENT_H

#include <ostream>
#include <vector>

#include "FermiBreakUp/util/DataTypes.h"
#include "FermiBreakUp/util/Particle.h"

namespace fbu {
  class Fragment;

  using FragmentVector = std::vector<const Fragment*>;

  class Fragment {
  public:
    Fragment(
      AtomicMass atomicMass,
      ChargeNumber chargeNumber,
      FermiInt polarization,
      FermiFloat excitationEnergy);

    Fragment(Fragment&&) = default;

    std::vector<Particle> GetDecayFragments(const LorentzVector& momentum) const;

    virtual void AppendDecayFragments(const LorentzVector& momentum, std::vector<Particle>& particles) const = 0;

    AtomicMass GetAtomicMass() const;

    ChargeNumber GetChargeNumber() const;

    FermiInt GetPolarization() const;

    FermiFloat GetExcitationEnergy() const;

    FermiFloat GetMass() const;

    FermiFloat GetTotalEnergy() const;

    virtual ~Fragment() = default;

  protected:
    AtomicMass atomicMass_;  // A
    ChargeNumber chargeNumber_; // Z
    FermiInt polarization_;
    FermiFloat excitationEnergy_;
    FermiFloat mass_;
  };
} // namespace fbu

namespace std {
  ostream& operator<<(ostream&, const ::fbu::Fragment&);
} // namespace std

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_FRAGMENT_H
