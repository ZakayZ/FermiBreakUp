//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESTABLEVALUESNUCLEIPROPERTIESTABLEH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESTABLEVALUESNUCLEIPROPERTIESTABLEH_

#include <vector>

#include "Utilities/DataTypes.h"

namespace properties {

  class NucleiPropertiesTable {
  public:
    NucleiPropertiesTable();

    FermiFloat GetNuclearMass(MassNumber massNumber, ChargeNumber chargeNumber) const;

    bool ContainsParticle(MassNumber massNumber, ChargeNumber chargeNumber) const;

    FermiUInt GetMaxMass() const;

    FermiUInt GetMaxCharge() const;

    ~NucleiPropertiesTable() = default;

  private:
    static FermiFloat ElectronicBindingEnergy(ChargeNumber chargeNumber);

    size_t GetIndex(MassNumber massNumber, ChargeNumber chargeNumber) const;

    FermiFloat GetAtomicMass(MassNumber massNumber, ChargeNumber chargeNumber) const;

    bool VerifyNuclei(MassNumber massNumber, ChargeNumber chargeNumber) const;

    static const MassNumber MaxMassNumber;

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

#endif //FERMIBREAKUPMYFERMIBREAKUPUTILITIESTABLEVALUESNUCLEIPROPERTIESTABLEH_
