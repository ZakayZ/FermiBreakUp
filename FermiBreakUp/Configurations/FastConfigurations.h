//
// Created by Artem Novikov on 18.02.2024.
//

#ifndef FERMIBREAKUP_CONFIGURATIONS_FASTCONFIGURATIONS_H
#define FERMIBREAKUP_CONFIGURATIONS_FASTCONFIGURATIONS_H

#include <unordered_map>

#include "Split.h"
#include "VConfigurations.h"

namespace fermi {

  class FastConfigurations : public VConfigurations {
  public:
    FastConfigurations() = default;

    FastConfigurations(NucleiData nucleiData, FermiFloat totalEnergy);

    VConfigurations& GenerateSplits(NucleiData nucleiData, FermiFloat totalEnergy) override;

    std::optional<FragmentVector> ChooseSplit() override;

    [[nodiscard]] std::unique_ptr<VConfigurations> Clone() const override;

  private:
    std::vector<size_t> configurations_;
    std::vector<FermiFloat> weights_;

    std::unordered_map<NucleiData, std::vector<FragmentVector>> cachedConfigurations_;
    NucleiData lastNuclei_{};
  };

}  // namespace fermi

#endif // FERMIBREAKUP_CONFIGURATIONS_FASTCONFIGURATIONS_H
