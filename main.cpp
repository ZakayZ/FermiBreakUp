#include <iostream>

#include "Handler/AAMCCFermiBreakUp.h"
#include "FermiBreakUp/FermiBreakUp.h"
#include "utilities/nuclei_properties/data_storage/CSVNuclearMass.h"
#include "utilities/nuclei_properties/NucleiProperties.h"
#include "Handler/ExcitationHandler.h"
#include "configurations/FastConfigurations.h"
#include "configurations/CachedConfigurations.h"
#include "configurations/Configurations.h"

//#include "table_values/NucleiPropertiesTable.h"
//#include "table_values/NucleiPropertiesTableAME12.h"
//
//void DumpTables() {
//  std::ofstream thOut("../TheoreticalTable.data");
//  std::ofstream prOut("../PracticalTable.data");
//  thOut << NucleiPropertiesTable();
//  prOut << NucleiPropertiesTableAME12();
//}

using namespace fermi;

void CalculateFragments(AtomicMass mass,
                        ChargeNumber charge,
                        const std::string& dumpName,
                        FermiFloat step = 0.2,
                        size_t tests = 1e4) {
  auto model = FermiBreakUp();
  std::vector<FermiFloat> energyNucleonValues;
  std::vector<float> avgParts;
  for (FermiFloat energyNucleon = 0; energyNucleon <= 10; energyNucleon += step) {
    size_t partsCounter = 0;
    auto additionalEnergy = energyNucleon * FermiFloat(mass);
    for (size_t i = 0; i < tests; ++i) {
      auto vec = LorentzVector(0, 0, 0, properties::nuclei_properties()->GetNuclearMass(mass, charge) + additionalEnergy);
      auto particles = model.BreakItUp(Particle(mass, charge, vec));
      partsCounter += particles.size();
    }
    avgParts.push_back(float(partsCounter) / float(tests));
    energyNucleonValues.push_back(energyNucleon);
  }

  std::ofstream out(dumpName);

  out << "energy,avgCount\n";
  for (size_t i = 0; i < avgParts.size(); ++i) {
    out << energyNucleonValues[i] << ',' << avgParts[i] << '\n';
  }

  std::cout << dumpName << ": done\n";
}

void CalculateMomentum(AtomicMass mass, ChargeNumber charge, const std::string& dumpName, FermiFloat energy,
                       const Vector3& momentum, size_t tests = 1e4) {
  auto model = FermiBreakUp();
  std::ofstream out(dumpName);
  auto vec = LorentzVector(momentum.x(), momentum.y(), momentum.z(),
                           std::sqrt(std::pow(properties::nuclei_properties()->GetNuclearMass(mass, charge) + energy, 2)
                                         + momentum.mag2()));
  out << vec / mass << '\n';
  std::vector<FermiFloat> xComponent, yComponent, zComponent, magnitude;
  for (size_t i = 0; i < tests; ++i) {
    auto particles = model.BreakItUp(Particle(mass, charge, vec));
    auto sum = LorentzVector();
    for (const auto& particle : particles) {
      sum += particle.GetMomentum();
      out << particle.GetMomentum() / particle.GetAtomicMass() << ' ';
    }
    out << '\n';
  }

  std::cout << dumpName << ": done\n";
}

void CalculateFragmentsHandler(AtomicMass mass, ChargeNumber charge, const std::string& dumpName,
                               FermiFloat excessEnergy, size_t tests = 1e4, bool log = false) {
  auto handler = ExcitationHandler();
  std::ofstream out(dumpName);

  out << "[\n";
  for (size_t i = 0; i < tests; ++i) {
    auto vec =
        LorentzVector(0, 0, 0, G4NucleiProperties::GetNuclearMass(FermiInt(mass), FermiInt(charge)) + excessEnergy * FermiFloat(mass));
    auto particles = handler.BreakItUp(G4Fragment(mass, charge, vec));
    out << " [";
    size_t id = 0;
    for (auto& particle : particles) {
      out << "{ \"A\":" << particle.GetDefinition()->GetAtomicMass() << ", \"Z\": "
          << particle.GetDefinition()->GetPDGCharge() << " }";
      ++id;
      if (id != particles.size()) {
        out << ", ";
      }
    }
    out << ']';
    if (i != tests - 1) {
      out << ',';
    }
    out << '\n';

    if (log) {
      std::cout << i << '\n';
    }
  }

  out << "]\n";

  std::cout << dumpName << ": done\n";
}

void CalculateMomentumHandler(G4int mass, G4int charge, const std::string& dumpName, FermiFloat energy,
                       const Vector3& momentum, size_t tests = 1e4) {
  auto model = ExcitationHandler();
  auto fermi = std::make_unique<FermiBreakUp>(std::make_unique<FastConfigurations>());
  model.SetFermiBreakUp(std::make_unique<AAMCCFermiBreakUp>(std::move(fermi)));
  std::ofstream out(dumpName);
  auto vec = LorentzVector(momentum.x(), momentum.y(), momentum.z(),
                           std::sqrt(std::pow(G4NucleiProperties::GetNuclearMass(mass, charge) + energy, 2)
                                         + momentum.mag2()));
  out << vec / mass << '\n';
  std::vector<FermiFloat> xComponent, yComponent, zComponent, magnitude;
  for (size_t i = 0; i < tests; ++i) {
    auto particles = model.BreakItUp(G4Fragment(mass, charge, vec));
    for (const auto& particle : particles) {
      if (particle.GetDefinition()->GetAtomicMass() > 0) {
        out << LorentzVector(particle.GetMomentum(), particle.GetTotalEnergy()) / particle.GetDefinition()->GetAtomicMass() << ' ';
      }
    }
    out << '\n';
  }

  std::cout << dumpName << ": done\n";
}

int main() {
//  CalculateMomentum(2_m, 6_c, "../Results/stat.data", 12 * 10 * CLHEP::GeV, {0, 0, 0});
//  CalculateMomentum(2_m, 6_c, "../Results/movX.data", 12 * 5 * CLHEP::MeV, {12 * 10 * CLHEP::GeV, 0, 0});
//  CalculateMomentum(2_m, 6_c, "../Results/movY.data", 12 * 5 * CLHEP::MeV, {0, 12 * 10 * CLHEP::GeV, 0});
//  CalculateMomentum(2_m, 6_c, "../Results/movZ.data", 12 * 5 * CLHEP::MeV, {0, 0, 12 * 10 * CLHEP::GeV});
//
//  CalculateFragments(2_m, 6_c, "../Results/C12.csv");
//
//  CalculateFragments(3_m, 6_c, "../Results/C13.csv");
//
//  CalculateFragments(2_m, 7_c, "../Results/N12.csv");
//
//  CalculateFragments(3_m, 7_c, "../Results/N13.csv");

  CalculateFragmentsHandler(2_m, 6_c, "../Results/C12_05Distr.dat", 0.5 * CLHEP::MeV);

  CalculateFragmentsHandler(2_m, 6_c, "../Results/C12_4Distr.dat", 4 * CLHEP::MeV);

//  CalculateFragmentsHandler(3_m, 6_c, "../Results/C13_05Distr.dat", 0.5 * CLHEP::MeV);
//
//  CalculateFragmentsHandler(3_m, 6_c, "../Results/C13_4Distr.dat", 4 * CLHEP::MeV);
//
//  CalculateFragmentsHandler(2_m, 7_c, "../Results/N12_05Distr.dat", 0.5 * CLHEP::MeV);
//
//  CalculateFragmentsHandler(2_m, 7_c, "../Results/N12_4Distr.dat", 4 * CLHEP::MeV);
//
//  CalculateFragmentsHandler(3_m, 7_c, "../Results/N13_05Distr.dat", 0.5 * CLHEP::MeV);
//
//  CalculateFragmentsHandler(3_m, 7_c, "../Results/N13_4Distr.dat", 4 * CLHEP::MeV);

//  CalculateFragmentsHandler(7_m, 9_c, "../Results/Au197_05Distr.dat", 0.5 * CLHEP::MeV, 1000);
//
//  CalculateFragmentsHandler(7_m, 9_c, "../Results/Au197_4Distr.dat", 4 * CLHEP::MeV, 1000);

//  G4double energy = 4;
//  CalculateMomentumHandler(197, 79, "../Results/auStat.data", 197 * energy * CLHEP::MeV, {0, 0, 0}, 1000);
//  CalculateMomentumHandler(197, 79, "../Results/auMovX.data", 197 * energy * CLHEP::MeV, {197 * energy * CLHEP::GeV, 0, 0}, 1000);
//  CalculateMomentumHandler(197, 79, "../Results/auMovY.data", 197 * energy * CLHEP::MeV, {0, 197 * energy * CLHEP::GeV, 0}, 1000);
//  CalculateMomentumHandler(197, 79, "../Results/auMovZ.data", 197 * energy * CLHEP::MeV, {0, 0, 197 * energy * CLHEP::GeV}, 1000);
}
