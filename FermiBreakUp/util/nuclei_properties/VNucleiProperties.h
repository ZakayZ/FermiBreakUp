//
// Created by Artem Novikov on 09.03.2023.
//

#ifndef FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_VNUCLEIPROPERTIES_H
#define FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_VNUCLEIPROPERTIES_H

#include "util/DataTypes.h"

namespace fermi {

  class VNucleiProperties {
  public:
    virtual FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const = 0;

    virtual bool IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const = 0;

    virtual ~VNucleiProperties() = default;

  protected:
    static FermiFloat AtomicWeight(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static FermiFloat NuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static FermiFloat BindingEnergy(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static void PrintInvalidNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static bool IsInvalidNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber);
  };

} // namespace fermi

#endif // FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_VNUCLEIPROPERTIES_H
