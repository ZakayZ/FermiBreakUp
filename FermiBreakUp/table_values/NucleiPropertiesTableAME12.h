//
// Created by Artem Novikov on 26.02.2023.
//

#ifndef FERMIBREAKUP_TABLE_VALUES_NUCLEIPROPERTIESTABLEAME12_H
#define FERMIBREAKUP_TABLE_VALUES_NUCLEIPROPERTIESTABLEAME12_H

#include <vector>
#include <array>
#include <optional>

#include "util/DataTypes.h"

namespace fermi {

  class NucleiPropertiesTableAME12 {
  public:
    NucleiPropertiesTableAME12();

    FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    FermiFloat GetMassExcess(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    FermiFloat GetBindingEnergy(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    FermiFloat GetBetaDecayEnergy(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    bool ContainsParticle(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    FermiUInt GetMaxMass() const;

    FermiUInt GetMaxCharge() const;

    ~NucleiPropertiesTableAME12() = default;

  private:
    size_t GetIndex(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    FermiFloat GetAtomicMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    bool VerifyNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    static constexpr AtomicMass MaxMassNumber = 295_m;
    static constexpr ChargeNumber MaxChargeNumber = 120_c;

    static constexpr size_t ParticleCount = 3353;
    static constexpr size_t ShortTableCount = FermiUInt(MaxMassNumber);

    static const std::array<FermiFloat, ParticleCount> MassExcess;

    static const std::array<FermiFloat, ParticleCount> BetaEnergy;

    static const std::array<size_t, ParticleCount> IndexCharge;

    static const std::array<size_t, ParticleCount> IndexMass;

    static const std::array<size_t, ShortTableCount> ShortTable;

    static inline std::optional<std::vector<FermiFloat>> electronMass_ = std::nullopt;
  };

} // namespace fermi

namespace std {
  ostream& operator<<(ostream& out, const ::fermi::NucleiPropertiesTableAME12& table);
} // namespace std

#endif // FERMIBREAKUP_TABLE_VALUES_NUCLEIPROPERTIESTABLEAME12_H
