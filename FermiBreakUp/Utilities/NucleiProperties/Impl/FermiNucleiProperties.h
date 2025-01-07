//
// Created by Artem Novikov on 09.03.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESFERMINUCLEIPROPERTIESH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESFERMINUCLEIPROPERTIESH_

#include <map>
#include <memory>

#include "Utilities/NucleiProperties/VNucleiProperties.h"

namespace properties {

  class FermiNucleiProperties : public VNucleiProperties {
  public:
    FermiNucleiProperties();

    template <typename DataSource>
    FermiNucleiProperties(const DataSource& dataSource);

    template <typename Iter>
    FermiNucleiProperties(Iter begin, Iter end);

    [[nodiscard]] FermiFloat GetNuclearMass(MassNumber massNumber, ChargeNumber chargeNumber) const override final;

    [[nodiscard]] bool IsStable(MassNumber massNumber, ChargeNumber chargeNumber) const override final;

    void AddMass(MassNumber massNumber, ChargeNumber chargeNumber, FermiFloat mass);

    void AddMass(NucleiData nucleiData, FermiFloat mass);

  private:
    std::map<NucleiData, FermiFloat> nucleiMass_;
  };

  template <typename DataSource>
  FermiNucleiProperties::FermiNucleiProperties(const DataSource& dataSource)
      : FermiNucleiProperties(dataSource.begin(), dataSource.end()) {}

  template <typename Iter>
  FermiNucleiProperties::FermiNucleiProperties(Iter begin, Iter end) {
    static_assert(std::is_same_v<typename Iter::value_type, std::pair<const NucleiData, FermiFloat>>, "invalid iterator");
    for (auto it = begin; it != end; ++it) {
      AddMass(it->first, it->second);
    }
  }

} // namespace properties

#endif //FERMIBREAKUPMYFERMIBREAKUPUTILITIESFERMINUCLEIPROPERTIESH_
