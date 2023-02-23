//
// Created by Artem Novikov on 19.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_RANDOMIZER_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_RANDOMIZER_H_

#include <vector>

#include "DataTypes.h"

class Randomizer {
 public:
  static FermiFloat UniformRealDistribution();

  static FermiFloat NormalDistribution(FermiFloat mean, FermiFloat deviation);

  static ParticleMomentum IsotropicVector(FermiFloat Magnitude = 1);

  static std::vector<FermiFloat> ProbabilityDistribution(size_t point_count);
 private:
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_RANDOMIZER_H_
