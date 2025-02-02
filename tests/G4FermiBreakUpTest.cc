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

#include "G4FermiBreakUp.hh"

#include "util/G4FermiCache.hh"
#include "util/G4FermiDataTypes.hh"
#include "util/G4FermiLogger.hh"
#include "util/G4FermiRandomizer.hh"
#include "util/nuclei_properties/G4FermiNucleiProperties.hh"
#include <CLHEP/Units/PhysicalConstants.h>
#include <gtest/gtest.h>

#include <exception>
#include <numeric>

using namespace fbu;

namespace
{
std::array<G4FermiStr, 3> CacheTypes = {
  "NONE",
  "LAST",
  "LFU",
};

std::unique_ptr<G4FermiVCache<G4FermiNucleiData, G4FermiPossibleFragmentSplits>>
GetCache(const G4FermiStr& type)
{
  if (type == CacheTypes[0]) {
    return nullptr;
  }
  else if (type == CacheTypes[1]) {
    return std::make_unique<G4FermiSimpleCache<G4FermiNucleiData, G4FermiPossibleFragmentSplits>>();
  }
  else if (type == CacheTypes[2]) {
    return std::make_unique<G4FermiLFUCache<G4FermiNucleiData, G4FermiPossibleFragmentSplits>>(10);
  }
  throw std::runtime_error("unknown cache type: " + type);
}

G4FermiFloat RelTolerance(G4FermiFloat expected, G4FermiFloat eps, G4FermiFloat abs = 1e-5)
{
  auto relTol = eps * std::abs(expected);
  return std::max(relTol, abs);
}
}  // namespace

float CalculateFragmentCount(
  G4FermiAtomicMass mass, G4FermiChargeNumber charge, const G4FermiVector3& vec,
  G4FermiFloat energyPerNucleon, size_t tests,
  std::unique_ptr<G4FermiVCache<G4FermiNucleiData, G4FermiPossibleFragmentSplits>>&& cache =
    nullptr)
{
  auto model = G4FermiBreakUp(std::move(cache));
  const auto energy = energyPerNucleon * G4FermiFloat(mass);
  const auto totalEnergy = std::sqrt(
    std::pow(G4FermiNucleiProperties()->GetNuclearMass(mass, charge) + energy, 2) + vec.mag2());
  const auto mom = G4FermiLorentzVector(vec, totalEnergy);
  const auto particle = G4FermiParticle(mass, charge, mom);

  size_t partsCounter = 0;
  for (size_t i = 0; i < tests; ++i) {
    const auto particles = model.BreakItUp(particle);
    partsCounter += particles.size();
  }

  return float(partsCounter) / float(tests);
}

class G4FermiConfigurationsFixture : public ::testing::TestWithParam<G4FermiStr>
{
  protected:
    G4FermiStr type;
};

INSTANTIATE_TEST_SUITE_P(FermiBreakUpTests, G4FermiConfigurationsFixture,
                         ::testing::Values(CacheTypes[0], CacheTypes[1], CacheTypes[2]));

TEST_P(G4FermiConfigurationsFixture, CarbonDecay)
{
  G4FermiLogger::GlobalLevel = G4FermiLogLevel::ERROR;
  constexpr size_t RUNS = 1e3;

  // Carbons shouldn't break up [0, 0.7]
  ASSERT_NEAR(1,
              CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 0 * CLHEP::MeV, RUNS,
                                     GetCache(G4FermiConfigurationsFixture::GetParam())),
              0.01);
  ASSERT_NEAR(1,
              CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 0.25 * CLHEP::MeV, RUNS,
                                     GetCache(G4FermiConfigurationsFixture::GetParam())),
              0.01);
  ASSERT_NEAR(1,
              CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 0.5 * CLHEP::MeV, RUNS,
                                     GetCache(G4FermiConfigurationsFixture::GetParam())),
              0.01);
  ASSERT_NEAR(1,
              CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 0.7 * CLHEP::MeV, RUNS,
                                     GetCache(G4FermiConfigurationsFixture::GetParam())),
              0.01);

  // Carbons should break into 3 parts [1, 1.4]
  ASSERT_NEAR(3,
              CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 1 * CLHEP::MeV, RUNS,
                                     GetCache(G4FermiConfigurationsFixture::GetParam())),
              0.01);
  ASSERT_NEAR(3,
              CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 1.25 * CLHEP::MeV, RUNS,
                                     GetCache(G4FermiConfigurationsFixture::GetParam())),
              0.01);
  ASSERT_NEAR(3,
              CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 1.4 * CLHEP::MeV, RUNS,
                                     GetCache(G4FermiConfigurationsFixture::GetParam())),
              0.01);

  // Carbons should break into less than 3 parts [1.5, 3.5]
  ASSERT_LE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 1.5 * CLHEP::MeV, RUNS,
                                   GetCache(G4FermiConfigurationsFixture::GetParam())),
            3);
  ASSERT_LE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 2 * CLHEP::MeV, RUNS,
                                   GetCache(G4FermiConfigurationsFixture::GetParam())),
            3);
  ASSERT_LE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 3 * CLHEP::MeV, RUNS,
                                   GetCache(G4FermiConfigurationsFixture::GetParam())),
            3);
  ASSERT_LE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 3.5 * CLHEP::MeV, RUNS,
                                   GetCache(G4FermiConfigurationsFixture::GetParam())),
            3);

  // Carbons should break into more than 3 parts [5, ...]
  ASSERT_GE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 5 * CLHEP::MeV, RUNS,
                                   GetCache(G4FermiConfigurationsFixture::GetParam())),
            3);
  ASSERT_GE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 7 * CLHEP::MeV, RUNS,
                                   GetCache(G4FermiConfigurationsFixture::GetParam())),
            3);
  ASSERT_GE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 9 * CLHEP::MeV, RUNS,
                                   GetCache(G4FermiConfigurationsFixture::GetParam())),
            3);
  ASSERT_GE(CalculateFragmentCount(12_m, 6_c, {0, 0, 0}, 20 * CLHEP::MeV, RUNS,
                                   GetCache(G4FermiConfigurationsFixture::GetParam())),
            3);
}

TEST_P(G4FermiConfigurationsFixture, UnstableNuclei)
{
  G4FermiLogger::GlobalLevel = G4FermiLogLevel::ERROR;
  constexpr size_t RUNS = 1e3;

  // protons should break up
  for (int i = 2; i <= 16; ++i) {
    ASSERT_NEAR(i,
                CalculateFragmentCount(G4FermiAtomicMass(i), G4FermiChargeNumber(i), {0, 0, 0}, 0,
                                       RUNS, GetCache(G4FermiConfigurationsFixture::GetParam())),
                0.01);
  }

  // neutron should break up
  for (int i = 2; i <= 16; ++i) {
    ASSERT_NEAR(i,
                CalculateFragmentCount(G4FermiAtomicMass(i), 0_c, {0, 0, 0}, 0, RUNS,
                                       GetCache(G4FermiConfigurationsFixture::GetParam())),
                0.01);
  }
}

TEST_P(G4FermiConfigurationsFixture, MomentumConservation)
{
  G4FermiLogger::GlobalLevel = G4FermiLogLevel::WARN;
  auto model = G4FermiBreakUp(GetCache(G4FermiConfigurationsFixture::GetParam()));
  constexpr int SEED = 5;
  srand(SEED);
  constexpr int TRIES = 500;
  constexpr size_t RUNS = 1e3;
  for (int t = 0; t < TRIES; ++t) {
    const auto mass = G4FermiAtomicMass(rand() % 16 + 1);
    const auto charge = G4FermiChargeNumber(rand() % (int(mass) + 1));
    const auto energy = G4FermiFloat((rand() % 1000) * CLHEP::MeV * G4FermiFloat(mass));
    const auto vec = G4FermiRandomizer::IsotropicVector() * (rand() % 1000) * CLHEP::MeV;
    const auto totalEnergy = std::sqrt(
      std::pow(G4FermiNucleiProperties()->GetNuclearMass(mass, charge) + energy, 2) + vec.mag2());
    const auto mom = G4FermiLorentzVector(vec, totalEnergy);
    const auto particle = G4FermiParticle(mass, charge, mom);
    for (size_t i = 0; i < RUNS; ++i) {
      const auto particles = model.BreakItUp(particle);

      auto sum =
        std::accumulate(particles.begin(), particles.end(), G4FermiLorentzVector(0, 0, 0, 0),
                        [](const auto& a, const auto& b) { return a + b.GetMomentum(); });

      ASSERT_NEAR(sum.m2(), mom.m2(), RelTolerance(mom.m2(), 1e-5))
        << "A = " << mass << " Z = " << charge << " #fragments = " << particles.size();

      ASSERT_NEAR(sum.x(), mom.x(), RelTolerance(mom.x(), 1e-5));
      ASSERT_NEAR(sum.y(), mom.y(), RelTolerance(mom.y(), 1e-5));
      ASSERT_NEAR(sum.z(), mom.z(), RelTolerance(mom.z(), 1e-5));
      ASSERT_NEAR(sum.e(), mom.e(), RelTolerance(mom.e(), 1e-5));
    }
  }
}

TEST_P(G4FermiConfigurationsFixture, BaryonAndChargeConservation)
{
  G4FermiLogger::GlobalLevel = G4FermiLogLevel::ERROR;
  auto model = G4FermiBreakUp(GetCache(G4FermiConfigurationsFixture::GetParam()));
  int SEED = 5;
  srand(SEED);
  int TRIES = 500;
  size_t RUNS = 1e3;
  for (int t = 0; t < TRIES; ++t) {
    const auto mass = G4FermiAtomicMass(rand() % 16 + 1);
    const auto charge = G4FermiChargeNumber(rand() % (int(mass) + 1));
    const auto energy = G4FermiFloat((rand() % 1000) * CLHEP::MeV * G4FermiFloat(mass));
    const auto vec = G4FermiRandomizer::IsotropicVector() * (rand() % 1000) * CLHEP::MeV;
    const auto totalEnergy = std::sqrt(
      std::pow(G4FermiNucleiProperties()->GetNuclearMass(mass, charge) + energy, 2) + vec.mag2());
    const auto mom = G4FermiLorentzVector(vec, totalEnergy);
    const auto particle = G4FermiParticle(mass, charge, mom);
    for (size_t i = 0; i < RUNS; ++i) {
      const auto particles = model.BreakItUp(particle);

      auto fragmentsMassSum = G4FermiAtomicMass(0);
      auto fragmentsChargeSum = G4FermiChargeNumber(0);
      for (const auto& fragment : particles) {
        fragmentsMassSum =
          G4FermiAtomicMass(G4FermiUInt(fragmentsMassSum) + G4FermiUInt(fragment.GetAtomicMass()));
        fragmentsChargeSum = G4FermiChargeNumber(G4FermiUInt(fragmentsChargeSum)
                                                 + G4FermiUInt(fragment.GetChargeNumber()));
      }
      ASSERT_EQ(fragmentsMassSum, mass);
      ASSERT_EQ(fragmentsChargeSum, charge);
    }
  }
}
