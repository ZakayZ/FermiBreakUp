#include <iostream>

#include "Handler/AAMCCFermiBreakUp.h"
#include "FermiBreakUp/FermiBreakUp.h"
#include "Utilities/NucleiProperties/DataStorage/CSVNuclearMass.h"
#include "Utilities/NucleiProperties/NucleiProperties.h"
#include "Handler/ExcitationHandler.h"
#include "Configurations/FastFermiConfigurations.h"
#include "Configurations/CachedFermiConfigurations.h"
#include "Configurations/FermiConfigurations.h"

//#include "TableValues/NucleiPropertiesTable.h"
//#include "TableValues/NucleiPropertiesTableAME12.h"
//
//void DumpTables() {
//  std::ofstream th_out("../TheoreticalTable.data");
//  std::ofstream pr_out("../PracticalTable.data");
//  th_out << NucleiPropertiesTable();
//  pr_out << NucleiPropertiesTableAME12();
//}

using namespace fermi;

void CalculateFragments(MassNumber mass,
                        ChargeNumber charge,
                        const std::string& dump_name,
                        FermiFloat step = 0.2,
                        size_t tests = 1e4) {
  auto model = FermiBreakUp();
  std::vector<FermiFloat> energy_nucleon_values;
  std::vector<float> avg_parts;
  for (FermiFloat energy_nucleon = 0; energy_nucleon <= 10; energy_nucleon += step) {
    size_t parts_counter = 0;
    auto additional_energy = energy_nucleon * FermiFloat(mass);
    for (size_t i = 0; i < tests; ++i) {
      auto vec = LorentzVector(0, 0, 0, properties::NucleiProperties()->GetNuclearMass(mass, charge) + additional_energy);
      auto particles = model.BreakItUp(FermiParticle(mass, charge, vec));
      parts_counter += particles.size();
    }
    avg_parts.push_back(float(parts_counter) / float(tests));
    energy_nucleon_values.push_back(energy_nucleon);
  }

  std::ofstream out(dump_name);

  out << "energy,avg_count\n";
  for (size_t i = 0; i < avg_parts.size(); ++i) {
    out << energy_nucleon_values[i] << ',' << avg_parts[i] << '\n';
  }

  std::cout << dump_name << ": done\n";
}

void CalculateMomentum(MassNumber mass, ChargeNumber charge, const std::string& dump_name, FermiFloat energy,
                       const Vector3& momentum, size_t tests = 1e4) {
  auto model = FermiBreakUp();
  std::ofstream out(dump_name);
  auto vec = LorentzVector(momentum.x(), momentum.y(), momentum.z(),
                           std::sqrt(std::pow(properties::NucleiProperties()->GetNuclearMass(mass, charge) + energy, 2)
                                         + momentum.mag2()));
  out << vec / mass << '\n';
  std::vector<FermiFloat> x_component, y_component, z_component, magnitude;
  for (size_t i = 0; i < tests; ++i) {
    auto particles = model.BreakItUp(FermiParticle(mass, charge, vec));
    auto sum = LorentzVector();
    for (const auto& particle : particles) {
      sum += particle.GetMomentum();
      out << particle.GetMomentum() / particle.GetMassNumber() << ' ';
    }
    out << '\n';
  }

  std::cout << dump_name << ": done\n";
}

void CalculateFragmentsHandler(MassNumber mass, ChargeNumber charge, const std::string& dump_name,
                               FermiFloat excess_energy, size_t tests = 1e4, bool log = false) {
  auto handler = ExcitationHandler();
  std::ofstream out(dump_name);

  out << "[\n";
  for (size_t i = 0; i < tests; ++i) {
    auto vec =
        LorentzVector(0, 0, 0, G4NucleiProperties::GetNuclearMass(FermiInt(mass), FermiInt(charge)) + excess_energy * FermiFloat(mass));
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

  std::cout << dump_name << ": done\n";
}

void CalculateMomentumHandler(G4int mass, G4int charge, const std::string& dump_name, FermiFloat energy,
                       const Vector3& momentum, size_t tests = 1e4) {
  auto model = ExcitationHandler();
  auto fermi = std::make_unique<FermiBreakUp>(std::make_unique<FastFermiConfigurations>());
  model.SetFermiBreakUp(std::make_unique<AAMCCFermiBreakUp>(std::move(fermi)));
  std::ofstream out(dump_name);
  auto vec = LorentzVector(momentum.x(), momentum.y(), momentum.z(),
                           std::sqrt(std::pow(G4NucleiProperties::GetNuclearMass(mass, charge) + energy, 2)
                                         + momentum.mag2()));
  out << vec / mass << '\n';
  std::vector<FermiFloat> x_component, y_component, z_component, magnitude;
  for (size_t i = 0; i < tests; ++i) {
    auto particles = model.BreakItUp(G4Fragment(mass, charge, vec));
    for (const auto& particle : particles) {
      if (particle.GetDefinition()->GetAtomicMass() > 0) {
        out << LorentzVector(particle.GetMomentum(), particle.GetTotalEnergy()) / particle.GetDefinition()->GetAtomicMass() << ' ';
      }
    }
    out << '\n';
  }

  std::cout << dump_name << ": done\n";
}

int main() {
//  CalculateMomentum(12_m, 6_c, "../Results/stat.data", 12 * 10 * CLHEP::GeV, {0, 0, 0});
//  CalculateMomentum(12_m, 6_c, "../Results/mov_x.data", 12 * 5 * CLHEP::MeV, {12 * 10 * CLHEP::GeV, 0, 0});
//  CalculateMomentum(12_m, 6_c, "../Results/mov_y.data", 12 * 5 * CLHEP::MeV, {0, 12 * 10 * CLHEP::GeV, 0});
//  CalculateMomentum(12_m, 6_c, "../Results/mov_z.data", 12 * 5 * CLHEP::MeV, {0, 0, 12 * 10 * CLHEP::GeV});
//
//  CalculateFragments(12_m, 6_c, "../Results/C12.csv");
//
//  CalculateFragments(13_m, 6_c, "../Results/C13.csv");
//
//  CalculateFragments(12_m, 7_c, "../Results/N12.csv");
//
//  CalculateFragments(13_m, 7_c, "../Results/N13.csv");

  CalculateFragmentsHandler(12_m, 6_c, "../Results/C12_05_distr.dat", 0.5 * CLHEP::MeV);

  CalculateFragmentsHandler(12_m, 6_c, "../Results/C12_4_distr.dat", 4 * CLHEP::MeV);

//  CalculateFragmentsHandler(13_m, 6_c, "../Results/C13_05_distr.dat", 0.5 * CLHEP::MeV);
//
//  CalculateFragmentsHandler(13_m, 6_c, "../Results/C13_4_distr.dat", 4 * CLHEP::MeV);
//
//  CalculateFragmentsHandler(12_m, 7_c, "../Results/N12_05_distr.dat", 0.5 * CLHEP::MeV);
//
//  CalculateFragmentsHandler(12_m, 7_c, "../Results/N12_4_distr.dat", 4 * CLHEP::MeV);
//
//  CalculateFragmentsHandler(13_m, 7_c, "../Results/N13_05_distr.dat", 0.5 * CLHEP::MeV);
//
//  CalculateFragmentsHandler(13_m, 7_c, "../Results/N13_4_distr.dat", 4 * CLHEP::MeV);

//  CalculateFragmentsHandler(197_m, 79_c, "../Results/Au197_05_distr.dat", 0.5 * CLHEP::MeV, 1000);
//
//  CalculateFragmentsHandler(197_m, 79_c, "../Results/Au197_4_distr.dat", 4 * CLHEP::MeV, 1000);

//  G4double energy = 4;
//  CalculateMomentumHandler(197, 79, "../Results/au_stat.data", 197 * energy * CLHEP::MeV, {0, 0, 0}, 1000);
//  CalculateMomentumHandler(197, 79, "../Results/au_mov_x.data", 197 * energy * CLHEP::MeV, {197 * energy * CLHEP::GeV, 0, 0}, 1000);
//  CalculateMomentumHandler(197, 79, "../Results/au_mov_y.data", 197 * energy * CLHEP::MeV, {0, 197 * energy * CLHEP::GeV, 0}, 1000);
//  CalculateMomentumHandler(197, 79, "../Results/au_mov_z.data", 197 * energy * CLHEP::MeV, {0, 0, 197 * energy * CLHEP::GeV}, 1000);
}
