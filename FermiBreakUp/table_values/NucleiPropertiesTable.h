//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESTABLEVALUESNUCLEIPROPERTIESTABLEH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESTABLEVALUESNUCLEIPROPERTIESTABLEH_

#include <vector>

#include "utilities/DataTypes.h"

namespace properties {

  class NucleiPropertiesTable {
  public:
    NucleiPropertiesTable();

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

    static const AtomicMass MaxMassNumber;

    static const ChargeNumber MaxChargeNumber;

    static const size_t ParticleCount;

    static const std::vector<FermiFloat> AtomicMassExcess;

    static const std::vector<size_t> IndexCharge;

    static const std::vector<size_t> IndexMass;

    static const size_t ShortTableCount;

    static const std::vector<size_t> ShortTable;
  };

  std::ostream& operator<<(std::ostream& out, const NucleiPropertiesTable& table);

} // namespace properties

#endif // FERMIBREAKUPMYFERMIBREAKUPUTILITIESTABLEVALUESNUCLEIPROPERTIESTABLEH_
