//
// Created by Artem Novikov on 18.02.2024.
//

#ifndef HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESIMPLFERMIFASTNUCLEIPROPERTIESH_
#define HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESIMPLFERMIFASTNUCLEIPROPERTIESH_

#include <vector>

#include "Utilities/DataTypes.h"
#include "Utilities/NucleiProperties/VNucleiProperties.h"

namespace properties {

  class FastNucleiProperties : public VNucleiProperties {
  public:
    FastNucleiProperties();

    template <typename DataSource>
    FastNucleiProperties(const DataSource& dataSource);

    template <typename Iter>
    FastNucleiProperties(Iter begin, Iter end);

    [[nodiscard]] FermiFloat GetNuclearMass(MassNumber massNumber, ChargeNumber chargeNumber) const override final;

    [[nodiscard]] FermiFloat GetNuclearMass(MassNumber massNumber, ChargeNumber chargeNumber);

    [[nodiscard]] bool IsStable(MassNumber massNumber, ChargeNumber chargeNumber) const override final;

    void AddMass(MassNumber massNumber, ChargeNumber chargeNumber, FermiFloat mass);

    void AddMass(NucleiData nucleiData, FermiFloat mass);

    ~FastNucleiProperties() = default;

  private:
    struct MassData {
      FermiFloat mass;
      bool isValid = false;
      bool isCached = false;
    };

    [[nodiscard]] static size_t GetSlot(MassNumber massNumber, ChargeNumber chargeNumber);

    std::vector<MassData> nucleiMasses_;
  };

  template <typename DataSource>
  FastNucleiProperties::FastNucleiProperties(const DataSource& dataSource)
      : FastNucleiProperties(dataSource.begin(), dataSource.end()) {}

  template <typename Iter>
  FastNucleiProperties::FastNucleiProperties(Iter begin, Iter end) {
    static_assert(std::is_same_v<typename Iter::value_type, std::pair<const NucleiData, FermiFloat>>, "invalid iterator");
    for (auto it = begin; it != end; ++it) {
      AddMass(it->first, it->second);
    }
  }

} // namespace properties

#endif //HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESIMPLFERMIFASTNUCLEIPROPERTIESH_
