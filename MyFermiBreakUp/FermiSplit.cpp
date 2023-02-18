//
// Created by Artem Novikov on 17.02.2023.
//

#include <numeric>

#include "FermiSplit.h"
#include "IntegerPartition.h"
#include "FermiFragmentPool.h"

FermiSplit::FermiSplit(uint32_t mass_number, uint32_t charge_number, const uint32_t fragment_count) {
  /// Check argument correctness
  if (mass_number < 0 || charge_number < 0 || fragment_count < 0) {
    std::string error_message =
        "G4FermiSplitter::Initialize() Error: Non valid arguments A = " + std::to_string(mass_number) + " Z = "
            + std::to_string(charge_number) + " #fragments = " + std::to_string(fragment_count);
    throw std::runtime_error(error_message);
  }
  if (charge_number > mass_number || fragment_count > mass_number) {
    std::string error_message =
        "G4FermiSplitter::Initialize() Error: Non physical arguments = " + std::to_string(mass_number) + " Z = "
            + std::to_string(charge_number) + " #fragments = " + std::to_string(fragment_count);
    throw std::runtime_error(error_message);
  }

  /// Form all possible partition by combination of A partitions and Z partitions (Z partitions include null parts)
  for (auto& mass_partition : IntegerPartition(mass_number, fragment_count, false)) {
    for (auto& charge_partition : IntegerPartition(charge_number, fragment_count, true)) {
      /// Get multiplicities provided that for each a,z pair there could be several posibilities,
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
}

const FermiSplit::FragmentSplits& FermiSplit::GetSplits() const {
  return splits_;
}

void FermiSplit::AddValidSplits(const FermiSplit::FragmentSplits& possible_splits) {
  /// TODO refactor creation, to eliminate duplicates from the start for speed up
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

std::vector<size_t> FermiSplit::FragmentVariations(const Partition& mass_partition, const Partition& charge_partition) {
  FermiFragmentPool fragment_pool;

  auto fragment_count = mass_partition.size();

  std::vector<size_t> fragment_variations;
  fragment_variations.reserve(fragment_count);

  for (size_t fragment_idx = 0; fragment_idx < fragment_count; ++fragment_idx) {
    auto possible_fragments = fragment_pool.Count(mass_partition[fragment_idx], charge_partition[fragment_idx]);
    if (possible_fragments <= 0) {
      return fragment_variations;
    }
    fragment_variations.push_back(possible_fragments);
  }
  return fragment_variations;
}

FermiSplit::FragmentSplits FermiSplit::GeneratePossibleSplits(
    const Partition& mass_partition, const Partition& charge_partition, const std::vector<size_t>& fragment_variation) {
  FermiFragmentPool fragment_pool;

  auto splits_count =
      std::accumulate(fragment_variation.begin(), fragment_variation.end(), 1, std::multiplies<size_t>());

  auto fragment_count = mass_partition.size();

  FragmentSplits splits;
  splits.resize(splits_count);
  for (auto& split : splits) {
    split.reserve(fragment_count);
  }

  for (size_t fragment_idx = 0; fragment_idx < fragment_count; ++fragment_idx) {
    auto fragment_range = fragment_pool.GetFragments(mass_partition[fragment_idx], charge_partition[fragment_idx]);
    size_t step = fragment_variation[fragment_idx];
    size_t offset = 0;
    for (auto fragment_it = fragment_range.first; fragment_it != fragment_range.second; ++fragment_it) {
      for (size_t pos = offset++; pos < splits_count; pos += step) {
        splits[pos].push_back(fragment_it->second);
      }
    }
    step = fragment_variation[fragment_idx];
  }
  return splits;
}
