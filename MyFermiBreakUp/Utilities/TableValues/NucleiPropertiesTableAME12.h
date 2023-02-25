//
// Created by Artem Novikov on 26.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_TABLEVALUES_NUCLEIPROPERTIESTABLEAME12_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_TABLEVALUES_NUCLEIPROPERTIESTABLEAME12_H_

#include <vector>

#include "DataTypes.h"

class NucleiPropertiesTableAME12 {
 public:
  NucleiPropertiesTableAME12();

  FermiFloat GetNuclearMass(uint32_t mass_number, uint32_t charge_number) const;

  FermiFloat GetMassExcess(uint32_t mass_number, uint32_t charge_number) const;

  FermiFloat GetBindingEnergy(uint32_t mass_number, uint32_t charge_number) const;

  FermiFloat GetBetaDecayEnergy(uint32_t mass_number, uint32_t charge_number) const;

  bool ContainsParticle(uint32_t mass_number, uint32_t charge_number) const;

  ~NucleiPropertiesTableAME12() = default;

 private:
  size_t GetIndex(uint32_t mass_number, uint32_t charge_number) const;

  FermiFloat GetAtomicMass(uint32_t mass_number, uint32_t charge_number) const;

  bool VerifyNuclei(uint32_t mass_number, uint32_t charge_number) const;

  static const size_t MaxMassNumber;

  static const size_t MaxChargeNumber;

  static const size_t ParticleCount;

  static const std::vector<FermiFloat> MassExcess;

  static const std::vector<FermiFloat> BetaEnergy;

  static const std::vector<size_t> IndexCharge;

  static const std::vector<size_t> IndexMass;

  static const size_t ShortTableCount;

  static const std::vector<size_t> ShortTable;

  static std::vector<FermiFloat>* electron_mass_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_TABLEVALUES_NUCLEIPROPERTIESTABLEAME12_H_
