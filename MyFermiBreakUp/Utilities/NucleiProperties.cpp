//
// Created by Artem Novikov on 18.02.2023.
//

#include <CLHEP/Units/PhysicalConstants.h>

#include "NucleiProperties.h"
#include "TableValues/NucleiPropertiesTable.h"
#include "TableValues/NucleiPropertiesTableAME12.h"

const FermiFloat NucleiProperties::proton_mass = CLHEP::proton_mass_c2;

const FermiFloat NucleiProperties::neutron_mass = CLHEP::neutron_mass_c2;

const FermiFloat NucleiProperties::deuteron_mass = 1.875613 * CLHEP::GeV;

const FermiFloat NucleiProperties::triton_mass = 2.808921 * CLHEP::GeV;

const FermiFloat NucleiProperties::alpha_mass = 3.727379 * CLHEP::GeV;

const FermiFloat NucleiProperties::He3_mass = 2.808391 * CLHEP::GeV;

FermiFloat NucleiProperties::GetNuclearMass(uint32_t mass_number, uint32_t charge_number) {
  if (IsInvalidNuclei(mass_number, charge_number)) { /// TODO Charge might be negative???
    std::cerr << "G4NucleiProperties::GetNuclearMass: Wrong values for A = " << mass_number
              << " and Z = " << charge_number << std::endl;
    return 0;
  }

  if (charge_number <= 2) {
    if (charge_number == 1 && mass_number == 1) {
      return proton_mass;
    }
    if (charge_number == 0 && mass_number == 1) {
      return neutron_mass;
    }
    if (charge_number == 1 && mass_number == 2) {
      return deuteron_mass;
    }
    if (charge_number == 1 && mass_number == 3) {
      return triton_mass;
    }
    if (charge_number == 2 && mass_number == 4) {
      return alpha_mass;
    }
    if (charge_number == 2 && mass_number == 3) {
      return He3_mass;
    }
  }

  NucleiPropertiesTableAME12 table_AME12;
  if (table_AME12.ContainsParticle(mass_number, charge_number)) {
    /// AME 03 table
    return table_AME12.GetNuclearMass(mass_number, charge_number);
  }

  NucleiPropertiesTable table_theoretical;
  if (table_theoretical.ContainsParticle(mass_number, charge_number)) {
    /// Theoretical table
    return table_theoretical.GetNuclearMass(mass_number, charge_number);
  }

  /// Raw calculation
  return NuclearMass(FermiFloat(mass_number), FermiFloat(charge_number));

  return 0;
}

bool NucleiProperties::IsStable(uint32_t mass_number, uint32_t charge_number) {
  if (IsInvalidNuclei(mass_number, charge_number)) {
    std::cerr << "G4NucleiProperties::IsInStableTable: Wrong values for A = "
              << mass_number << " and Z = " << charge_number << std::endl;
    return false;
  }

  return NucleiPropertiesTable().ContainsParticle(mass_number, charge_number);
}

FermiFloat NucleiProperties::AtomicMass(FermiFloat mass_number, FermiFloat charge_number) {
  NucleiPropertiesTableAME12 table_AME12;
  const FermiFloat hydrogen_mass_excess = table_AME12.GetMassExcess(1, 1);
  const FermiFloat neutron_mass_excess = table_AME12.GetMassExcess(1, 0);

  FermiFloat mass = static_cast<FermiFloat>(mass_number - charge_number) * neutron_mass_excess
      + static_cast<FermiFloat>(charge_number) * hydrogen_mass_excess - BindingEnergy(mass_number, charge_number)
      + static_cast<FermiFloat>(mass_number) * CLHEP::amu_c2;

  return mass;
}

FermiFloat NucleiProperties::NuclearMass(FermiFloat mass_number, FermiFloat charge_number) {
  if (IsInvalidNuclei(mass_number, charge_number)) {
    std::cerr << "NucleiProperties::NuclearMass: Wrong values for A = "
              << mass_number << " and Z = " << charge_number << std::endl;
    return 0;
  }

  FermiFloat mass = AtomicMass(mass_number, charge_number);
  /// atomic mass is converted to nuclear mass according formula in AME03
  mass -= charge_number * CLHEP::electron_mass_c2;
  mass += (14.4381 * std::pow(charge_number, 2.39) + 1.55468 * 1e-6 * std::pow(charge_number, 5.35)) * CLHEP::eV;

  return mass;
}

FermiFloat NucleiProperties::BindingEnergy(FermiFloat mass_number, FermiFloat charge_number) {
  /// Weitzsaecker's Mass formula
  int N_pairing = int(mass_number - charge_number) % 2;                                                     /// pairing
  int Z_pairing = int(charge_number) % 2;

  FermiFloat binding =
      -15.67
          * mass_number                                                                                  /// nuclear volume
          + 17.23 * std::pow(mass_number,
                             2. / 3.)                                                          /// surface energy
          + 93.15 * ((mass_number / 2. - charge_number) * (mass_number / 2. - charge_number))
              / mass_number /// asymmetry
          + 0.6984523 * std::pow(charge_number, 2) * std::pow(mass_number, -1. / 3.);                       /// coulomb

  if (N_pairing == Z_pairing) {
    binding += (N_pairing + Z_pairing - 1) * 12.0 / std::sqrt(mass_number);                                 /// pairing
  }

  return -binding * CLHEP::MeV;
}

bool NucleiProperties::IsInvalidNuclei(FermiFloat mass_number, FermiFloat charge_number) {
  return mass_number < 1 || charge_number < 0 || charge_number > mass_number;
}

