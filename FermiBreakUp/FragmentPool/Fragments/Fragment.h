//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSFragmentH_
#define FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSFragmentH_

#include <vector>

#include "Utilities/DataTypes.h"
#include "Particle.h"

namespace fermi {

  class Fragment {
  public:
    Fragment(MassNumber massNumber, ChargeNumber chargeNumber, int polarization, FermiFloat excitationEnergy);

    Fragment(const Fragment&) = delete;

    Fragment& operator=(const Fragment&) = delete;

    virtual ParticleVector GetFragments(const LorentzVector& momentum) const = 0;

    MassNumber GetA() const;

    MassNumber GetMassNumber() const;

    ChargeNumber GetZ() const;

    ChargeNumber GetChargeNumber() const;

    int32_t GetPolarization() const;

    FermiFloat GetExcitationEnergy() const;

    FermiFloat GetFragmentMass() const;

    FermiFloat GetTotalEnergy() const;

    virtual ~Fragment() = 0;

  protected:
    MassNumber massNumber_;  // A
    ChargeNumber chargeNumber_;  // Z
    int32_t polarization;
    FermiFloat excitationEnergy_;
  };

}  // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSFragmentH_
