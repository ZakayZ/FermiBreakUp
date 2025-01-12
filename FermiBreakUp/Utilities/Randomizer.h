//
// Created by Artem Novikov on 19.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESRANDOMIZERH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESRANDOMIZERH_

#include <vector>
#include <algorithm>

#include "DataTypes.h"

class Randomizer {
public:
  static FermiFloat uniform_real_distribution();

  static FermiFloat normal_distribution(FermiFloat mean = 0, FermiFloat deviation = 1);

  static ParticleMomentum IsotropicVector(FermiFloat magnitude = 1);

  static std::vector<FermiFloat> ProbabilityDistribution(size_t pointCount);
};

#endif // FERMIBREAKUPMYFERMIBREAKUPUTILITIESRANDOMIZERH_
