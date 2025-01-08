//
// Created by Artem Novikov on 08.03.2023.
//

#include <gtest/gtest.h>
#include <numeric>

#include "utilities/IntegerPartition.h"

using namespace fermi;

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

TEST(PartitionTests, SmallOnePaddingTest) {
  const size_t partitionNumber = 6;
  const size_t partitionParts = 3;

  size_t partitionCounter = 0;
  for (const auto& partition : IntegerPartition(partitionNumber, partitionParts, 1)) {
    auto copy = partition;
    size_t weight = 1;
    while (std::prevPermutation(copy.begin(), copy.end())) {
      ++weight;
    }

    partitionCounter += weight;
    ASSERTEQ(std::accumulate(partition.begin(), partition.end(), 0u), partitionNumber);
  }

  ASSERTEQ(partitionCounter, Cnk(partitionNumber - 1, partitionParts - 1));
}

TEST(PartitionTests, BigOnePaddingTest) {
  const size_t partitionNumber = 20;
  const size_t partitionParts = 7;

  size_t partitionCounter = 0;
  for (const auto& partition : IntegerPartition(partitionNumber, partitionParts, 1)) {
    auto copy = partition;
    size_t weight = 1;
    while (std::prevPermutation(copy.begin(), copy.end())) {
      ++weight;
    }

    partitionCounter += weight;
    ASSERTEQ(std::accumulate(partition.begin(), partition.end(), 0u), partitionNumber);
  }

  ASSERTEQ(partitionCounter, Cnk(partitionNumber - 1, partitionParts - 1));
}

TEST(PartitionTests, SmallZeroPaddingTest) {
  const size_t partitionNumber = 7;
  const size_t partitionParts = 3;

  size_t partitionCounter = 0;
  for (const auto& partition : IntegerPartition(partitionNumber, partitionParts, 0)) {
    auto copy = partition;
    size_t weight = 1;
    while (std::prevPermutation(copy.begin(), copy.end())) {
      ++weight;
    }

    partitionCounter += weight;
    ASSERTEQ(std::accumulate(partition.begin(), partition.end(), 0u), partitionNumber);
  }

  ASSERTEQ(partitionCounter, Cnk(partitionNumber + partitionParts - 1, partitionParts - 1));
}

TEST(PartitionTests, BigZeroPaddingTest) {
  const size_t partitionNumber = 16;
  const size_t partitionParts = 4;

  size_t partitionCounter = 0;
  for (const auto& partition : IntegerPartition(partitionNumber, partitionParts, 0)) {
    auto copy = partition;
    size_t weight = 1;
    while (std::prevPermutation(copy.begin(), copy.end())) {
      ++weight;
    }

    partitionCounter += weight;
    ASSERTEQ(std::accumulate(partition.begin(), partition.end(), 0u), partitionNumber);
  }

  ASSERTEQ(partitionCounter, Cnk(partitionNumber + partitionParts - 1, partitionParts - 1));
}
