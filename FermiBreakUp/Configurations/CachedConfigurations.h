//
// Created by Artem Novikov on 24.05.2023.
//

#ifndef FERMIBREAKUP_CONFIGURATIONS_CACHEDCONFIGURATIONS_H
#define FERMIBREAKUP_CONFIGURATIONS_CACHEDCONFIGURATIONS_H

#include "Split.h"
#include "VConfigurations.h"

namespace fermi {

  class CachedConfigurations : public VConfigurations {
  public:
    CachedConfigurations() = default;

    CachedConfigurations(NucleiData nucleiData, FermiFloat totalEnergy);

    VConfigurations& GenerateSplits(NucleiData nucleiData, FermiFloat totalEnergy) override;

    std::optional<FragmentVector> ChooseSplit() override;

    [[nodiscard]] std::unique_ptr<VConfigurations> Clone() const override;

  private:
    std::vector<size_t> configurations_;
    std::vector<FermiFloat> weights_;

    std::vector<FragmentVector> cachedConfigurations_;
    NucleiData lastNuclei_{};
  };

}  // namespace fermi

#endif // FERMIBREAKUP_CONFIGURATIONS_CACHEDCONFIGURATIONS_H
