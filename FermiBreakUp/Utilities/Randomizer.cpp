//
// Created by Artem Novikov on 19.02.2023.
//

#include <random>
#include <CLHEP/Units/PhysicalConstants.h>

#include "Randomizer.h"

FermiFloat Randomizer::uniform_real_distribution() {
  static std::random_device device;
  static std::mt19937 generator(device());
  static std::uniform_real_distribution<FermiFloat> distribution(0, 1);
  return distribution(generator);
}

FermiFloat Randomizer::normal_distribution(FermiFloat mean, FermiFloat deviation) {
  static std::random_device device;
  static std::mt19937 generator(device());
  static std::normal_distribution<FermiFloat> distribution(0, 1);
  return mean + distribution(generator) * deviation;
}

ParticleMomentum Randomizer::IsotropicVector(FermiFloat magnitude) {
  auto cos = 1.0 - 2.0 * uniform_real_distribution();
  auto sin = std::sqrt(1.0 - std::pow(cos, 2));
  auto phi = CLHEP::twopi * uniform_real_distribution();
  ParticleMomentum momentum(magnitude * std::cos(phi) * sin,
                            magnitude * std::sin(phi) * sin,
                            magnitude * cos);
//  ParticleMomentum momentum(normal_distribution(), normal_distribution(), normal_distribution());
//  momentum = momentum * (magnitude) / momentum.mag();
  return momentum;
}

std::vector<FermiFloat> Randomizer::ProbabilityDistribution(size_t pointCount) {
  // Sample uniform random numbers in increasing order
  std::vector<FermiFloat> probabilityDistribution;
  probabilityDistribution.reserve(pointCount);

  probabilityDistribution.push_back(0);
  std::generate_n(std::back_inserter(probabilityDistribution), pointCount - 2, Randomizer::uniform_real_distribution);
  probabilityDistribution.push_back(1);

  std::sort(probabilityDistribution.begin(), probabilityDistribution.end());

  return probabilityDistribution;
}
