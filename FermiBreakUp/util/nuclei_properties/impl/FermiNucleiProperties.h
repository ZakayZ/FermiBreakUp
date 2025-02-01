//
// Created by Artem Novikov on 18.02.2024.
//

#ifndef FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_FermiNucleiProperties_H
#define FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_FermiNucleiProperties_H

#include <vector>

#include "util/DataTypes.h"
#include "util/nuclei_properties/VNucleiProperties.h"

namespace fbu {
  class FermiNucleiProperties : public VNucleiProperties {
  public:
    FermiNucleiProperties();

    template <typename data_source>
    FermiNucleiProperties(const data_source& dataSource);

    template <typename Iter>
    FermiNucleiProperties(Iter begin, Iter end);

    [[nodiscard]] FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const override;

    [[nodiscard]] bool IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const override;

    void AddStableNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiFloat mass);

    void AddStableNuclei(NucleiData nucleiData, FermiFloat mass);

    ~FermiNucleiProperties() = default;

  private:
    struct MassData {
      FermiFloat mass;

      bool isStable = false; // value was added via AddMass, it is considered stable

      bool isCached = false; // value has been calculated earlier
    };

    mutable std::vector<MassData> nucleiMasses_;
  };

  template <typename data_source>
  FermiNucleiProperties::FermiNucleiProperties(const data_source& dataSource)
    : FermiNucleiProperties(dataSource.begin(), dataSource.end())
  {
  }

  template <typename Iter>
  FermiNucleiProperties::FermiNucleiProperties(Iter begin, Iter end) {
    static_assert(std::is_same_v<typename Iter::value_type, std::pair<const NucleiData, FermiFloat>>, "invalid iterator");
    for (auto it = begin; it != end; ++it) {
      AddStableNuclei(it->first, it->second);
    }
  }

} // namespace fbu

#endif // FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_FermiNucleiProperties_H
