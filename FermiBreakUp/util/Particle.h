//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_PARTICLE_H
#define FERMIBREAKUP_PARTICLE_H

#include "DataTypes.h"

namespace fermi {

  class Particle {
  public:
    Particle() = delete;

    Particle(const Particle&) = default;
    Particle(Particle&&) = default;

    Particle& operator=(const Particle&) = default;
    Particle& operator=(Particle&&) = default;

    Particle(AtomicMass atomicMass, ChargeNumber chargeNumber, const LorentzVector& momentum);

    NucleiData GetNucleiData() const;

    AtomicMass GetAtomicMass() const;

    ChargeNumber GetChargeNumber() const;

    const LorentzVector& GetMomentum() const;

    FermiFloat GetExcitationEnergy() const;

    FermiFloat GetGroundStateMass() const;

    bool IsStable() const;

  private:
    void CalculateExcitationEnergy();

    AtomicMass atomicMass_;
    ChargeNumber chargeNumber_;
    LorentzVector momentum_;

    FermiFloat groundStateMass_ = 0;
    FermiFloat excitationEnergy_ = 0;
  };

} // namespace fermi

namespace std {
  ostream& operator<<(ostream&, const ::fermi::Particle&);
} // namespace std

#endif // FERMIBREAKUP_PARTICLE_H
