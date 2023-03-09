//
// Created by Artem Novikov on 19.02.2023.
//

#include <functional>

#include "FermiConfigurations.h"
#include "ConfigurationProperties.h"
#include "Randomizer.h"

const size_t FermiConfigurations::MaxNumberOfFragments = 16;

FermiConfigurations::FermiConfigurations(MassNumber mass_number, ChargeNumber charge_number, FermiFloat total_energy) {
  /// let's split nucleus into 2,...,A fragments
  FermiFloat total_weight = 0;
  auto max_fragments_count = FermiUInt(mass_number);
  for (uint32_t particle_count = 2; particle_count <= max_fragments_count; particle_count++) {
    /// Initialize Configuration for k fragments
    for (auto& split : FermiSplit(mass_number, charge_number, particle_count)) {
      /// Non-Normalized statistical weight for given channel with k fragments
      auto split_weight = ConfigurationProperties::DecayProbability(split, mass_number, total_energy);
      if (split_weight != 0) {
        total_weight += split_weight;

        weights_.push_back(split_weight);
        configurations_.emplace_back(std::move(split));  /// split is moved!
      }
    }
  }

  /// Let's normalize statistical weights of channels
  std::transform(weights_.begin(), weights_.end(),
                 weights_.begin(), std::bind(std::divides<FermiFloat>(), std::placeholders::_1, total_weight));
}

bool FermiConfigurations::IsSplitPossible() const {
  return !configurations_.empty();
}

const FragmentSplit& FermiConfigurations::ChooseSplit() const {
  if (!IsSplitPossible()) {
    throw std::runtime_error("No possible splits!");
  }

  FermiFloat wheel_result = Randomizer::UniformRealDistribution();
  FermiFloat accumulated_weight = 0;

  for (size_t i = 0; i < weights_.size(); ++i) {
    accumulated_weight += weights_[i];

    if (accumulated_weight >= wheel_result) {
      return configurations_[i];
    }
  }

  throw std::runtime_error("No split chosen, something went wrong!");
}
