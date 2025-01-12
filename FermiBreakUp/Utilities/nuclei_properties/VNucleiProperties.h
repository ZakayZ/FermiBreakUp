//
// Created by Artem Novikov on 09.03.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESVNUCLEIPROPERTIESH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESVNUCLEIPROPERTIESH_

#include "utilities/DataTypes.h"

namespace properties {

  class VNucleiProperties {
  public:
    virtual FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const = 0;

    virtual bool IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const = 0;

    virtual ~VNucleiProperties() = 0;

  protected:
    static FermiFloat AtomicWeight(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static FermiFloat NuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static FermiFloat BindingEnergy(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static void PrintInvalidNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static bool IsInvalidNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber);
  };

} // namespace properties

#endif // FERMIBREAKUPMYFERMIBREAKUPUTILITIESVNUCLEIPROPERTIESH_
