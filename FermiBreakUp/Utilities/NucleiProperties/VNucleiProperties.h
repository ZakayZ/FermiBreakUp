//
// Created by Artem Novikov on 09.03.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESVNUCLEIPROPERTIESH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESVNUCLEIPROPERTIESH_

#include "Utilities/DataTypes.h"

namespace properties {

  class VNucleiProperties {
  public:
    virtual FermiFloat GetNuclearMass(MassNumber massNumber, ChargeNumber chargeNumber) const = 0;

    virtual bool IsStable(MassNumber massNumber, ChargeNumber chargeNumber) const = 0;

    virtual ~VNucleiProperties() = 0;

  protected:
    static FermiFloat AtomicMass(MassNumber massNumber, ChargeNumber chargeNumber);

    static FermiFloat NuclearMass(MassNumber massNumber, ChargeNumber chargeNumber);

    static FermiFloat BindingEnergy(MassNumber massNumber, ChargeNumber chargeNumber);

    static void PrintInvalidNuclei(MassNumber massNumber, ChargeNumber chargeNumber);

    static bool IsInvalidNuclei(MassNumber massNumber, ChargeNumber chargeNumber);
  };

} // namespace properties

#endif //FERMIBREAKUPMYFERMIBREAKUPUTILITIESVNUCLEIPROPERTIESH_
