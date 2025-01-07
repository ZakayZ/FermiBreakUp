//
// Created by Artem Novikov on 09.03.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESNATIVENUCLEIPROPERTIESH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESNATIVENUCLEIPROPERTIESH_

#include "Utilities/NucleiProperties/VNucleiProperties.h"

namespace properties {

  class NativeNucleiProperties : public VNucleiProperties {
  public:
    [[nodiscard]] FermiFloat GetNuclearMass(MassNumber massNumber, ChargeNumber chargeNumber) const override final;

    [[nodiscard]] bool IsStable(MassNumber massNumber, ChargeNumber chargeNumber) const override final;

  private:
    static FermiFloat AtomicMass(MassNumber massNumber, ChargeNumber chargeNumber);

    static FermiFloat NuclearMass(MassNumber massNumber, ChargeNumber chargeNumber);

    static FermiFloat BindingEnergy(MassNumber massNumber, ChargeNumber chargeNumber);

    static bool IsInvalidNuclei(MassNumber massNumber, ChargeNumber chargeNumber);

    static const FermiFloat protonMass;
    static const FermiFloat neutronMass;
    static const FermiFloat deuteronMass;
    static const FermiFloat tritonMass;
    static const FermiFloat alphaMass;
    static const FermiFloat He3Mass;
  };

} // namespace properties

#endif //FERMIBREAKUPMYFERMIBREAKUPUTILITIESNATIVENUCLEIPROPERTIESH_
