//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_FERMIBREAKUP_H
#define FERMIBREAKUP_FERMIBREAKUP_H

#include <memory>

#include "Splitter.h"
#include "util/Particle.h"

namespace fbu {

  class FermiBreakUp {
  public:
    using SplitCache = VCache<NucleiData, FragmentSplits>;

    FermiBreakUp() = default;

    FermiBreakUp(std::unique_ptr<SplitCache>&& cache);

    std::vector<Particle> BreakItUp(const Particle& nucleus) const;

  private:
    std::vector<Particle> SelectSplit(const Particle& particle, const FragmentSplits& splits) const;

    mutable std::unique_ptr<SplitCache> cache_ = nullptr;

    // improve performance, reusing allocated memory
    mutable std::vector<FermiFloat> weights_;
    mutable FragmentSplits splits_;
  };

} // namespace fbu

#endif // FERMIBREAKUP_FERMIBREAKUP_H
