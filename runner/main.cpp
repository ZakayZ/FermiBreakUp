#include "G4FermiBreakUp.hh"

#include "G4FermiCache.hh"
#include "G4FermiNucleiProperties.hh"
#include <CLHEP/Units/PhysicalConstants.h>

#include <fstream>
#include <iostream>

using namespace fbu;

void CalculateFragments(G4FermiAtomicMass mass, G4FermiChargeNumber charge,
                        const std::string& dumpName, G4FermiFloat step = 0.2, size_t tests = 1e4)
{
  auto model = G4FermiBreakUp(
    std::make_unique<G4FermiSimpleCache<G4FermiNucleiData, G4FermiPossibleFragmentSplits>>());
  std::vector<G4FermiFloat> energyNucleonValues;
  std::vector<float> avgParts;
  for (G4FermiFloat energyNucleon = 0.; energyNucleon <= 10.; energyNucleon += step) {
    size_t partsCounter = 0;
    auto additionalEnergy = energyNucleon * G4FermiFloat(mass);
    for (size_t i = 0; i < tests; ++i) {
      auto vec = G4FermiLorentzVector(
        0, 0, 0, G4FermiNucleiProperties()->GetNuclearMass(mass, charge) + additionalEnergy);
      auto particles = model.BreakItUp(G4FermiParticle(mass, charge, vec));
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

void CalculateMomentum(G4FermiAtomicMass mass, G4FermiChargeNumber charge,
                       const std::string& dumpName, G4FermiFloat energy,
                       const G4FermiVector3& momentum, size_t tests = 1e4)
{
  auto model = G4FermiBreakUp(
    std::make_unique<G4FermiSimpleCache<G4FermiNucleiData, G4FermiPossibleFragmentSplits>>());
  std::ofstream out(dumpName);
  auto vec = G4FermiLorentzVector(
    momentum.x(), momentum.y(), momentum.z(),
    std::sqrt(std::pow(G4FermiNucleiProperties()->GetNuclearMass(mass, charge) + energy, 2)
              + momentum.mag2()));
  out << vec / mass << '\n';
  std::vector<G4FermiFloat> xComponent, yComponent, zComponent, magnitude;
  for (size_t i = 0; i < tests; ++i) {
    auto particles = model.BreakItUp(G4FermiParticle(mass, charge, vec));
    auto sum = G4FermiLorentzVector();
    for (const auto& particle : particles) {
      sum += particle.GetMomentum();
      out << particle.GetMomentum() / particle.GetAtomicMass() << ' ';
    }
    out << '\n';
  }

  std::cout << dumpName << ": done\n";
}

int main()
{
  CalculateMomentum(12_m, 6_c, "../Results/stat.data", 12 * 10 * CLHEP::GeV, {0, 0, 0});
  CalculateMomentum(12_m, 6_c, "../Results/mov_x.data", 12 * 5 * CLHEP::MeV,
                    {12 * 10 * CLHEP::GeV, 0, 0});
  CalculateMomentum(12_m, 6_c, "../Results/mov_y.data", 12 * 5 * CLHEP::MeV,
                    {0, 12 * 10 * CLHEP::GeV, 0});
  CalculateMomentum(12_m, 6_c, "../Results/mov_z.data", 12 * 5 * CLHEP::MeV,
                    {0, 0, 12 * 10 * CLHEP::GeV});

  CalculateFragments(12_m, 6_c, "../Results/C12.csv");

  CalculateFragments(13_m, 6_c, "../Results/C13.csv");

  CalculateFragments(12_m, 7_c, "../Results/N12.csv");

  CalculateFragments(13_m, 7_c, "../Results/N13.csv");
}
