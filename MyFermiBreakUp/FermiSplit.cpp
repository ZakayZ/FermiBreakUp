//
// Created by Artem Novikov on 17.02.2023.
//

#include <numeric>

#include "FermiSplit.h"
#include "IntegerPartition.h"
#include "FermiFragmentPool.h"
#include "LRUCache.h"

const size_t FermiSplit::MemoryLimit = 20;

FermiSplit::SplitsCache FermiSplit::Cache(MemoryLimit);

FermiSplit::FermiSplit(MassNumber mass_number, ChargeNumber charge_number, const uint32_t fragment_count, bool cache) {
  auto error = ValidateInputs(mass_number, charge_number, fragment_count);
  if (!error.empty()) {
    throw std::runtime_error(error);
  }

  auto nuclei_data = NucleiData{mass_number, charge_number};
  if (cache && Cache.Contains({nuclei_data, fragment_count})) {
    splits_= Cache.Get({nuclei_data, fragment_count});
    return;
  }

  /// Form all possible partition by combination of A partitions and Z partitions (Z partitions include null parts)
  for (auto& mass_partition : IntegerPartition(mass_number, fragment_count, false)) {
    for (auto& charge_partition : IntegerPartition(charge_number, fragment_count, true)) {
      /// Get multiplicities provided that for each a,z pair there could be several possibilities,
      /// we have to count them in order to create all possible combinations.
      auto fragment_variation = FragmentVariations(mass_partition, charge_partition);

      /// if size of multiplicities is equal to K, it means that all combinations a,z exist in the fragments pool
      if (fragment_variation.size() == fragment_count) {
        auto additional_splits =
            GeneratePossibleSplits(mass_partition, charge_partition, fragment_variation);

        AddValidSplits(additional_splits);
      }
    }
  }

  if (cache) {
    Cache.Insert({nuclei_data, fragment_count}, splits_);
  }
}

FermiSplit::iterator FermiSplit::begin() {
  return splits_.begin();
}

FermiSplit::const_iterator FermiSplit::begin() const {
  return splits_.cbegin();
}

FermiSplit::const_iterator FermiSplit::cbegin() const {
  return splits_.cbegin();
}

FermiSplit::iterator FermiSplit::end() {
  return splits_.end();
}

FermiSplit::const_iterator FermiSplit::end() const {
  return splits_.cend();
}

FermiSplit::const_iterator FermiSplit::cend() const {
  return splits_.cend();
}

const std::vector<FragmentSplit>& FermiSplit::GetSplits() const {
  return splits_;
}

std::string FermiSplit::ValidateInputs(MassNumber mass_number, ChargeNumber charge_number, uint32_t fragment_count) {
  std::string error_message = "";
  if (mass_number < 0_m || charge_number < 0_c || fragment_count < 0) {
    error_message = "Non valid arguments A = " + std::to_string(mass_number) + " Z = "
        + std::to_string(charge_number) + " #fragments = " + std::to_string(fragment_count);
  }
  if (FermiUInt(charge_number) > FermiUInt(mass_number) || fragment_count > FermiUInt(mass_number)) {
    error_message = "Non physical arguments = " + std::to_string(mass_number) + " Z = "
        + std::to_string(charge_number) + " #fragments = " + std::to_string(fragment_count);
  }

  return error_message;
}

std::vector<size_t> FermiSplit::FragmentVariations(const Partition& mass_partition, const Partition& charge_partition) {
  FermiFragmentPool fragment_pool;

  auto fragment_count = mass_partition.size();

  std::vector<size_t> fragment_variations;
  fragment_variations.reserve(fragment_count);

  for (size_t fragment_idx = 0; fragment_idx < fragment_count; ++fragment_idx) {
    auto possible_fragments = fragment_pool.Count(MassNumber(mass_partition[fragment_idx]),
                                                  ChargeNumber(charge_partition[fragment_idx]));
    if (possible_fragments <= 0) {
      return fragment_variations;
    }
    fragment_variations.push_back(possible_fragments);
  }
  return fragment_variations;
}

std::vector<FragmentSplit> FermiSplit::GeneratePossibleSplits(
    const Partition& mass_partition, const Partition& charge_partition, const std::vector<size_t>& fragment_variation) {
  FermiFragmentPool fragment_pool;

  auto splits_count =
      std::accumulate(fragment_variation.begin(), fragment_variation.end(), 1, std::multiplies<size_t>());

  auto fragment_count = mass_partition.size();

  std::vector<FragmentSplit> splits;
  splits.resize(splits_count);
  for (auto& split : splits) {
    split.reserve(fragment_count);
  }

  for (size_t fragment_idx = 0; fragment_idx < fragment_count; ++fragment_idx) {
    auto fragment_range = fragment_pool.GetFragments(MassNumber(mass_partition[fragment_idx]),
                                                     ChargeNumber(charge_partition[fragment_idx]));
    size_t offset = 0;
    size_t step = fragment_variation[fragment_idx];
    for (auto fragment_it = fragment_range.first; fragment_it != fragment_range.second; ++fragment_it) {
      for (size_t pos = offset++; pos < splits_count; pos += step) {
        splits[pos].push_back(fragment_it->second);
      }
    }
  }
  return splits;
}

void FermiSplit::AddValidSplits(const std::vector<FragmentSplit>& possible_splits) {
  for (auto split : possible_splits) {
    std::sort(split.begin(), split.end(), std::greater<const FermiFragment*>());
    /// greater, because they already partially sorted by greater
  }
  /// move splits into main vector (eliminating a few of them that are repeated)
  splits_.emplace_back(possible_splits[0]);
  for (auto& split : possible_splits) {
    if (splits_.back() == split) {
      continue;
    }
    splits_.emplace_back(split);
  }
}
