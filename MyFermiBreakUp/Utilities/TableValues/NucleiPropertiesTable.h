//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_TABLEVALUES_NUCLEIPROPERTIESTABLE_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_TABLEVALUES_NUCLEIPROPERTIESTABLE_H_

#include <vector>

#include "DataTypes.h"

class NucleiPropertiesTable {
 public:
  NucleiPropertiesTable();

  FermiFloat GetNuclearMass(uint32_t mass_number, uint32_t charge_number) const;

  bool ContainsParticle(uint32_t mass_number, uint32_t charge_number) const;

  ~NucleiPropertiesTable() = default;

 private:
  static FermiFloat ElectronicBindingEnergy(uint32_t charge_number);

  size_t GetIndex(uint32_t mass_number, uint32_t charge_number) const;

  FermiFloat GetAtomicMass(uint32_t mass_number, uint32_t charge_number) const;

  bool VerifyNuclei(uint32_t mass_number, uint32_t charge_number) const;


  static const size_t ParticleCount;

  static const std::vector<FermiFloat> AtomicMassExcess;

  static const std::vector<size_t> IndexCharge;

  static const std::vector<size_t> IndexMass;

  static const size_t ShortTableCount;

  static const std::vector<size_t> ShortTable;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_TABLEVALUES_NUCLEIPROPERTIESTABLE_H_
