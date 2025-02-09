#include <iostream>
#include <fstream>
#include <filesystem>

#include <CLHEP/Units/PhysicalConstants.h>

#include <FermiBreakUp/FermiBreakUp.h>
#include <FermiBreakUp/nuclei_properties/NucleiProperties.h>
#include <FermiBreakUp/util/Cache.h>

using namespace fbu;

namespace fs = std::filesystem;

void CalculateFragments(
  AtomicMass mass,
  ChargeNumber charge,
  const std::string& dumpName,
  FermiFloat step = 0.2,
  size_t tests = 1e4)
{
  auto model = FermiBreakUp(std::make_unique<SimpleCache<NucleiData, FragmentSplits>>());
  std::vector<FermiFloat> energyNucleonValues;
  std::vector<float> avgParts;
  for (FermiFloat energyNucleon = 0.; energyNucleon <= 10.; energyNucleon += step) {
    size_t partsCounter = 0;
    auto additionalEnergy = energyNucleon * FermiFloat(mass);
    for (size_t i = 0; i < tests; ++i) {
      auto vec = LorentzVector(0, 0, 0, NucleiProperties()->GetNuclearMass(mass, charge) + additionalEnergy);
      auto particles = model.BreakItUp(Particle(mass, charge, vec));
      partsCounter += particles.size();
    }
    avgParts.push_back(float(partsCounter) / float(tests));
    energyNucleonValues.push_back(energyNucleon);
  }

  std::ofstream out(dumpName);

  out << "energy,avg_count\n";
  for (size_t i = 0; i < avgParts.size(); ++i) {
    out << energyNucleonValues[i] << ',' << avgParts[i] << '\n';
  }

  std::cout << dumpName << ": done\n";
}

void CalculateMomentum(
  AtomicMass mass,
  ChargeNumber charge,
  const std::string& dumpName,
  FermiFloat energy,
  const Vector3& momentum,
  size_t tests = 1e4)
{
  auto model = FermiBreakUp(std::make_unique<SimpleCache<NucleiData, FragmentSplits>>());
  std::ofstream out(dumpName);
  auto vec = LorentzVector(momentum.x(), momentum.y(), momentum.z(),
                           std::sqrt(std::pow(NucleiProperties()->GetNuclearMass(mass, charge) + energy, 2)
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

int main() {
  const auto resultsPath = fs::path("../Results");
  fs::create_directory(resultsPath);

  CalculateMomentum(12_m, 6_c, resultsPath / "stat.data", 12 * 10 * CLHEP::GeV, {0, 0, 0});
  CalculateMomentum(12_m, 6_c, resultsPath / "mov_x.data", 12 * 5 * CLHEP::MeV, {12 * 10 * CLHEP::GeV, 0, 0});
  CalculateMomentum(12_m, 6_c, resultsPath / "mov_y.data", 12 * 5 * CLHEP::MeV, {0, 12 * 10 * CLHEP::GeV, 0});
  CalculateMomentum(12_m, 6_c, resultsPath / "mov_z.data", 12 * 5 * CLHEP::MeV, {0, 0, 12 * 10 * CLHEP::GeV});

  CalculateFragments(12_m, 6_c, resultsPath / "C12.csv");
  CalculateFragments(13_m, 6_c, resultsPath / "C13.csv");
  CalculateFragments(12_m, 7_c, resultsPath / "N12.csv");
  CalculateFragments(13_m, 7_c, resultsPath / "N13.csv");
}
