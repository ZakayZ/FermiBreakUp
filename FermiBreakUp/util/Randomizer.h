//
// Created by Artem Novikov on 19.02.2023.
//

#ifndef FERMIBREAKUP_UTILITIES_RANDOMIZER_H
#define FERMIBREAKUP_UTILITIES_RANDOMIZER_H

#include <random>
#include <vector>

#include "DataTypes.h"

namespace fbu {

  class Randomizer {
  private:
    using RandomEngine = std::mt19937;

  public:
    static FermiFloat SampleUniform();

    static FermiFloat SampleNormal(FermiFloat mean = 0, FermiFloat deviation = 1);

    static ParticleMomentum IsotropicVector(FermiFloat magnitude = 1);

    static std::vector<FermiFloat> ProbabilityDistribution(size_t pointCount);

    static size_t SampleDistribution(const std::vector<FermiFloat>& weights);

    static void SetSeed(RandomEngine::result_type seed);

  private:
    static inline RandomEngine Engine_ = {};
  };

} // namespace fbu

#endif // FERMIBREAKUP_UTILITIES_RANDOMIZER_H
