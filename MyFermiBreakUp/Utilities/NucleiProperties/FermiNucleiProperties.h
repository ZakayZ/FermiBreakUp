//
// Created by Artem Novikov on 09.03.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_FERMINUCLEIPROPERTIES_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_FERMINUCLEIPROPERTIES_H_

#include <map>

#include "VNucleiProperties.h"

class FermiNucleiProperties : public VNucleiProperties {
 public:
  FermiNucleiProperties();

  FermiFloat GetNuclearMass(MassNumber mass_number, ChargeNumber charge_number) const override;

  bool IsStable(MassNumber mass_number, ChargeNumber charge_number) const override;

 private:
  static std::map<NucleiData, FermiFloat>* nuclei_mass_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_FERMINUCLEIPROPERTIES_H_
