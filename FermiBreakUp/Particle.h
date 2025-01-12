//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPPARTICLEH_
#define FERMIBREAKUPMYFERMIBREAKUPPARTICLEH_

#include <vector>

#include "utilities/DataTypes.h"

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

    void SetMassAndCharge(AtomicMass atomicMass, ChargeNumber chargeNumber);

    void SetMomentum(const LorentzVector& momentum);

    ~Particle() = default;

  private:
    void CalculateExcitationEnergy();

    void CalculateGroundStateMass();

    AtomicMass atomicMass_;
    ChargeNumber chargeNumber_;
    LorentzVector momentum_;

    FermiFloat excitationEnergy_ = 0;
    FermiFloat groundStateMass_ = 0;
  };

  std::ostream& operator<<(std::ostream&, const Particle&);

}  // namespace fermi

#endif // FERMIBREAKUPMYFERMIBREAKUPPARTICLEH_
