//
// Created by Artem Novikov on 19.02.2023.
//

#include <random>
#include <CLHEP/Units/PhysicalConstants.h>

#include "Randomizer.h"

FermiFloat Randomizer::UniformRealDistribution() {
  static std::random_device device;
  static std::mt19937 generator(device());
  static std::uniform_real_distribution<FermiFloat> distribution(0, 1);
  return distribution(generator);
}

FermiFloat Randomizer::NormalDistribution(FermiFloat mean, FermiFloat deviation) {
  static std::random_device device;
  static std::mt19937 generator(device());
  static std::normal_distribution<FermiFloat> distribution(0, 1);
  return mean + distribution(generator) * deviation;
}

ParticleMomentum Randomizer::IsotropicVector(FermiFloat Magnitude) {
  auto cos = 1.0 - 2.0 * UniformRealDistribution();
  auto sin = std::sqrt(1.0 - std::pow(cos, 2));
  auto phi = CLHEP::twopi * UniformRealDistribution();
  ParticleMomentum momentum(Magnitude * std::cos(phi) * sin,
                            Magnitude * std::sin(phi) * sin,
                            Magnitude * cos);
  return momentum;
}
