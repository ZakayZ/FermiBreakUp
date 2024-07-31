//
// Created by Artem Novikov on 19.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FERMICONFIGURATIONS_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FERMICONFIGURATIONS_H_

#include <vector>

#include "Split.h"
#include "VConfigurations.h"

namespace fermi {

  class Configurations : public VConfigurations {
  public:
    Configurations() = default;

    Configurations(NucleiData nuclei_data, FermiFloat total_energy);

    fermi::VConfigurations& GenerateSplits(NucleiData nuclei_data, FermiFloat total_energy) override;

    std::optional<FragmentVector> ChooseSplit() override;

    [[nodiscard]] std::unique_ptr<fermi::VConfigurations> Clone() const override;

  private:
    std::vector<fermi::FragmentVector> configurations_;
    std::vector<FermiFloat> weights_;
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FERMICONFIGURATIONS_H_
