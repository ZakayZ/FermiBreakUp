//
// Created by Artem Novikov on 19.02.2023.
//

#ifndef FERMIBREAKUP_UTILITIES_RANDOMIZER_H
#define FERMIBREAKUP_UTILITIES_RANDOMIZER_H

#include <vector>
#include <algorithm>

#include "DataTypes.h"

namespace fermi {

  class Randomizer {
  public:
    static FermiFloat SampleUniform();

    static FermiFloat SampleNormal(FermiFloat mean = 0, FermiFloat deviation = 1);

    static ParticleMomentum IsotropicVector(FermiFloat magnitude = 1);

    static std::vector<FermiFloat> ProbabilityDistribution(size_t pointCount);
  };

} // namespace fermi

#endif // FERMIBREAKUP_UTILITIES_RANDOMIZER_H
