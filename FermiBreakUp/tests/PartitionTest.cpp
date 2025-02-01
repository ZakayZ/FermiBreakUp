//
// Created by Artem Novikov on 08.03.2023.
//

#include <gtest/gtest.h>
#include <numeric>

#include "util/IntegerPartition.h"

using namespace fbu;

size_t factorial(size_t num) {
  size_t fact = 1;
  for (size_t i = 2; i <= num; ++i) {
    fact *= i;
  }
  return fact;
}

size_t Cnk(size_t n, size_t k) {
  return factorial(n) / factorial(k) / factorial(n - k);
}

TEST(PartitionTests, SmallOnePadding) {
  constexpr size_t partitionNumber = 6;
  constexpr size_t partitionParts = 3;

  size_t partitionCounter = 0;
  for (const auto& partition : IntegerPartition(partitionNumber, partitionParts, 1)) {
    auto copy = partition;
    size_t weight = 1;
    while (std::prev_permutation(copy.begin(), copy.end())) {
      ++weight;
    }

    partitionCounter += weight;
    ASSERT_EQ(std::accumulate(partition.begin(), partition.end(), 0u), partitionNumber);
  }

  ASSERT_EQ(partitionCounter, Cnk(partitionNumber - 1, partitionParts - 1));
}

TEST(PartitionTests, BigOnePadding) {
  const size_t partitionNumber = 20;
  const size_t partitionParts = 7;

  size_t partitionCounter = 0;
  for (const auto& partition : IntegerPartition(partitionNumber, partitionParts, 1)) {
    auto copy = partition;
    size_t weight = 1;
    while (std::prev_permutation(copy.begin(), copy.end())) {
      ++weight;
    }

    partitionCounter += weight;
    ASSERT_EQ(std::accumulate(partition.begin(), partition.end(), 0u), partitionNumber);
  }

  ASSERT_EQ(partitionCounter, Cnk(partitionNumber - 1, partitionParts - 1));
}

TEST(PartitionTests, SmallZeroPadding) {
  constexpr size_t partitionNumber = 7;
  constexpr size_t partitionParts = 3;

  size_t partitionCounter = 0;
  for (const auto& partition : IntegerPartition(partitionNumber, partitionParts, 0)) {
    auto copy = partition;
    size_t weight = 1;
    while (std::prev_permutation(copy.begin(), copy.end())) {
      ++weight;
    }

    partitionCounter += weight;
    ASSERT_EQ(std::accumulate(partition.begin(), partition.end(), 0u), partitionNumber);
  }

  ASSERT_EQ(partitionCounter, Cnk(partitionNumber + partitionParts - 1, partitionParts - 1));
}

TEST(PartitionTests, BigZeroPadding) {
  constexpr size_t partitionNumber = 16;
  constexpr size_t partitionParts = 4;

  size_t partitionCounter = 0;
  for (const auto& partition : IntegerPartition(partitionNumber, partitionParts, 0)) {
    auto copy = partition;
    size_t weight = 1;
    while (std::prev_permutation(copy.begin(), copy.end())) {
      ++weight;
    }

    partitionCounter += weight;
    ASSERT_EQ(std::accumulate(partition.begin(), partition.end(), 0u), partitionNumber);
  }

  ASSERT_EQ(partitionCounter, Cnk(partitionNumber + partitionParts - 1, partitionParts - 1));
}
