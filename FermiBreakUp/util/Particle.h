//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_PARTICLE_H
#define FERMIBREAKUP_PARTICLE_H

#include <vector>

#include "DataTypes.h"

namespace fermi {

  class Particle;

  using ParticleVector = std::vector<Particle>;

  class Particle {
  public:
    Particle() = delete;

    Particle(const Particle&) = default;

    Particle& operator=(const Particle&) = default;

    Particle(AtomicMass atomicMass, ChargeNumber chargeNumber, const LorentzVector& momentum);

    NucleiData GetNucleiData() const;

    AtomicMass GetAtomicMass() const;

    ChargeNumber GetChargeNumber() const;

    const LorentzVector& GetMomentum() const;

    FermiFloat GetExcitationEnergy() const;

    FermiFloat GetGroundStateMass() const;

    FermiFloat GetBindingEnergy() const;

    bool IsStable() const;

    void SetMomentum(const LorentzVector& momentum);

    ~Particle() = default;

  private:
    void CalculateExcitationEnergy();

    AtomicMass atomicMass_;
    ChargeNumber chargeNumber_;
    LorentzVector momentum_;

    FermiFloat groundStateMass_ = 0;
    FermiFloat excitationEnergy_ = 0;
  };

  std::ostream& operator<<(std::ostream&, const Particle&);

} // namespace fermi

#endif // FERMIBREAKUP_PARTICLE_H
