//
// Created by Artem Novikov on 17.02.2023.
//

#include <algorithm>
#include <iterator>
#include <numeric>
#include <string>

#include <CLHEP/Units/PhysicalConstants.h>

#include "fragment_pool/FragmentPool.h"
#include "util/IntegerPartition.h"
#include "util/Logger.h"

#include "Split.h"

using namespace fermi;

namespace {
  // Kappa = V/V_0 it is used in calculation of Coulomb energy, Kappa is dimensionless
  constexpr FermiFloat Kappa = 1.0;

  // Nuclear radius R0 (is a model parameter)
  constexpr FermiFloat R0 = 1.3 * CLHEP::fermi;

  FermiFloat CoulombBarrier(const FragmentVector& split) {
    // Coulomb Barrier (MeV) for given channel with K fragments.
    static const FermiFloat coef = (3. / 5.) * (CLHEP::elm_coupling / R0) * std::cbrt(1. / (1. + Kappa));

    FermiUInt atomicMassSum = 0.;
    FermiUInt chargeSum = 0.;
    FermiFloat CoulombEnergy = 0.;
    for (const auto fragmentPtr : split) {
      auto mass = static_cast<FermiUInt>(fragmentPtr->GetAtomicMass());
      auto charge = static_cast<FermiUInt>(fragmentPtr->GetChargeNumber());
      CoulombEnergy += std::pow(charge, 2) / std::cbrt(static_cast<FermiFloat>(mass));
      atomicMassSum += mass;
      chargeSum += charge;
    }

    CoulombEnergy -= std::pow(static_cast<FermiFloat>(chargeSum), 2)
                     / std::cbrt(static_cast<FermiFloat>(atomicMassSum));
    return -coef * CoulombEnergy;
  }

  FermiFloat SpinFactor(const FragmentVector& split) {
    FermiFloat factor = 1;

    for (const auto fragmentPtr : split) {
      factor *= fragmentPtr->GetPolarization();
    }

    return factor;
  }

  FermiFloat KineticEnergy(const FragmentVector& split, FermiFloat totalEnergy) {
    auto kineticEnergy = totalEnergy;
    for (const auto fragmentPtr : split) {
      kineticEnergy -= fragmentPtr->GetTotalEnergy();
    }

    // skip columb calculation for optimization purposes
    if (kineticEnergy <= 0.) {
      return kineticEnergy;
    }

    return kineticEnergy - CoulombBarrier(split);
  }

  FermiFloat MassFactor(const FragmentVector& split) {
    FermiFloat massSum = 0.;
    FermiFloat massProduct = 1.;
    for (const auto fragmentPtr : split) {
      auto fragmentMass = fragmentPtr->GetMass();
      massProduct *= fragmentMass;
      massSum += fragmentMass;
    }
    auto massFactor = massProduct / massSum;
    massFactor *= std::sqrt(massFactor);
    return massFactor;
  }

  inline size_t Factorial(const size_t n) {
    FermiUInt factorial = 1;
    for (FermiUInt i = 2; i <= n; ++i) { factorial *= i; }
    return factorial;
  }

  FermiFloat ConfigurationFactor(const FragmentVector& split) {
    // get all mass numbers and count repetitions
    std::vector<AtomicMass> masses(split.size());
    std::transform(split.begin(), split.end(), masses.begin(), std::mem_fn(&Fragment::GetAtomicMass));
    std::sort(masses.begin(), masses.end());

    // avoid overflow with floats
    // TODO: optimize with ints maybe
    FermiFloat factor = 1;

    size_t repeatCount = 1; // we skip first, so start with 1
    for (size_t i = 1; i < masses.size(); ++i) {
      if (masses[i] != masses[i - 1]) {
        factor *= static_cast<FermiFloat>(Factorial(repeatCount));
        repeatCount = 0;
      }
      ++repeatCount;
    }
    factor *= static_cast<FermiFloat>(Factorial(repeatCount));

    return factor;
  }

  FermiFloat ConstFactor(AtomicMass atomicMass, size_t fragmentsCount) {
    static const FermiFloat COEF = std::pow(R0 / CLHEP::hbarc, 3) * Kappa * std::sqrt(2.0 / CLHEP::pi) / 3.0;

    return std::pow(COEF * static_cast<FermiFloat>(atomicMass), fragmentsCount - 1);
  }

  FermiFloat GammaFactor(size_t fragmentsCount) {
    FermiFloat gamma = 1.0;
    FermiFloat arg = 3.0 * static_cast<FermiFloat>(fragmentsCount - 1) / 2.0 - 1.0;
    while (arg > 1.1) {
      gamma *= arg;
      arg -= 1;
    }

    if (fragmentsCount % 2 == 0) {
      gamma *= std::sqrt(CLHEP::pi);
    }

    return gamma;
  }
} // namespace

FermiFloat fermi::DecayWeight(const FragmentVector& split, AtomicMass atomicMass, FermiFloat totalEnergy) {
  const auto kineticEnergy = KineticEnergy(split, totalEnergy); // in MeV

  // Check that there is enough energy to produce K fragments
  if (kineticEnergy <= 0.) {
    return 0.;
  }

  const auto power = 3.0 * static_cast<FermiFloat>(split.size() - 1) / 2.0 - 1.;
  const auto kineticFactor = std::pow(kineticEnergy, power);

  // Spin factor S_n
  const auto spinFactor = SpinFactor(split);

  // Calculate MassFactor
  const auto massFactor = MassFactor(split);

  // This is the constant (doesn't depend on energy) part
  // TODO: excessive because normalized weights are used
  const auto coef = ConstFactor(atomicMass, split.size());

  // Calculation of 1/gamma(3(k-1)/2)
  const auto gamma = GammaFactor(split.size());

  // Permutation Factor G_n
  const auto permutationFactor = ConfigurationFactor(split);

  return coef * kineticFactor * massFactor * spinFactor / (permutationFactor * gamma);
}

namespace {
  constexpr size_t ExpectedSplitSize = 100;

  void ThrowOnInvalidInputs(NucleiData nucleiData) {
    ASSERT_MSG(nucleiData.atomicMass > 0_m && nucleiData.chargeNumber >= 0_c,
               "Non valid arguments A = " << nucleiData.atomicMass
               << " Z = " << nucleiData.chargeNumber);

    ASSERT_MSG(FermiUInt(nucleiData.chargeNumber) <= FermiUInt(nucleiData.atomicMass),
               "Non physical arguments = " << nucleiData.atomicMass
               << " Z = " << nucleiData.chargeNumber);
  }

  std::vector<size_t> FragmentVariations(const Partition& massPartition, const Partition& chargePartition) {
    auto& fragmentPool = fermi::FragmentPool::Instance();

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

  std::optional<FragmentSplits> PossibleSplits(const Partition& massPartition, const Partition& chargePartition) {
    auto& fragmentPool = FragmentPool::Instance();
    size_t fragmentCount = massPartition.size();

    auto fragmentVariation = FragmentVariations(massPartition, chargePartition);
    if (std::any_of(fragmentVariation.begin(), fragmentVariation.end(), [](size_t n) { return n == 0; })) {
      return std::nullopt;
    }
    size_t splitsCount = std::accumulate(fragmentVariation.begin(), fragmentVariation.end(), 1, std::multiplies<>());

    FragmentSplits splits(splitsCount);
    for (auto& split: splits) {
      split.reserve(fragmentCount);
    }

    for (size_t fragmentIdx = 0; fragmentIdx < fragmentCount; ++fragmentIdx) {
      auto fragmentRange = fragmentPool.GetFragments(AtomicMass(massPartition[fragmentIdx]),
                                                     ChargeNumber(chargePartition[fragmentIdx]));
      size_t offset = 0;
      size_t step = fragmentVariation[fragmentIdx];
      for (const auto fragmentPtr : fragmentRange) {
        for (size_t pos = offset; pos < splitsCount; pos += step) {
          splits[pos].emplace_back(fragmentPtr);
        }
        ++offset;
      }
    }

    return splits;
  }

  void AddUniqueSplits(FragmentSplits& splits, std::vector<FragmentVector>&& sortedSplits) {
    // sort particles to compare
    for (auto& split : sortedSplits) {
      std::sort(split.begin(), split.end(), std::greater<>());
      // greater, because they already partially sorted as greater 
    }

    auto uniqueEnd = std::unique(sortedSplits.begin(), sortedSplits.end());
    splits.insert(splits.end(),
                  std::make_move_iterator(sortedSplits.begin()),
                  std::make_move_iterator(uniqueEnd));
  }
} // namespace

FragmentSplits fermi::GenerateSplits(NucleiData nucleiData) {
  FragmentSplits splits;
  GenerateSplits(nucleiData, splits);
  return splits;
}

void fermi::GenerateSplits(NucleiData nucleiData, FragmentSplits& splits) {
  ThrowOnInvalidInputs(nucleiData);

  splits.reserve(ExpectedSplitSize);

  // let's split nucleus into 2, ..., A fragments
  auto maxFragmentsCount = FermiUInt(nucleiData.atomicMass);

  for (FermiUInt fragmentCount = 2; fragmentCount <= maxFragmentsCount; ++fragmentCount) {
    // Form all possible partition by combination of A partitions and Z partitions (Z partitions include null parts)
    for (auto& massPartition : IntegerPartition(nucleiData.atomicMass, fragmentCount, 1)) {
      for (auto& chargePartition : IntegerPartition(nucleiData.chargeNumber, fragmentCount, 0)) {
        // Some splits are invalid, some nuclei doesn't exist
        if (auto partitionSplits = PossibleSplits(massPartition, chargePartition)) {
          AddUniqueSplits(splits, *std::move(partitionSplits));
        }
      }
    }
  }
}
