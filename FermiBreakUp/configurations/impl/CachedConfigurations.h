//
// Created by Artem Novikov on 24.05.2023.
//

#ifndef FERMIBREAKUP_CONFIGURATIONS_CACHEDCONFIGURATIONS_H
#define FERMIBREAKUP_CONFIGURATIONS_CACHEDCONFIGURATIONS_H

#include "configurations/VConfigurations.h"

namespace fermi {

  class CachedConfigurations : public VConfigurations {
  public:
    CachedConfigurations() = default;

    CachedConfigurations(const NucleiData nucleiData, const FermiFloat totalEnergy);

    VConfigurations& GenerateSplits(const NucleiData nucleiData, const FermiFloat totalEnergy) override;

    std::optional<FragmentVector> ChooseSplit() override;

    [[nodiscard]] std::unique_ptr<VConfigurations> Clone() const override;

  private:
    std::vector<size_t> configurations_;
    std::vector<FermiFloat> weights_;

    std::vector<FragmentVector> cachedConfigurations_;
    NucleiData lastNuclei_{};
  };

} // namespace fermi

#endif // FERMIBREAKUP_CONFIGURATIONS_CACHEDCONFIGURATIONS_H
