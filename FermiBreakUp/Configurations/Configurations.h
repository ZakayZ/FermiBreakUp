//
// Created by Artem Novikov on 19.02.2023.
//

#ifndef FERMIBREAKUP_CONFIGURATIONS_CONFIGURATIONS_H
#define FERMIBREAKUP_CONFIGURATIONS_CONFIGURATIONS_H

#include <vector>

#include "Split.h"
#include "VConfigurations.h"

namespace fermi {

  class Configurations : public VConfigurations {
  public:
    Configurations() = default;

    Configurations(NucleiData nucleiData, FermiFloat totalEnergy);

    fermi::VConfigurations& GenerateSplits(NucleiData nucleiData, FermiFloat totalEnergy) override;

    std::optional<FragmentVector> ChooseSplit() override;

    [[nodiscard]] std::unique_ptr<fermi::VConfigurations> Clone() const override;

  private:
    std::vector<fermi::FragmentVector> configurations_;
    std::vector<FermiFloat> weights_;
  };

}  // namespace fermi

#endif // FERMIBREAKUP_CONFIGURATIONS_CONFIGURATIONS_H
