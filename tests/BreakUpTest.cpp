//
// Created by Artem Novikov on 19.03.2023.
//

#include <numeric>
#include <gtest/gtest.h>

#include <CLHEP/Units/PhysicalConstants.h>

#include "FermiBreakUp/util/Cache.h"
#include "FermiBreakUp/util/DataTypes.h"
#include "FermiBreakUp/FermiBreakUp.h"
#include "FermiBreakUp/nuclei_properties/NucleiProperties.h"
#include "FermiBreakUp/util/Randomizer.h"
#include "FermiBreakUp/util/Logger.h"

using namespace fbu;

namespace {
  std::array<FermiStr, 3> CacheTypes = {
    "NONE",
    "LAST",
    "LFU",
  };

  std::unique_ptr<VCache<NucleiData, FragmentSplits>> GetCache(const FermiStr& type) {
    if (type == CacheTypes[0]) {
      return nullptr;
    } else if (type == CacheTypes[1]) {
      return std::make_unique<SimpleCache<NucleiData, FragmentSplits>>();
    } else if (type == CacheTypes[2]) {
      return std::make_unique<LFUCache<NucleiData, FragmentSplits>>(10);
    }
    throw std::runtime_error("unknown cache type: " + type);
  }

  FermiFloat RelTolerance(FermiFloat expected, FermiFloat eps, FermiFloat abs = 1e-5) {
    auto relTol = eps * std::abs(expected);
    return std::max(relTol, abs);
  }
} // namespace

float CalculateFragmentCount(
  AtomicMass mass,
  ChargeNumber charge,
  const Vector3& vec,
  FermiFloat energyPerNucleon,
  size_t tests,
  std::unique_ptr<VCache<NucleiData, FragmentSplits>>&& cache = nullptr)
{
  auto model = FermiBreakUp(std::move(cache));
  const auto energy = energyPerNucleon * FermiFloat(mass);
  const auto totalEnergy = std::sqrt(std::pow(NucleiProperties()->GetNuclearMass(mass, charge) + energy, 2) + vec.mag2());
  const auto mom = LorentzVector(vec, totalEnergy);
  const auto particle = Particle(mass, charge, mom);

  size_t partsCounter = 0;
  for (size_t i = 0; i < tests; ++i) {
    const auto particles = model.BreakItUp(particle);
    partsCounter += particles.size();
  }

  return float(partsCounter) / float(tests);
}

class ConfigurationsFixture : public ::testing::TestWithParam<FermiStr> {
 protected:
  FermiStr type;
};

INSTANTIATE_TEST_SUITE_P(
    FermiBreakUpTests,
    ConfigurationsFixture,
    ::testing::Values(
        CacheTypes[0],
        CacheTypes[1],
        CacheTypes[2]
    ));

TEST_P(ConfigurationsFixture, CarbonDecay) {
  Logger::GlobalLevel = LogLevel::ERROR;
  constexpr size_t RUNS = 1e3;

  // Carbons shouldn't break up [0, 0.7]
  ASSERT_NEAR(1, CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 0 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 0.01);
  ASSERT_NEAR(1, CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 0.25 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 0.01);
  ASSERT_NEAR(1, CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 0.5 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 0.01);
  ASSERT_NEAR(1, CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 0.7 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 0.01);

  // Carbons should break into 3 parts [1, 1.4]
  ASSERT_NEAR(3, CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 1 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 0.01);
  ASSERT_NEAR(3, CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 1.25 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 0.01);
  ASSERT_NEAR(3, CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 1.4 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 0.01);

  // Carbons should break into less than 3 parts [1.5, 3.5]
  ASSERT_LE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 1.5 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 3);
  ASSERT_LE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 2 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 3);
  ASSERT_LE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 3 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 3);
  ASSERT_LE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 3.5 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 3);

  // Carbons should break into more than 3 parts [5, ...]
  ASSERT_GE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 5 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 3);
  ASSERT_GE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 7 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 3);
  ASSERT_GE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 9 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 3);
  ASSERT_GE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 20 * CLHEP::MeV, RUNS, GetCache(ConfigurationsFixture::GetParam())), 3);
}

TEST_P(ConfigurationsFixture, UnstableNuclei) {
  Logger::GlobalLevel = LogLevel::ERROR;
  constexpr size_t RUNS = 1e3;

  // protons should break up
  for (int i = 2; i <= 16; ++i) {
    ASSERT_NEAR(i, CalculateFragmentCount(AtomicMass(i), ChargeNumber(i), {0, 0, 0}, 0, RUNS, GetCache(ConfigurationsFixture::GetParam())), 0.01);
  }

  // neutron should break up
  for (int i = 2; i <= 16; ++i) {
    ASSERT_NEAR(i, CalculateFragmentCount(AtomicMass(i), 0_c, {0, 0, 0}, 0, RUNS, GetCache(ConfigurationsFixture::GetParam())), 0.01);
  }
}

TEST_P(ConfigurationsFixture, MomentumConservation) {
  Logger::GlobalLevel = LogLevel::WARN;
  auto model = FermiBreakUp(GetCache(ConfigurationsFixture::GetParam()));
  constexpr int SEED = 5;
  srand(SEED);
  constexpr int TRIES = 500;
  constexpr size_t RUNS = 1e3;
  for (int t = 0; t < TRIES; ++t) {
    const auto mass = AtomicMass(rand() % 16 + 1);
    const auto charge = ChargeNumber(rand() % (int(mass) + 1));
    const auto energy = FermiFloat((rand() % 1000) * CLHEP::MeV * FermiFloat(mass));
    const auto vec = Randomizer::IsotropicVector() * (rand() % 1000) * CLHEP::MeV;
    const auto totalEnergy = std::sqrt(std::pow(NucleiProperties()->GetNuclearMass(mass, charge) + energy, 2) + vec.mag2());
    const auto mom = LorentzVector(vec, totalEnergy);
    const auto particle = Particle(mass, charge, mom);
    for (size_t i = 0; i < RUNS; ++i) {
      const auto particles = model.BreakItUp(particle);

      auto sum = std::accumulate(
        particles.begin(), particles.end(),
        LorentzVector(0, 0, 0, 0),
        [](const auto& a, const auto& b) { return a + b.GetMomentum(); });

      ASSERT_NEAR(sum.m2(), mom.m2(), RelTolerance(mom.m2(), 1e-5)) 
        << "A = " << mass
        << " Z = " << charge
        << " #fragments = " << particles.size();

      ASSERT_NEAR(sum.x(), mom.x(), RelTolerance(mom.x(), 1e-5));
      ASSERT_NEAR(sum.y(), mom.y(), RelTolerance(mom.y(), 1e-5));
      ASSERT_NEAR(sum.z(), mom.z(), RelTolerance(mom.z(), 1e-5));
      ASSERT_NEAR(sum.e(), mom.e(), RelTolerance(mom.e(), 1e-5));
    }
  }
}

TEST_P(ConfigurationsFixture, BaryonAndChargeConservation) {
  Logger::GlobalLevel = LogLevel::ERROR;
  auto model = FermiBreakUp(GetCache(ConfigurationsFixture::GetParam()));
  int SEED = 5;
  srand(SEED);
  int TRIES = 500;
  size_t RUNS = 1e3;
  for (int t = 0; t < TRIES; ++t) {
    const auto mass = AtomicMass(rand() % 16 + 1);
    const auto charge = ChargeNumber(rand() % (int(mass) + 1));
    const auto energy = FermiFloat((rand() % 1000) * CLHEP::MeV * FermiFloat(mass));
    const auto vec = Randomizer::IsotropicVector() * (rand() % 1000) * CLHEP::MeV;
    const auto totalEnergy = std::sqrt(std::pow(NucleiProperties()->GetNuclearMass(mass, charge) + energy, 2) + vec.mag2());
    const auto mom = LorentzVector(vec, totalEnergy);
    const auto particle = Particle(mass, charge, mom);
    for (size_t i = 0; i < RUNS; ++i) {
      const auto particles = model.BreakItUp(particle);

      auto fragmentsMassSum = AtomicMass(0);
      auto fragmentsChargeSum = ChargeNumber(0);
      for (const auto& fragment : particles) {
        fragmentsMassSum = AtomicMass(FermiUInt(fragmentsMassSum) + FermiUInt(fragment.GetAtomicMass()));
        fragmentsChargeSum = ChargeNumber(FermiUInt(fragmentsChargeSum) + FermiUInt(fragment.GetChargeNumber()));
      }
      ASSERT_EQ(fragmentsMassSum, mass);
      ASSERT_EQ(fragmentsChargeSum, charge);
    }
  }
}
