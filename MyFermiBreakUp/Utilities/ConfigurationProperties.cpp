//
// Created by Artem Novikov on 19.02.2023.
//
#include <numbers>

#include "ConfigurationProperties.h"
#include "CLHEP/Units/PhysicalConstants.h"
#include "FermiFragmentPool.h"

/// Kappa = V/V_0 it is used in calculation of Coulomb energy, Kappa is dimensionless
const FermiFloat ConfigurationProperties::Kappa = 1.0;

/// r0 is the nuclear radius
const FermiFloat ConfigurationProperties::r0 = 1.3 * CLHEP::fermi;

FermiFloat ConfigurationProperties::DecayProbability(
    const FragmentSplit& split, uint32_t atomic_weight, FermiFloat total_energy) {
///// TODO optimization like original maybe

  FermiFloat kinetic_energy = CalculateKineticEnergy(split, total_energy);  /// in MeV
  /// Check that there is enough energy to produce K fragments
  if (kinetic_energy <= 0) { return 0; }

  /// Spin factor
  FermiFloat S_n = CalculateSpinFactor(split);

  /// Calculate MassFactor
  auto mass_factor = CalculateMassFactor(split);

  /// This is the constant (doesn't depend on nucleus) part
  auto coefficient = CalculateConstFactor(atomic_weight, split.size());

  /// Calculation of 1/gamma(3(k-1)/2)
  auto gamma = CalculateGammaFactor(split.size());

  /// Permutation Factor G_n
  auto G_n = CalculateConfigurationFactor(split);

  auto Weight = coefficient * mass_factor * (S_n / G_n) / gamma;
  Weight *= std::pow(kinetic_energy, 3.0 * static_cast<FermiFloat>(split.size() - 1) / 2.0) / kinetic_energy;

  return Weight;
}

FermiFloat ConfigurationProperties::CoulombBarrier(const FragmentSplit& split) {
  ///  Calculates Coulomb Barrier (MeV) for given channel with K fragments.
  static const FermiFloat coefficient = (3. / 5.) * (CLHEP::elm_coupling / r0) * std::pow(1. / (1. + Kappa), 1. / 3.);

  FermiFloat mass_sum = 0;
  FermiFloat charge_sum = 0;
  FermiFloat CoulombEnergy = 0;
  for (auto& fragment_ptr : split) {
    auto mass = static_cast<FermiFloat>(fragment_ptr->GetChargeNumber());
    auto charge = static_cast<FermiFloat>(fragment_ptr->GetMassNumber());
    CoulombEnergy += std::pow(charge, 2) / std::pow(mass, 1. / 3.);
    mass_sum += mass;
    charge_sum += charge;
  }
  CoulombEnergy -= std::pow(charge_sum, 2) / std::pow(mass_sum, 1. / 3.);
  return -coefficient * CoulombEnergy;
}

FermiFloat ConfigurationProperties::CalculateSpinFactor(const FragmentSplit& split) {
  FermiFloat S_n = 1;

  for (auto fragment_ptr : split) {
    auto& fragment = *fragment_ptr;
    S_n *= fragment.GetPolarization();
  }
  return S_n;
}

FermiFloat ConfigurationProperties::CalculateKineticEnergy(const FragmentSplit& split, FermiFloat total_energy) {
  for (auto fragment_ptr : split) {
    auto& fragment = *fragment_ptr;
    total_energy -= fragment.GetMassNumber() + fragment.GetExcitationEnergy();
  }
  if (total_energy > 0) {
    total_energy -= CoulombBarrier(split);
  }
  if (total_energy <= 0) {
    total_energy = 0;
  }
  return total_energy;
}

FermiFloat ConfigurationProperties::CalculateMassFactor(const FragmentSplit& split) {
  FermiFloat mass_sum = 0;
  FermiFloat mass_product = 1;
  for (auto fragment_ptr : split) {
    auto& fragment = *fragment_ptr;
    auto fragment_mass = fragment.GetFragmentMass();
    mass_product *= fragment_mass;
    mass_sum += fragment_mass;
  }
  auto mass_factor = mass_product / mass_sum;
  mass_factor *= std::sqrt(mass_factor);
  return mass_factor;
}

FermiFloat ConfigurationProperties::CalculateConfigurationFactor(const FragmentSplit& split) { /// TODO
  std::vector<size_t> nuclei_count;
  nuclei_count.reserve(split.size());

  /// sort split by a,z pair
  auto sorted_split = split;
  auto cmp = [](const FermiFragment* a, const FermiFragment* b) {
    return a->GetMassNumber() < b->GetMassNumber()
        || a->GetMassNumber() == b->GetMassNumber() && a->GetChargeNumber() < b->GetChargeNumber();
  };
  std::sort(sorted_split.begin(), sorted_split.end(), cmp);

  NucleiData last_nuclei{sorted_split[0]->GetMassNumber(), sorted_split[0]->GetChargeNumber()};
  nuclei_count.push_back(0);
  for (auto fragment : sorted_split) {
    if (last_nuclei.mass_number == fragment->GetMassNumber()
        && last_nuclei.charge_number == fragment->GetChargeNumber()) {
      ++nuclei_count.back();
    } else {
      last_nuclei = {fragment->GetMassNumber(), fragment->GetChargeNumber()};
      nuclei_count.push_back(1);
    }
  }

  FermiFloat G_n = 1;
  for (auto count : nuclei_count) {
    auto factorial = [](size_t n) -> size_t {
      size_t factorial = 1;
      for (size_t i = 2; i < n; ++i) { factorial *= i; }
      return factorial;
    };
    G_n *= static_cast<FermiFloat>(factorial(count));
  }

  return G_n;
}

FermiFloat ConfigurationProperties::CalculateConstFactor(uint32_t atomic_weight, uint32_t fragments_count) {
  static const FermiFloat constant_part = std::pow(r0 / CLHEP::hbarc, 3.0) * Kappa * std::sqrt(2.0 / CLHEP::pi) / 3.0;
  FermiFloat coefficient = std::pow(constant_part * atomic_weight, fragments_count - 1);
  return coefficient;
}

FermiFloat ConfigurationProperties::CalculateGammaFactor(uint32_t fragments_count) {
  FermiFloat gamma = 1.0;
  FermiFloat arg = 3.0 * static_cast<FermiFloat>(fragments_count - 1) / 2.0 - 1.0;
  while (arg > 1.1) {
    gamma *= arg;
    arg--;
  }

  if (fragments_count % 2 == 0) { gamma *= std::sqrt(CLHEP::pi); }

  return gamma;
}
