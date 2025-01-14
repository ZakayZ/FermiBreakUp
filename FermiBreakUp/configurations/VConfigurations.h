//
// Created by Artem Novikov on 21.05.2023.
//

#ifndef FERMIBREAKUP_VCONFIGURATIONS_H
#define FERMIBREAKUP_VCONFIGURATIONS_H

#include <optional>
#include <memory>

#include "util/DataTypes.h"
#include "fragment_pool/fragments/Fragment.h"

namespace fermi {
  class VConfigurations {
  public:
    virtual VConfigurations& GenerateSplits(const NucleiData nucleiData, const FermiFloat totalEnergy) = 0;

    virtual std::optional<FragmentVector> ChooseSplit() = 0;

    // useful for tests
    virtual std::unique_ptr<VConfigurations> Clone() const = 0;

    virtual ~VConfigurations() = default;
  };

} // namespace fermi

#endif // FERMIBREAKUP_VCONFIGURATIONS_H
