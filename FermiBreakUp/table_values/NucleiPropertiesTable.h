//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_TABLE_VALUES_NUCLEIPROPERTIESTABLE_H
#define FERMIBREAKUP_TABLE_VALUES_NUCLEIPROPERTIESTABLE_H

#include <array>

#include "util/DataTypes.h"

namespace fermi {

  class NucleiPropertiesTable {
  public:
    FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    bool ContainsParticle(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    FermiUInt GetMaxMass() const;

    FermiUInt GetMaxCharge() const;

    ~NucleiPropertiesTable() = default;

  private:
    static FermiFloat ElectronicBindingEnergy(ChargeNumber chargeNumber);

    size_t GetIndex(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    FermiFloat GetAtomicMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    bool VerifyNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    static constexpr AtomicMass MaxMassNumber = 339_m;
    static constexpr ChargeNumber MaxChargeNumber = 136_c;

    static constexpr size_t ParticleCount = 8979;
    static constexpr size_t ShortTableCount = 137;

    static const std::array<FermiFloat, ParticleCount> AtomicMassExcess;

    static const std::array<size_t, ParticleCount> IndexCharge;

    static const std::array<size_t, ParticleCount> IndexMass;

    static const std::array<size_t, ShortTableCount> ShortTable;
  };

  std::ostream& operator<<(std::ostream& out, const NucleiPropertiesTable& table);

} // namespace fermi

#endif // FERMIBREAKUP_TABLE_VALUES_NUCLEIPROPERTIESTABLE_H
