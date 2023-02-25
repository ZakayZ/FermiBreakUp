//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_H_

#include "DataTypes.h"

class NucleiProperties {
 public:
  static FermiFloat GetNuclearMass(uint32_t mass_number, uint32_t charge_number);

  static bool IsStable(uint32_t mass_number, uint32_t charge_number);

 private:
  static FermiFloat AtomicMass(FermiFloat mass_number, FermiFloat charge_number);

  static FermiFloat NuclearMass(FermiFloat mass_number, FermiFloat charge_number);

  static FermiFloat BindingEnergy(FermiFloat mass_number, FermiFloat charge_number);

  static bool IsInvalidNuclei(FermiFloat mass_number, FermiFloat charge_number);

  static const FermiFloat proton_mass;
  static const FermiFloat neutron_mass;
  static const FermiFloat deuteron_mass;
  static const FermiFloat triton_mass;
  static const FermiFloat alpha_mass;
  static const FermiFloat He3_mass;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_H_
