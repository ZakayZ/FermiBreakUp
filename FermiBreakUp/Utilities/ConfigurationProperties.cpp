//
// Created by Artem Novikov on 19.02.2023.
//

#include "ConfigurationProperties.h"
#include "CLHEP/Units/PhysicalConstants.h"

using namespace fermi;

// KAPPA = V/V_0 it is used in calculation of Coulomb energy, KAPPA is dimensionless
const FermiFloat ConfigurationProperties::KAPPA = 1.0;

// R0 is the nuclear radius
const FermiFloat ConfigurationProperties::R0 = 1.3 * CLHEP::fermi;

FermiFloat ConfigurationProperties::DecayProbability(const FragmentVector& split,
                                                     uint32_t atomicWeight,
                                                     FermiFloat totalEnergy) {
  FermiFloat kineticEnergy = CalculateKineticEnergy(split, totalEnergy);  // in MeV
  // Check that there is enough energy to produce K fragments
  if (kineticEnergy <= 0) { return 0; }

  // Spin factor S_n
  FermiFloat s = CalculateSpinFactor(split);

  // Calculate MassFactor
  auto massFactor = CalculateMassFactor(split);

  // This is the constant (doesn't depend on nucleus) part
  auto scale = CalculateConstFactor(atomicWeight, split.size());

  // Calculation of 1/gamma(3(k-1)/2)
  auto gamma = CalculateGammaFactor(split.size());

  // Permutation Factor G_n
  auto g = CalculateConfigurationFactor(split);

  auto weight = scale * massFactor * (s / g) / gamma;
  weight *= std::pow(kineticEnergy, 3.0 * static_cast<FermiFloat>(split.size() - 1) / 2.0 - 1.);

  return weight;
}

FermiFloat ConfigurationProperties::CoulombBarrier(const FragmentVector& split) {
  //  Calculates Coulomb Barrier (MeV) for given channel with K fragments.
  static const FermiFloat coefficient = (3. / 5.) * (CLHEP::elm_coupling / R0) * std::pow(1. / (1. + KAPPA), 1. / 3.);

  FermiFloat massSum = 0;
  FermiFloat chargeSum = 0;
  FermiFloat CoulombEnergy = 0;
  for (auto& fragmentPtr : split) {
    auto mass = static_cast<FermiFloat>(fragmentPtr->GetAtomicMass());
    auto charge = static_cast<FermiFloat>(fragmentPtr->GetChargeNumber());
    CoulombEnergy += std::pow(charge, 2) / std::pow(mass, 1. / 3.);
    massSum += mass;
    chargeSum += charge;
  }
  CoulombEnergy -= std::pow(chargeSum, 2) / std::pow(massSum, 1. / 3.);
  return -coefficient * CoulombEnergy;
}

FermiFloat ConfigurationProperties::CalculateSpinFactor(const FragmentVector& split) {
  FermiFloat SN = 1;

  for (auto fragmentPtr : split) {
    auto& fragment = *fragmentPtr;
    SN *= fragment.GetPolarization();
  }
  return SN;
}

FermiFloat ConfigurationProperties::CalculateKineticEnergy(const FragmentVector& split, FermiFloat totalEnergy) {
  for (auto fragmentPtr : split) {
    auto& fragment = *fragmentPtr;
    totalEnergy -= fragment.GetFragmentMass() + fragment.GetExcitationEnergy();
  }
  if (totalEnergy > 0) {
    totalEnergy -= CoulombBarrier(split);
  }
  if (totalEnergy <= 0) {
    totalEnergy = 0;
  }
  return totalEnergy;
}

FermiFloat ConfigurationProperties::CalculateMassFactor(const FragmentVector& split) {
  FermiFloat massSum = 0;
  FermiFloat massProduct = 1;
  for (auto fragmentPtr : split) {
    auto& fragment = *fragmentPtr;
    auto fragmentMass = fragment.GetFragmentMass();
    massProduct *= fragmentMass;
    massSum += fragmentMass;
  }
  auto massFactor = massProduct / massSum;
  massFactor *= std::sqrt(massFactor);
  return massFactor;
}

FermiFloat ConfigurationProperties::CalculateConfigurationFactor(const FragmentVector& split) {
  // get all mass numbers and count repetitions
  std::vector<AtomicMass> masses;
  masses.reserve(split.size());
  for(auto fragmentPtr: split){
    masses.push_back(fragmentPtr->GetAtomicMass());
  }
  std::sort(masses.begin(), masses.end());

  std::vector<size_t> massRepeats;
  massRepeats.reserve(split.size());
  massRepeats.push_back(0);
  AtomicMass lastMass(masses[0]);
  for (auto fragmentMass : masses) {
    if (lastMass == fragmentMass) {
      ++massRepeats.back();
    } else {
      lastMass = fragmentMass;
      massRepeats.push_back(1);
    }
  }

  FermiFloat GN = 1;
  for (auto count : massRepeats) {
    auto factorial = [](size_t n) -> size_t {
      size_t factorial = 1;
      for (size_t i = 2; i < n; ++i) { factorial *= i; }
      return factorial;
    };
    GN *= static_cast<FermiFloat>(factorial(count));
  }

  return GN;
}

FermiFloat ConfigurationProperties::CalculateConstFactor(uint32_t atomicWeight, size_t fragmentsCount) {
  static const FermiFloat constantPart = std::pow(R0 / CLHEP::hbarc, 3.0) * KAPPA * std::sqrt(2.0 / CLHEP::pi) / 3.0;
  FermiFloat coefficient = std::pow(constantPart * atomicWeight, fragmentsCount - 1);
  return coefficient;
}

FermiFloat ConfigurationProperties::CalculateGammaFactor(size_t fragmentsCount) {
  FermiFloat gamma = 1.0;
  FermiFloat arg = 3.0 * static_cast<FermiFloat>(fragmentsCount - 1) / 2.0 - 1.0;
  while (arg > 1.1) {
    gamma *= arg;
    arg--;
  }

  if (fragmentsCount % 2 == 0) { gamma *= std::sqrt(CLHEP::pi); }

  return gamma;
}
