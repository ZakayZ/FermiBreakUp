//
// Created by Artem Novikov on 18.02.2024.
//

#ifndef FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_FermiNucleiProperties_H
#define FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_FermiNucleiProperties_H

#include <vector>

#include "FermiBreakUp/util/DataTypes.h"
#include "FermiBreakUp/nuclei_properties/VNucleiProperties.h"

namespace fbu {
  class FermiNucleiProperties : public VNucleiProperties {
  public:
    FermiNucleiProperties();

    template <typename DataSource>
    FermiNucleiProperties(const DataSource& dataSource)
      : FermiNucleiProperties(dataSource.begin(), dataSource.end())
    {
    }

    template <typename Iter>
    FermiNucleiProperties(Iter begin, Iter end) {
      static_assert(
        std::is_same_v<typename Iter::value_type, std::pair<const NucleiData, FermiFloat>>,
        "invalid iterator");
      for (auto it = begin; it != end; ++it) {
        AddNuclei(it->first, it->second);
      }
    }

    FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const override;

    bool IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const override;

    void AddNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiFloat mass, bool isStable = true);

    void AddNuclei(NucleiData nucleiData, FermiFloat mass, bool isStable = true);

  private:
    struct MassData {
      FermiFloat mass;

      bool isStable = false; // is nuclei considered to be stable

      bool isCached = false; // value has been calculated earlier
    };

    mutable std::vector<MassData> nucleiMasses_;
  };
} // namespace fbu

#endif // FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_FermiNucleiProperties_H
