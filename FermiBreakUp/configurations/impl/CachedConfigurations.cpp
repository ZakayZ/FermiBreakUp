//
// Created by Artem Novikov on 24.05.2023.
//

#include "util/Randomizer.h"

#include "configurations/Split.h"

#include "CachedConfigurations.h"

using namespace fermi;

CachedConfigurations::CachedConfigurations(NucleiData nucleiData, FermiFloat totalEnergy) {
  CachedConfigurations::GenerateSplits(nucleiData, totalEnergy);
}

VConfigurations& CachedConfigurations::GenerateSplits(NucleiData nucleiData, FermiFloat totalEnergy) {
  auto maxFragmentsCount = FermiUInt(nucleiData.atomicMass);
  if (nucleiData != lastNuclei_) {
    lastNuclei_ = nucleiData;
    cachedConfigurations_.clear();

    for (uint32_t particleCount = 2; particleCount <= maxFragmentsCount; ++particleCount) {
      for (auto& split : PossibleSplits(nucleiData, particleCount)) {
        cachedConfigurations_.emplace_back(std::move(split));  // split is moved!
      }
    }
  }

  configurations_.clear();
  weights_.clear();

  FermiFloat totalWeight = 0;
  for(size_t i = 0; i < cachedConfigurations_.size(); ++i) {
    auto splitWeight = DecayProbability(cachedConfigurations_[i], nucleiData.atomicMass, totalEnergy);

    if (splitWeight != 0) {
      totalWeight += splitWeight;

      weights_.push_back(splitWeight);
      configurations_.emplace_back(i);
    }
  }

  std::transform(weights_.begin(), weights_.end(),
                 weights_.begin(), std::bind(std::divides<>(), std::placeholders::_1, totalWeight));

  return *this;
}

std::optional<FragmentVector> CachedConfigurations::ChooseSplit() {
  if (configurations_.empty()) {
    return std::nullopt;
  }

  FermiFloat wheelResult = Randomizer::SampleUniform();
  FermiFloat accumulatedWeight = 0;

  for (size_t i = 0; i < weights_.size(); ++i) {
    accumulatedWeight += weights_[i];

    if (accumulatedWeight >= wheelResult) {
      return cachedConfigurations_[configurations_[i]];
    }
  }

  throw std::runtime_error("No split chosen, something went wrong!");
}

std::unique_ptr<VConfigurations> CachedConfigurations::Clone() const {
  return std::make_unique<CachedConfigurations>(*this);
}
