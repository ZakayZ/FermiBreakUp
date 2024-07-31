//
// Created by Artem Novikov on 24.05.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_CACHEDFERMICONFIGURATIONS_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_CACHEDFERMICONFIGURATIONS_H_

#include "Split.h"
#include "VConfigurations.h"

namespace fermi {

  class CachedConfigurations : public VConfigurations {
  public:
    CachedConfigurations() = default;

    CachedConfigurations(NucleiData nuclei_data, FermiFloat total_energy);

    VConfigurations& GenerateSplits(NucleiData nuclei_data, FermiFloat total_energy) override;

    std::optional<FragmentVector> ChooseSplit() override;

    [[nodiscard]] std::unique_ptr<VConfigurations> Clone() const override;

  private:
    std::vector<size_t> configurations_;
    std::vector<FermiFloat> weights_;

    std::vector<FragmentVector> cached_configurations_;
    NucleiData last_nuclei_{};
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_CACHEDFERMICONFIGURATIONS_H_
