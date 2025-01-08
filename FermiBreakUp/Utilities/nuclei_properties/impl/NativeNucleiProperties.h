//
// Created by Artem Novikov on 09.03.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESNATIVENUCLEIPROPERTIESH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESNATIVENUCLEIPROPERTIESH_

#include "utilities/nuclei_properties/VNucleiProperties.h"

namespace properties {

  class NativeNucleiProperties : public VNucleiProperties {
  public:
    [[nodiscard]] FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const override final;

    [[nodiscard]] bool IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const override final;

  private:
    static FermiFloat AtomicWeight(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static FermiFloat NuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static FermiFloat BindingEnergy(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static bool IsInvalidNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static const FermiFloat protonMass;
    static const FermiFloat neutronMass;
    static const FermiFloat deuteronMass;
    static const FermiFloat tritonMass;
    static const FermiFloat alphaMass;
    static const FermiFloat He3Mass;
  };

} // namespace properties

#endif //FERMIBREAKUPMYFERMIBREAKUPUTILITIESNATIVENUCLEIPROPERTIESH_
