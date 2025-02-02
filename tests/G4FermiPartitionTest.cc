//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// G4FermiBreakUp alternative de-excitation model
// by A. Novikov (January 2025)
//

#include "G4FermiIntegerPartition.hh"

#include <gtest/gtest.h>

#include <numeric>

using namespace fbu;

size_t factorial(size_t num)
{
  size_t fact = 1;
  for (size_t i = 2; i <= num; ++i) {
    fact *= i;
  }
  return fact;
}

size_t Cnk(size_t n, size_t k)
{
  return factorial(n) / factorial(k) / factorial(n - k);
}

TEST(PartitionTests, SmallOnePadding)
{
  constexpr size_t partitionNumber = 6;
  constexpr size_t partitionParts = 3;

  size_t partitionCounter = 0;
  for (const auto& partition : G4FermiIntegerPartition(partitionNumber, partitionParts, 1)) {
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

TEST(PartitionTests, BigOnePadding)
{
  const size_t partitionNumber = 20;
  const size_t partitionParts = 7;

  size_t partitionCounter = 0;
  for (const auto& partition : G4FermiIntegerPartition(partitionNumber, partitionParts, 1)) {
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

TEST(PartitionTests, SmallZeroPadding)
{
  constexpr size_t partitionNumber = 7;
  constexpr size_t partitionParts = 3;

  size_t partitionCounter = 0;
  for (const auto& partition : G4FermiIntegerPartition(partitionNumber, partitionParts, 0)) {
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

TEST(PartitionTests, BigZeroPadding)
{
  constexpr size_t partitionNumber = 16;
  constexpr size_t partitionParts = 4;

  size_t partitionCounter = 0;
  for (const auto& partition : G4FermiIntegerPartition(partitionNumber, partitionParts, 0)) {
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
