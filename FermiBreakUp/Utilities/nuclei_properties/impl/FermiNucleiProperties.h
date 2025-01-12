//
// Created by Artem Novikov on 09.03.2023.
//

#ifndef FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_FERMINUCLEIPROPERTIES_H
#define FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_FERMINUCLEIPROPERTIES_H

#include <map>
#include <memory>

#include "utilities/nuclei_properties/VNucleiProperties.h"

namespace properties {

  class FermiNucleiProperties : public VNucleiProperties {
  public:
    FermiNucleiProperties();

    template <typename data_source>
    FermiNucleiProperties(const data_source& dataSource);

    template <typename Iter>
    FermiNucleiProperties(Iter begin, Iter end);

    [[nodiscard]] FermiFloat GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const override final;

    [[nodiscard]] bool IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const override final;

    void AddMass(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiFloat mass);

    void AddMass(NucleiData nucleiData, FermiFloat mass);

  private:
    std::map<NucleiData, FermiFloat> nucleiMass_;
  };

  template <typename data_source>
  FermiNucleiProperties::FermiNucleiProperties(const data_source& dataSource)
      : FermiNucleiProperties(dataSource.begin(), dataSource.end()) {}

  template <typename Iter>
  FermiNucleiProperties::FermiNucleiProperties(Iter begin, Iter end) {
    static_assert(std::is_same_v<typename Iter::value_type, std::pair<const NucleiData, FermiFloat>>, "invalid iterator");
    for (auto it = begin; it != end; ++it) {
      AddMass(it->first, it->second);
    }
  }

} // namespace properties

#endif // FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_IMPL_FERMINUCLEIPROPERTIES_H
