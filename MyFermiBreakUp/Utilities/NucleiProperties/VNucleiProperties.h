//
// Created by Artem Novikov on 09.03.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_VNUCLEIPROPERTIES_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_VNUCLEIPROPERTIES_H_

#include "DataTypes.h"

class VNucleiProperties {
 public:
  virtual FermiFloat GetNuclearMass(MassNumber mass_number, ChargeNumber charge_number) const = 0;

  virtual bool IsStable(MassNumber mass_number, ChargeNumber charge_number) const = 0;

  virtual ~VNucleiProperties() = 0;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_VNUCLEIPROPERTIES_H_
