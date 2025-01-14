//
// Created by Artem Novikov on 18.02.2024.
//

#ifndef FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_FASTNUCLEIPROPERTIES_H
#define FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_FASTNUCLEIPROPERTIES_H

#include <vector>

#include "util/DataTypes.h"
#include "util/nuclei_properties/VNucleiProperties.h"

namespace fermi {
  class FastNucleiProperties : public VNucleiProperties {
  public:
    FastNucleiProperties();

    template <typename data_source>
    FastNucleiProperties(const data_source& dataSource);

    template <typename Iter>
    FastNucleiProperties(Iter begin, Iter end);

    [[nodiscard]] FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const override;

    [[nodiscard]] bool IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const override;

    void AddStableNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiFloat mass);

    void AddStableNuclei(NucleiData nucleiData, FermiFloat mass);

    ~FastNucleiProperties() = default;

  private:
    struct MassData {
      FermiFloat mass;

      bool isStable = false; // value was added via AddMass, it is considered stable

      bool isCached = false; // value has been calculated earlier
    };

    [[nodiscard]] static size_t GetSlot(AtomicMass atomicMass, ChargeNumber chargeNumber);

    mutable std::vector<MassData> nucleiMasses_;
  };

  template <typename data_source>
  FastNucleiProperties::FastNucleiProperties(const data_source& dataSource)
    : FastNucleiProperties(dataSource.begin(), dataSource.end())
  {
  }

  template <typename Iter>
  FastNucleiProperties::FastNucleiProperties(Iter begin, Iter end) {
    static_assert(std::is_same_v<typename Iter::value_type, std::pair<const NucleiData, FermiFloat>>, "invalid iterator");
    for (auto it = begin; it != end; ++it) {
      AddStableNuclei(it->first, it->second);
    }
  }

} // namespace fermi

#endif // FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_FASTNUCLEIPROPERTIES_H
