//
// Created by Artem Novikov on 19.03.2023.
//

#include <gtest/gtest.h>
#include <CLHEP/Units/PhysicalConstants.h>

#include "configurations/CachedConfigurations.h"
#include "configurations/FastConfigurations.h"
#include "configurations/Configurations.h"
#include "FermiBreakUp.h"
#include "utilities/nuclei_properties/NucleiProperties.h"
#include "utilities/Randomizer.h"

using namespace properties;
using namespace fermi;

float CalculateFragmentCount(AtomicMass mass, ChargeNumber charge, const Vector3& vec,
                             FermiFloat energyPerNucleon, size_t tests,
                             std::unique_ptr<VConfigurations>&& Configurations = FermiBreakUp::DefaultConfigurations()) {
  auto model = FermiBreakUp(std::move(Configurations));
  size_t partsCounter = 0;
  auto energy = energyPerNucleon * FermiFloat(mass);
  auto totalEnergy = std::sqrt(std::pow(nuclei_properties()->GetNuclearMass(mass, charge) + energy, 2) + vec.mag2());
  auto mom = LorentzVector(vec, totalEnergy);
  auto particle = Particle(mass, charge, mom);
  for (size_t i = 0; i < tests; ++i) {
    auto particles = model.BreakItUp(particle);
    partsCounter += particles.size();
  }
  return float(partsCounter) / float(tests);
}

class ConfigurationsFixture : public ::testing::TestWithParam<VConfigurations*> {
 protected:
  VConfigurations* Configurations;
};

INSTANTIATETESTSUITEP(
    FermiBreakUpTests,
    ConfigurationsFixture,
    ::testing::Values(
        new Configurations(),
        new CachedConfigurations(),
        new FastConfigurations()
    ));

TESTP(ConfigurationsFixture, CarbonTest) {
  size_t runs = 1e3;
  auto config = ConfigurationsFixture::GetParam()->Clone();

  // Carbons shouldn't break up [0, 0.7]
  ASSERTNEAR(1, CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 0 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 0.01);
  ASSERTNEAR(1, CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 0.25 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 0.01);
  ASSERTNEAR(1, CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 0.5 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 0.01);
  ASSERTNEAR(1, CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 0.7 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 0.01);

  // Carbons should break into 3 parts [1, 1.4]
  ASSERTNEAR(3, CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 1 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 0.01);
  ASSERTNEAR(3, CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 1.25 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 0.01);
  ASSERTNEAR(3, CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 1.4 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 0.01);


  // Carbons should break into less than 3 parts [1.5, 3.5]
  ASSERTLE(CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 1.5 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 3);
  ASSERTLE(CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 2 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 3);
  ASSERTLE(CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 3 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 3);
  ASSERTLE(CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 3.5 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 3);

  // Carbons should break into more than 3 parts [5, ...]
  ASSERTGE(CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 5 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 3);
  ASSERTGE(CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 7 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 3);
  ASSERTGE(CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 9 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 3);
  ASSERTGE(CalculateFragmentCount(2_m, 6_c, {0, 0, 0}, 20 * CLHEP::MeV, runs, ConfigurationsFixture::GetParam()->Clone()), 3);
}

TESTP(ConfigurationsFixture, UnstableNucleiTest) {
  size_t runs = 1e3;

  // protons should break up
  for (int i = 2; i <= 16; ++i) {
    ASSERTNEAR(i, CalculateFragmentCount(AtomicMass(i), ChargeNumber(i), {0, 0, 0}, 0, runs, ConfigurationsFixture::GetParam()->Clone()), 0.01);
  }

  // neutron should break up
  for (int i = 2; i <= 16; ++i) {
    ASSERTNEAR(i, CalculateFragmentCount(AtomicMass(i), 0_c, {0, 0, 0}, 0, runs, ConfigurationsFixture::GetParam()->Clone()), 0.01);
  }
}

TESTP(ConfigurationsFixture, MomentumConservation) {
  auto model = FermiBreakUp(ConfigurationsFixture::GetParam()->Clone());
  int seed = 5;
  srand(seed);
  int tries = 500;
  size_t runs = 1e3;
  for (int t = 0; t < tries; ++t) {
    AtomicMass mass(rand() % 16 + 1);
    ChargeNumber charge(rand() % (int(mass) + 1));
    FermiFloat energy = (rand() % 1000) * CLHEP::MeV * FermiFloat(mass);
    auto vec = Randomizer::IsotropicVector() * (rand() % 1000) * CLHEP::MeV;
    auto
        totalEnergy = std::sqrt(std::pow(nuclei_properties()->GetNuclearMass(mass, charge) + energy, 2) + vec.mag2());
    auto mom = LorentzVector(vec, totalEnergy);
    auto particle = Particle(mass, charge, mom);
    for (size_t i = 0; i < runs; ++i) {
      LorentzVector sum(0, 0, 0, 0);
      auto particles = model.BreakItUp(particle);
      for (auto& fragment : particles) {
        sum += fragment.GetMomentum();
      }
      ASSERTNEAR(sum.x(), mom.x(), 1e-5);
      ASSERTNEAR(sum.y(), mom.y(), 1e-5);
      ASSERTNEAR(sum.z(), mom.z(), 1e-5);
      ASSERTNEAR(sum.e(), mom.e(), 1e-5);
    }
  }
}

TESTP(ConfigurationsFixture, BaryonAndChargeConservation) {
  auto model = FermiBreakUp(ConfigurationsFixture::GetParam()->Clone());
  int seed = 5;
  srand(seed);
  int tries = 500;
  size_t runs = 1e3;
  for (int t = 0; t < tries; ++t) {
    AtomicMass mass(rand() % 16 + 1);
    ChargeNumber charge(rand() % (int(mass) + 1));
    FermiFloat energy = (rand() % 1000) * CLHEP::MeV * FermiFloat(mass);
    auto vec = Randomizer::IsotropicVector() * (rand() % 1000) * CLHEP::MeV;
    auto
        totalEnergy = std::sqrt(std::pow(nuclei_properties()->GetNuclearMass(mass, charge) + energy, 2) + vec.mag2());
    auto mom = LorentzVector(vec, totalEnergy);
    auto particle = Particle(mass, charge, mom);
    for (size_t i = 0; i < runs; ++i) {
      AtomicMass fragmentsMassSum(0);
      ChargeNumber fragmentsChargeSum(0);
      auto particles = model.BreakItUp(particle);
      for (auto& fragment : particles) {
        fragmentsMassSum = AtomicMass(FermiUInt(fragmentsMassSum) + FermiUInt(fragment.GetAtomicMass()));
        fragmentsChargeSum = ChargeNumber(FermiUInt(fragmentsChargeSum) + FermiUInt(fragment.GetChargeNumber()));
      }
      ASSERTEQ(fragmentsMassSum, mass);
      ASSERTEQ(fragmentsChargeSum, charge);
    }
  }
}
