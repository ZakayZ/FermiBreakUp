//
// Created by Artem Novikov on 18.02.2024.
//

#include "utilities/ConfigurationProperties.h"
#include "utilities/Randomizer.h"

#include "FastConfigurations.h"

using namespace fermi;

FastConfigurations::FastConfigurations(NucleiData nucleiData, FermiFloat totalEnergy) {
  FastConfigurations::GenerateSplits(nucleiData, totalEnergy);
}

VConfigurations& FastConfigurations::GenerateSplits(NucleiData nucleiData, FermiFloat totalEnergy) {
  lastNuclei_= nucleiData;
  auto maxFragmentsCount = FermiUInt(nucleiData.atomicMass);
  auto& cache = cachedConfigurations_[nucleiData];
  if (cache.empty()) {
    cache.reserve(100);

    for (uint32_t particleCount = 2; particleCount <= maxFragmentsCount; ++particleCount) {
      for (auto& split : Split(nucleiData, particleCount)) {
        cache.emplace_back(std::move(split));  // split is moved!
      }
    }
  }

  configurations_.clear();
  weights_.clear();

  FermiFloat totalWeight = 0;
  for (size_t i = 0; i < cache.size(); ++i) {
    auto splitWeight =
        ConfigurationProperties::DecayProbability(cache[i], nucleiData.atomicMass, totalEnergy);

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

std::optional<FragmentVector> FastConfigurations::ChooseSplit() {
  if (configurations_.empty()) {
    return {};
  }

  FermiFloat wheelResult = Randomizer::uniform_real_distribution();
  FermiFloat accumulatedWeight = 0;

  for (size_t i = 0; i < weights_.size(); ++i) {
    accumulatedWeight += weights_[i];

    if (accumulatedWeight >= wheelResult) {
      return cachedConfigurations_[lastNuclei_][configurations_[i]];
    }
  }

  throw std::runtime_error("No split chosen, something went wrong!");
}

std::unique_ptr<VConfigurations> FastConfigurations::Clone() const {
  return std::make_unique<FastConfigurations>(*this);
}
