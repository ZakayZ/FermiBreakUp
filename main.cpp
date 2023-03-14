#include <iostream>
#include <fstream>
#include <CLHEP/Units/PhysicalConstants.h>
#include "MyFermiBreakUp/IntegerPartition.h"
#include "NucleiProperties/NucleiProperties.h"
#include "MyFermiBreakUp/FermiBreakUp.h"
#include "TableValues/NucleiPropertiesTable.h"
#include "TableValues/NucleiPropertiesTableAME12.h"

void DumpTables() {
  std::ofstream th_out("../TheoreticalTable.data");
  std::ofstream pr_out("../PracticalTable.data");
  th_out << NucleiPropertiesTable();
  pr_out << NucleiPropertiesTableAME12();
}

void CalculateFragments(MassNumber mass,
                        ChargeNumber charge,
                        const std::string& dump_name,
                        FermiFloat step = 0.2,
                        size_t tests = 1e4) {
  std::vector<FermiFloat> energy_nucleon_values;
  std::vector<float> avg_parts;
  for (FermiFloat energy_nucleon = 0; energy_nucleon <= 10; energy_nucleon += step) {
    size_t parts_counter = 0;
    auto additional_energy = energy_nucleon * FermiFloat(mass);
    for (size_t i = 0; i < tests; ++i) {
      auto vec = LorentzVector(0, 0, 0, NucleiProperties().GetNuclearMass(mass, charge) + additional_energy);
      auto particles = FermiBreakUp::BreakItUp(FermiParticle(mass, charge, vec));
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
                       const Vector3& momentum, size_t tests = 1e3) {
  std::ofstream out(dump_name);
  auto vec = LorentzVector(momentum.x(), momentum.y(), momentum.z(),
                           NucleiProperties().GetNuclearMass(mass, charge) + energy + momentum.mag());
  out << vec / mass << '\n';
  std::vector<FermiFloat> x_component, y_component, z_component, magnitude;
  for (size_t i = 0; i < tests; ++i) {
    auto particles = FermiBreakUp::BreakItUp(FermiParticle(mass, charge, vec));
    auto sum = LorentzVector();
    for (const auto& particle : particles) {
      sum += particle.GetMomentum();
      out << particle.GetMomentum() / particle.GetMassNumber() << ' ';
    }
    if((sum.vect() - vec.vect()).mag() > 1e-5 || (sum - vec).m() > 1e-5) {
      std::cout << "cringe!\n";
    }
    out << '\n';
  }

  std::cout << dump_name << ": done\n";
}

int main() {
//  CalculateMomentum(12_m, 6_c, "../Data/stat.data", 12 * 10 * CLHEP::GeV, {0, 0, 0});
  CalculateMomentum(12_m, 6_c, "../Data/mov_x.data", 0, {12 * 10 * CLHEP::GeV, 0, 0});
  CalculateMomentum(12_m, 6_c, "../Data/mov_y.data", 0, {0, 12 * 10 * CLHEP::GeV, 0});
  CalculateMomentum(12_m, 6_c, "../Data/mov_z.data", 0, {0, 0, 12 * 10 * CLHEP::GeV});
//  Calculate(12_m, 6_c, "../C12.csv");
//
//  Calculate(13_m, 6_c, "../C13.csv");
//
//  Calculate(12_m, 7_c, "../N12.csv");
//
//  Calculate(13_m, 7_c, "../N13.csv");
}
