//
// Created by Artem Novikov on 09.03.2023.
//

#ifndef FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_VNUCLEIPROPERTIES_H
#define FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_VNUCLEIPROPERTIES_H

#include "util/DataTypes.h"

namespace fbu {

  class VNucleiProperties {
  public:
    virtual FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const = 0;

    virtual bool IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const = 0;

    virtual ~VNucleiProperties() = default;
  };

} // namespace fbu

#endif // FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_VNUCLEIPROPERTIES_H
