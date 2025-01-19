//
// Created by Artem Novikov on 09.03.2023.
//

#ifndef FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_NATIVENUCLEIPROPERTIES_H
#define FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_NATIVENUCLEIPROPERTIES_H

#include "util/nuclei_properties/VNucleiProperties.h"

namespace fermi {

  class NativeNucleiProperties : public VNucleiProperties {
  public:
    [[nodiscard]] FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const override;

    [[nodiscard]] bool IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const override;

  private:
    static FermiFloat AtomicWeight(AtomicMass atomicMass, ChargeNumber chargeNumber);

    static FermiFloat NuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber);
  };

} // namespace fermi

#endif // FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_NATIVENUCLEIPROPERTIES_H
