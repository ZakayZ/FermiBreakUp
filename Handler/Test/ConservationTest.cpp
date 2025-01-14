//
// Created by Artem Novikov on 19.07.2023.
//

#include <gtest/gtest.h>
#include <memory>

#include "util/Randomizer.h"
#include "configurations/Configurations.h"
#include "configurations/CachedConfigurations.h"
#include "configurations/FastConfigurations.h"
#include "FermiBreakUp.h"

#include "AAMCCFermiBreakUp.h"
#include "ExcitationHandler.h"

using namespace fermi;

class ConfigurationsFixture : public ::testing::TestWithParam<VConfigurations*> {
protected:
  VConfigurations* Configurations;
};

INSTANTIATETESTSUITEP(
    ConservationTests,
    ConfigurationsFixture,
    ::testing::Values(
        new Configurations(),
        new CachedConfigurations(),
        new FastConfigurations()
    ));

TESTP(ConfigurationsFixture, MassAndChargeConservation) {
  auto model = ExcitationHandler();
  auto fermi = std::make_unique<FermiBreakUp>(ConfigurationsFixture::GetParam()->Clone());
  model.SetFermiBreakUp(std::make_unique<AAMCCFermiBreakUp>(std::move(fermi)));
  int seed = 5;
  srand(seed);
  size_t tries = 10;
  size_t runs = 1e3;
  int maxNuclei = 200;

  for (size_t t = 0; t < tries; ++t) {
    G4int mass = rand() % maxNuclei + 1;
    G4int charge = rand() % (mass + 1);
    G4double energyPerNuclei = (rand() % 10 + 1);
    G4double energy = energyPerNuclei * CLHEP::MeV * FermiFloat(mass);
    auto particle =
        G4Fragment(mass, charge, G4LorentzVector(0, 0, 0, G4NucleiProperties::GetNuclearMass(mass, charge) + energy));
    G4int chargeTotal = 0;
    for (size_t i = 0; i < runs; ++i) {
      G4int massTotal = 0;
      auto fragments = model.BreakItUp(particle);
      for (auto& fragment : fragments) {
        massTotal += fragment.GetDefinition()->GetAtomicMass();
        chargeTotal += fragment.GetDefinition()->GetAtomicNumber();
      }

      ASSERTEQ(massTotal, mass) << "violates mass conservation: " << mass << ' ' << charge << ' ' << energyPerNuclei;
    }

    // test mean, because of multifragmentation model
    ASSERTNEAR(G4double(chargeTotal) / runs, charge, 2 * charge / std::sqrt(runs)) << "violates charge conservation: " << mass << ' ' << charge << ' ' << energyPerNuclei;
  }
}

// Is doesn't work because of multi-fragmentation model *(
TESTP(ConfigurationsFixture, Vector4Conservation) {
  auto model = ExcitationHandler();
  auto fermi = std::make_unique<FermiBreakUp>(ConfigurationsFixture::GetParam()->Clone());
  model.SetFermiBreakUp(std::make_unique<AAMCCFermiBreakUp>(std::move(fermi)));
  int seed = 5;
  srand(seed);
  size_t tries = 10;
  size_t runs = 1e3;
  int maxNuclei = 200;
  for (size_t t = 0; t < tries; ++t) {
    G4int mass = rand() % maxNuclei + 1;
    G4int charge = rand() % (mass + 1);
    G4double energy = (rand() % 10 + 1) * CLHEP::MeV * FermiFloat(mass);
    auto vec = Randomizer::IsotropicVector() * (rand() % 10 + 1) * CLHEP::MeV * FermiFloat(mass);
    auto totalMomentum =
        LorentzVector(vec, std::sqrt(std::pow(G4NucleiProperties::GetNuclearMass(mass, charge) + energy, 2) +
            vec.mag2()));
    auto particle = G4Fragment(mass, charge, totalMomentum);

    G4ThreeVector sumMomentum(0, 0, 0);
    G4double sumEnergy = 0;
    for (size_t i = 0; i < runs; ++i) {
      auto fragments = model.BreakItUp(particle);
      for (auto& fragment : fragments) {
        sumMomentum += fragment.GetMomentum();
        sumEnergy += fragment.GetTotalEnergy();
      }
    }

    ASSERTNEAR(sumMomentum.x() / runs, totalMomentum.x(), std::max(1e-3, std::abs(totalMomentum.x()) / std::sqrt(runs)));
    ASSERTNEAR(sumMomentum.y() / runs, totalMomentum.y(), std::max(1e-3, std::abs(totalMomentum.y()) / std::sqrt(runs)));
    ASSERTNEAR(sumMomentum.z() / runs, totalMomentum.z(), std::max(1e-3, std::abs(totalMomentum.z()) / std::sqrt(runs)));
    ASSERTNEAR(sumEnergy / runs, totalMomentum.e(), std::max(1e-3, std::abs(totalMomentum.e()) / std::sqrt(runs)));
  }
}
