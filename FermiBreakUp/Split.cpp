//
// Created by Artem Novikov on 17.02.2023.
//

#include <numeric>
#include <algorithm>
#include <array>

#include "Split.h"
#include "fragment_pool/FragmentPool.h"
#include "utilities/IntegerPartition.h"

using namespace fermi;

Split::Split(NucleiData nucleiData, const uint32_t fragmentCount) {
  auto error = ValidateInputs(nucleiData, fragmentCount);
  if (!error.empty()) {
    throw std::runtime_error(error);
  }

  reserve(100);

  // Form all possible partition by combination of A partitions and Z partitions (Z partitions include null parts)
  for (auto& massPartition : IntegerPartition(nucleiData.atomicMass, fragmentCount, 1)) {
    for (auto& chargePartition : IntegerPartition(nucleiData.chargeNumber, fragmentCount, 0)) {
      // Some splits are invalid, some nuclei doesn't exist
      if (IsSplitPossible(massPartition, chargePartition)) {
        auto additionalSplits = GeneratePossibleSplits(massPartition, chargePartition);

        AddValidSplits(std::move(additionalSplits));
      }
    }
  }
}

std::string Split::ValidateInputs(NucleiData nucleiData, uint32_t fragmentCount) {
  std::string errorMessage;
  if (nucleiData.atomicMass < 0_m || nucleiData.chargeNumber < 0_c) {
    errorMessage = "Non valid arguments A = " + std::to_string(nucleiData.atomicMass) + " Z = "
        + std::to_string(nucleiData.chargeNumber) + " #fragments = " + std::to_string(fragmentCount);
  }
  if (FermiUInt(nucleiData.chargeNumber) > FermiUInt(nucleiData.atomicMass)
      || fragmentCount > FermiUInt(nucleiData.atomicMass)) {
    errorMessage = "Non physical arguments = " + std::to_string(nucleiData.atomicMass) + " Z = "
        + std::to_string(nucleiData.chargeNumber) + " #fragments = " + std::to_string(fragmentCount);
  }

  return errorMessage;
}

std::vector<size_t> Split::FragmentVariations(const Partition& massPartition, const Partition& chargePartition) {
  auto& fragmentPool = fermi::fragment_pool::Instance();

  auto fragmentCount = massPartition.size();
  std::vector<size_t> fragmentVariations;
  fragmentVariations.reserve(fragmentCount);

  for (size_t fragmentIdx = 0; fragmentIdx < fragmentCount; ++fragmentIdx) {
    auto possibleFragments = fragmentPool.Count(AtomicMass(massPartition[fragmentIdx]),
                                                  ChargeNumber(chargePartition[fragmentIdx]));
    fragmentVariations.push_back(possibleFragments);
  }
  return fragmentVariations;
}

bool Split::IsSplitPossible(const Partition& massPartition, const Partition& chargePartition) {
  auto& fragmentPool = fermi::fragment_pool::Instance();

  auto fragmentCount = massPartition.size();

  for (size_t fragmentIdx = 0; fragmentIdx < fragmentCount; ++fragmentIdx) {
    if (fragmentPool.Count(AtomicMass(massPartition[fragmentIdx]),
                            ChargeNumber(chargePartition[fragmentIdx])) == 0) {
      return false;
    }
  }
  return true;
}

std::vector<FragmentVector> Split::GeneratePossibleSplits(
    const Partition& massPartition, const Partition& chargePartition) {
  auto& fragmentPool = fermi::fragment_pool::Instance();
  size_t fragmentCount = massPartition.size();

  auto fragmentVariation = FragmentVariations(massPartition, chargePartition);
  size_t splitsCount = std::accumulate(fragmentVariation.begin(), fragmentVariation.end(), 1, std::multiplies<>());

  std::vector<FragmentVector> splits(splitsCount);
  for (auto& split: splits) {
    split.reserve(fragmentCount);
  }

  for (size_t fragmentIdx = 0; fragmentIdx < fragmentCount; ++fragmentIdx) {
    auto fragmentRange = fragmentPool.GetFragments(AtomicMass(massPartition[fragmentIdx]),
                                                     ChargeNumber(chargePartition[fragmentIdx]));
    size_t offset = 0;
    size_t step = fragmentVariation[fragmentIdx];
    for (auto fragmentIt = fragmentRange.first; fragmentIt != fragmentRange.second; ++fragmentIt) {
      for (size_t pos = offset; pos < splitsCount; pos += step) {
        splits[pos].emplace_back(*fragmentIt);
      }
      ++offset;
    }
  }
  return splits;
}

void Split::AddValidSplits(std::vector<FragmentVector>&& possibleSplits) {
  for (auto split : possibleSplits) {
    std::sort(split.begin(), split.end(), std::greater<>());
    // greater, because they already partially sorted as greater 
  }

  // move splits into main vector (eliminating a few of them that are repeated)
  emplace_back(possibleSplits[0]);
  for (auto& split : possibleSplits) {
    if (back() == split) {
      continue;
    }
    emplace_back(std::move(split));
  }
}
