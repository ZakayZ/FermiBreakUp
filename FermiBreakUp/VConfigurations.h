//
// Created by Artem Novikov on 21.05.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPVFERMICONFIGURATIONSH_
#define FERMIBREAKUPMYFERMIBREAKUPVFERMICONFIGURATIONSH_

#include <optional>
#include <memory>

#include "utilities/DataTypes.h"
#include "Split.h"

namespace fermi {

  class VConfigurations {
  public:
    virtual VConfigurations& GenerateSplits(NucleiData nucleiData, FermiFloat totalEnergy) = 0;

    virtual std::optional<FragmentVector> ChooseSplit() = 0;

    virtual std::unique_ptr<VConfigurations> Clone() const = 0;

    virtual ~VConfigurations() = default;
  };

}  // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPVFERMICONFIGURATIONSH_
