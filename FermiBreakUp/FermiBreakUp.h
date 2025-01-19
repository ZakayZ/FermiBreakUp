//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_FERMIBREAKUP_H
#define FERMIBREAKUP_FERMIBREAKUP_H

#include <memory>

#include "Split.h"
#include "util/Particle.h"

namespace fermi {

  class FermiBreakUp {
  public:
    using SplitCache = VCache<NucleiData, FragmentSplits>;

    FermiBreakUp() = default;

    FermiBreakUp(std::unique_ptr<SplitCache>&& cache);

    std::vector<Particle> BreakItUp(const Particle& nucleus) const;

  private:
    std::unique_ptr<SplitCache> cache_ = nullptr;
  };

} // namespace fermi

#endif // FERMIBREAKUP_FERMIBREAKUP_H
