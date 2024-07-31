//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_Fragment_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_Fragment_H_

#include <vector>

#include "Utilities/DataTypes.h"
#include "Particle.h"

namespace fermi {

  class Fragment {
  public:
    Fragment(MassNumber mass_number, ChargeNumber charge_number, int polarization, FermiFloat excitation_energy);

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
    MassNumber mass_number_;  /// A
    ChargeNumber charge_number_;  /// Z
    int32_t polarization;
    FermiFloat excitation_energy_;
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_Fragment_H_
