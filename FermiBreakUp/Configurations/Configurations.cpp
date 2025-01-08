//
// Created by Artem Novikov on 19.02.2023.
//

#include <functional>

#include "Configurations.h"
#include "utilities/ConfigurationProperties.h"
#include "utilities/Randomizer.h"

using namespace fermi;

Configurations::Configurations(NucleiData nucleiData, FermiFloat totalEnergy) {
  Configurations::GenerateSplits(nucleiData, totalEnergy);
}

VConfigurations& Configurations::GenerateSplits(NucleiData nucleiData, FermiFloat totalEnergy) {
  configurations_.clear();
  weights_.clear();

  // let's split nucleus into 2,...,A fragments
  FermiFloat totalWeight = 0;
  auto maxFragmentsCount = FermiUInt(nucleiData.atomicMass);

  for (uint32_t particleCount = 2; particleCount <= maxFragmentsCount; particleCount++) {
    // initialize configuration for k fragments
    for (auto& split : Split(nucleiData, particleCount)) {
      // non-normalized statistical weight for given channel with k fragments
      auto splitWeight = ConfigurationProperties::DecayProbability(split, nucleiData.atomicMass, totalEnergy);
      if (splitWeight != 0) {
        totalWeight += splitWeight;

        weights_.push_back(splitWeight);
        configurations_.emplace_back(std::move(split));  // split is moved!
      }
    }
  }

  // let's normalize statistical weights of channels
  std::transform(weights_.begin(), weights_.end(),
                 weights_.begin(), std::bind(std::divides(), std::placeholders::_1, totalWeight));

  return *this;
}

std::optional<FragmentVector> Configurations::ChooseSplit() {
  if (configurations_.empty()) {
    return {};
  }

  FermiFloat wheelResult = Randomizer::uniform_real_distribution();
  FermiFloat accumulatedWeight = 0;

  for (size_t i = 0; i < weights_.size(); ++i) {
    accumulatedWeight += weights_[i];

    if (accumulatedWeight >= wheelResult) {
      return configurations_[i];
    }
  }

  throw std::runtime_error("No split chosen, something went wrong!");
}

std::unique_ptr<VConfigurations> Configurations::Clone() const {
  return std::make_unique<Configurations>(*this);
}
