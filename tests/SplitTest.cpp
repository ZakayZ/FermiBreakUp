//
// Created by Artem Novikov on 19.03.2023.
//

#include <algorithm>

#include <gtest/gtest.h>

#include <CLHEP/Units/PhysicalConstants.h>

#include "FermiBreakUp/Splitter.h"

using namespace fbu;

TEST(SplitTest, NoDuplicates) {
  FragmentSplits splits; // speeds up test
  for (FermiUInt a = 1; a < 18; ++a) {
    for (FermiUInt z = 0; z <= a; ++z) {
      const auto mass = AtomicMass(a);
      const auto charge = ChargeNumber(z);
      splits.clear();
      Splitter::GenerateSplits({mass, charge}, splits);

      for (auto& split : splits) {
        std::sort(split.begin(), split.end());
      }
      for (size_t i = 0; i < splits.size(); ++i) {
        for (size_t j = i + 1; j < splits.size(); ++j) {
          ASSERT_NE(splits[i], splits[j])
              << "Some of splits the same for A = "
              << mass << ", Z = " << charge;
        }
      }
    }
  }
}
