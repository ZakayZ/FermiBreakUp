//
// Created by Artem Novikov on 26.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESTABLEVALUESNUCLEIPROPERTIESTABLEAME12H_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESTABLEVALUESNUCLEIPROPERTIESTABLEAME12H_

#include <vector>

#include "utilities/DataTypes.h"

namespace properties {

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

    static const AtomicMass MaxMassNumber;

    static const ChargeNumber MaxChargeNumber;

    static const size_t ParticleCount;

    static const std::vector<FermiFloat> MassExcess;

    static const std::vector<FermiFloat> BetaEnergy;

    static const std::vector<size_t> IndexCharge;

    static const std::vector<size_t> IndexMass;

    static const size_t ShortTableCount;

    static const std::vector<size_t> ShortTable;

    static std::vector<FermiFloat>* electronMass_;
  };

  std::ostream& operator<<(std::ostream& out, const NucleiPropertiesTableAME12& table);

} // namespace properties

#endif // FERMIBREAKUPMYFERMIBREAKUPUTILITIESTABLEVALUESNUCLEIPROPERTIESTABLEAME12H_
