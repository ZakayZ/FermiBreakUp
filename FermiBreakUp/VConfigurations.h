//
// Created by Artem Novikov on 21.05.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_VFERMICONFIGURATIONS_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_VFERMICONFIGURATIONS_H_

#include <optional>
#include <memory>

#include "Utilities/DataTypes.h"
#include "Split.h"

namespace fermi {

  class VConfigurations {
  public:
    virtual VConfigurations& GenerateSplits(NucleiData nuclei_data, FermiFloat total_energy) = 0;

    virtual std::optional<FragmentVector> ChooseSplit() = 0;

    virtual std::unique_ptr<VConfigurations> Clone() const = 0;

    virtual ~VConfigurations() = default;
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_VFERMICONFIGURATIONS_H_
