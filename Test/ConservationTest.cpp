//
// Created by Artem Novikov on 19.07.2023.
//

#include <gtest/gtest.h>

#include "Handler/ExcitationHandler.h"
#include "Utilities/Randomizer.h"

TEST(ConservationTests, MassAndChargeConservation) {
  auto model = ExcitationHandler();
  int seed = 5;
  srand(seed);
  size_t tries = 15;
  size_t runs = 1e3;
  int max_nuclei = 200;

  for (size_t t = 0; t < tries; ++t) {
    G4int mass = rand() % max_nuclei + 1;
    G4int charge = rand() % (mass + 1);
    G4double energy = (rand() % 10 + 1) * CLHEP::MeV * FermiFloat(mass);
    auto particle =
        G4Fragment(mass, charge, G4LorentzVector(0, 0, 0, G4NucleiProperties::GetNuclearMass(mass, charge) + energy));
    G4int charge_total = 0;
    for (size_t i = 0; i < runs; ++i) {
      G4int mass_total = 0;
      auto fragments = model.BreakItUp(particle);
      for (auto& fragment : fragments) {
        mass_total += fragment.GetDefinition()->GetAtomicMass();
        charge_total += fragment.GetDefinition()->GetPDGCharge();
      }

      ASSERT_EQ(mass_total, mass);
    }

    /// test mean, because of multifragmentation model
    ASSERT_NEAR(G4double(charge_total) / runs, charge, charge / std::sqrt(runs));
  }
}

TEST(ConservationTests, Vector4Conservation) {
  auto model = ExcitationHandler();
  int seed = 5;
  srand(seed);
  size_t tries = 10;
  size_t runs = 1e3;
  int max_nuclei = 200;
  for (size_t t = 0; t < tries; ++t) {
    G4int mass = rand() % max_nuclei + 1;
    G4int charge = rand() % (mass + 1);
    G4double energy = (rand() % 10 + 1) * CLHEP::MeV * FermiFloat(mass);
    auto vec = Randomizer::IsotropicVector() * (rand() % 10 + 1) * CLHEP::MeV * FermiFloat(mass);
    auto total_momentum =
        LorentzVector(vec, std::sqrt(std::pow(G4NucleiProperties::GetNuclearMass(mass, charge) + energy, 2) +
            vec.mag2()));
    auto particle = G4Fragment(mass, charge, total_momentum);

    G4ThreeVector sum_momentum(0, 0, 0);
    G4double sum_energy = 0;
    for (size_t i = 0; i < runs; ++i) {
      auto fragments = model.BreakItUp(particle);
      for (auto& fragment : fragments) {
        sum_momentum += fragment.GetMomentum();
        sum_energy += fragment.GetTotalEnergy();
      }
    }

    ASSERT_NEAR(sum_momentum.x() / runs, total_momentum.x(), std::max(1e-3, std::abs(total_momentum.x()) / std::sqrt(runs)));
    ASSERT_NEAR(sum_momentum.y() / runs, total_momentum.y(), std::max(1e-3, std::abs(total_momentum.y()) / std::sqrt(runs)));
    ASSERT_NEAR(sum_momentum.z() / runs, total_momentum.z(), std::max(1e-3, std::abs(total_momentum.z()) / std::sqrt(runs)));
    ASSERT_NEAR(sum_energy / runs, total_momentum.e(), std::max(1e-3, std::abs(total_momentum.e()) / std::sqrt(runs)));
  }
}
