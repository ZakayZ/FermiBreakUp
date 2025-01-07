//
// Created by Artem Novikov on 21.02.2023.
//

#include <numeric>
#include <algorithm>
#include <functional>

#include "Decay.h"
#include "Utilities/Randomizer.h"

using namespace fermi;

static const size_t MaxTryCount = 1e6;

std::vector<LorentzVector> Decay::CalculateDecay(const LorentzVector& momentum,
                                                 const std::vector<FermiFloat>& fragmentsMass) const {
  std::vector<LorentzVector> result;
  result.reserve(fragmentsMass.size());
  auto totalEnergy = momentum.m();

  // 2 bodies case is faster
  if (fragmentsMass.size() == 2) {
    auto momentum4 = TwoBodyDecay(totalEnergy, fragmentsMass[0], fragmentsMass[1]);
    result.push_back(momentum4.first);
    result.push_back(momentum4.second);
    return result;
  }

  // N body case
  FermiFloat totalMass = std::accumulate(fragmentsMass.begin(), fragmentsMass.end(), FermiFloat(0));
  FermiFloat maxEnergy = totalEnergy - totalMass + fragmentsMass[0];
  FermiFloat maxWeight = CalculateMaxWeight(fragmentsMass, maxEnergy);

  size_t tryCount = 0;
  FermiFloat configurationWeight = 0;
  std::vector<FermiFloat> momentumMagnitudes(fragmentsMass.size());
  while (configurationWeight < Randomizer::uniform_real_distribution() * maxWeight) {
    auto virtualMasses = CalculateVirtualMasses(fragmentsMass, totalEnergy - totalMass);

    configurationWeight = CalculateMomentumMagnitudes(momentumMagnitudes, fragmentsMass, virtualMasses);

    if (tryCount++ > MaxTryCount) {
      throw std::runtime_error("FermiPhaseSpaceDecay::Decay: Cannot determine decay kinematics");
    }
  }

  ParticleMomentum pivotMomentum = Randomizer::IsotropicVector(momentumMagnitudes[0]);
  result.emplace_back(pivotMomentum, std::sqrt(pivotMomentum.mag2() + std::pow(fragmentsMass[0], 2)));  // 0
  result.emplace_back(-pivotMomentum, std::sqrt(pivotMomentum.mag2() + std::pow(fragmentsMass[1], 2))); // 1

  for (size_t i = 2; i < fragmentsMass.size(); ++i) {
    pivotMomentum = Randomizer::IsotropicVector(momentumMagnitudes[i - 1]);
    result.emplace_back(pivotMomentum, std::sqrt(pivotMomentum.mag2() + std::pow(fragmentsMass[i], 2)));
    Vector3 boostVector = (-1.0) * result.back().boostVector();
    // boost already created particles
    for (auto& fragmentMomentum: result) {
      fragmentMomentum.boost(boostVector);
    }
  }

  return result;
}

std::vector<FermiFloat> Decay::CalculateVirtualMasses(const std::vector<FermiFloat>& masses, FermiFloat energy) {
  auto probabilityDistribution = Randomizer::ProbabilityDistribution(masses.size());

  // Calculate virtual masses
  std::vector<FermiFloat> virtualMasses(masses.size());
  virtualMasses[0] = 0;
  std::partial_sum(masses.begin(), masses.end(), virtualMasses.begin());

  std::transform(probabilityDistribution.begin(),
                 probabilityDistribution.end(),
                 probabilityDistribution.begin(),
                 std::bind(std::multiplies<FermiFloat>(), std::placeholders::_1, energy));

  std::transform(probabilityDistribution.begin(),
                 probabilityDistribution.end(),
                 virtualMasses.begin(),
                 virtualMasses.begin(),
                 std::plus<FermiFloat>());
  return virtualMasses;
}

FermiFloat Decay::CalculateMomentumMagnitudes(std::vector<FermiFloat>& daughterMomentum,
                                              const std::vector<FermiFloat>& masses,
                                              const std::vector<FermiFloat>& virtualMasses) {
  size_t sz = daughterMomentum.size();
  FermiFloat weight = 1;
  for (size_t i = 0; i < sz - 1; ++i) {
    daughterMomentum[i] = TwoBodyMomentum(virtualMasses[i + 1], virtualMasses[i], masses[i + 1]);
    weight *= daughterMomentum[i];

    if (daughterMomentum[i] < 0) {
      std::cerr << "FermiPhaseSpaceDecay::Decay: Daughter momentum less than zero\n";
      return 0;
    }
  }
  daughterMomentum[sz - 1] = TwoBodyMomentum(virtualMasses[sz - 2], masses[sz - 2], masses[sz - 1]);
  return weight;
}

FermiFloat Decay::CalculateMaxWeight(const std::vector<FermiFloat>& masses, FermiFloat maxEnergy) {
  FermiFloat minEnergy = 0;
  FermiFloat maxWeight = 1.0;
  for (size_t i = 0; i < masses.size(); ++i) {
    maxEnergy += masses[i];
    minEnergy += masses[i - 1];
    maxWeight *= TwoBodyMomentum(maxEnergy, minEnergy, masses[i]);
  }
  return maxWeight;
}



