//
// Created by Artem Novikov on 09.03.2023.
//

#ifndef FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_NATIVENUCLEIPROPERTIES_H
#define FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_NATIVENUCLEIPROPERTIES_H

#include "util/nuclei_properties/VNucleiProperties.h"

namespace properties {

  class NativeNucleiProperties : public VNucleiProperties {
  public:
    [[nodiscard]] FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const override;

    [[nodiscard]] bool IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const override;

  private:
    static FermiFloat AtomicWeight(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static FermiFloat NuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static FermiFloat BindingEnergy(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static bool IsInvalidNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber);
  };

} // namespace properties

#endif // FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_NATIVENUCLEIPROPERTIES_H
