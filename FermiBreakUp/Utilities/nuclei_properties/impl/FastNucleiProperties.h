//
// Created by Artem Novikov on 18.02.2024.
//

#ifndef HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESIMPLFERMIFASTNUCLEIPROPERTIESH_
#define HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESIMPLFERMIFASTNUCLEIPROPERTIESH_

#include <vector>

#include "utilities/DataTypes.h"
#include "utilities/nuclei_properties/VNucleiProperties.h"

namespace properties {

  class FastNucleiProperties : public VNucleiProperties {
  public:
    FastNucleiProperties();

    template <typename data_source>
    FastNucleiProperties(const data_source& dataSource);

    template <typename Iter>
    FastNucleiProperties(Iter begin, Iter end);

    [[nodiscard]] FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const override final;

    [[nodiscard]] FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber);

    [[nodiscard]] bool IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const override final;

    void AddMass(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiFloat mass);

    void AddMass(NucleiData nucleiData, FermiFloat mass);

    ~FastNucleiProperties() = default;

  private:
    struct MassData {
      FermiFloat mass;
      bool isValid = false;
      bool isCached = false;
    };

    [[nodiscard]] static size_t GetSlot(AtomicMass atomicMass, ChargeNumber chargeNumber);

    std::vector<MassData> nucleiMasses_;
  };

  template <typename data_source>
  FastNucleiProperties::FastNucleiProperties(const data_source& dataSource)
      : FastNucleiProperties(dataSource.begin(), dataSource.end()) {}

  template <typename Iter>
  FastNucleiProperties::FastNucleiProperties(Iter begin, Iter end) {
    static_assert(std::is_same_v<typename Iter::value_type, std::pair<const NucleiData, FermiFloat>>, "invalid iterator");
    for (auto it = begin; it != end; ++it) {
      AddMass(it->first, it->second);
    }
  }

} // namespace properties

#endif // HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESIMPLFERMIFASTNUCLEIPROPERTIESH_
