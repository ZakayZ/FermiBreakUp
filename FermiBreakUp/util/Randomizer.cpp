//
// Created by Artem Novikov on 19.02.2023.
//

#include <numeric>
#include <random>
#include <CLHEP/Units/PhysicalConstants.h>

#include "Randomizer.h"
#include "Logger.h"

using namespace fermi;

FermiFloat Randomizer::SampleUniform() {
  static std::uniform_real_distribution<FermiFloat> distribution(0., 1.);
  return distribution(Engine_);
}

FermiFloat Randomizer::SampleNormal(FermiFloat mean, FermiFloat deviation) {
  static std::normal_distribution<FermiFloat> distribution(0., 1.);
  return mean + distribution(Engine_) * deviation;
}

ParticleMomentum Randomizer::IsotropicVector(FermiFloat magnitude) {
  const auto cos = 1.0 - 2.0 * SampleUniform();
  const auto sin = std::sqrt(1.0 - std::pow(cos, 2));
  const auto phi = CLHEP::twopi * SampleUniform();

  return ParticleMomentum(
    magnitude * std::cos(phi) * sin,
    magnitude * std::sin(phi) * sin,
    magnitude * cos);
}

std::vector<FermiFloat> Randomizer::ProbabilityDistribution(size_t pointCount) {
  // Sample uniform random numbers in increasing order
  std::vector<FermiFloat> probabilityDistribution(pointCount);

  probabilityDistribution.front() = 0.;
  std::generate_n(probabilityDistribution.begin(), pointCount - 2, Randomizer::SampleUniform);
  probabilityDistribution.back() = 1.;

  std::sort(probabilityDistribution.begin(), probabilityDistribution.end());

  return probabilityDistribution;
}

size_t Randomizer::SampleDistribution(const std::vector<FermiFloat>& weights) {
  const auto totalWeight = std::accumulate(weights.begin(), weights.end(), 0.);
  ASSERT_MSG(totalWeight > 0., "Invalid weights: all values are zero");

  const auto targetWeight = SampleUniform() * totalWeight;
  FermiFloat cummulativeWeight = 0;
  for (size_t i = 0; i < weights.size(); ++i) {
    cummulativeWeight += weights[i];

    if (cummulativeWeight >= targetWeight) {
      return i;
    }
  }

  return weights.size() - 1;
}

void Randomizer::SetSeed(RandomEngine::result_type seed) {
  Engine_.seed(seed);
}
