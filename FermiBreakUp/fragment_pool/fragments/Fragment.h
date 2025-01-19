//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_FRAGMENT_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_FRAGMENT_H

#include <ostream>
#include <vector>

#include "util/DataTypes.h"
#include "util/Particle.h"

namespace fermi {
  class Fragment;

  using FragmentVector = std::vector<const Fragment*>;

  class Fragment {
  public:
    Fragment(
      AtomicMass atomicMass,
      ChargeNumber chargeNumber,
      FermiInt polarization,
      FermiFloat excitationEnergy);

    Fragment(const Fragment&) = delete;

    Fragment& operator=(const Fragment&) = delete;

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
  };

} // namespace fermi

namespace std {
  ostream& operator<<(ostream&, const ::fermi::Fragment&);
} // namespace std
#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_FRAGMENT_H
