//
// Created by Artem Novikov on 18.02.2023.
//

#include "NucleiProperties.h"
#include "TableValues/NucleiPropertiesTable.h"
#include "TableValues/NucleiPropertiesTheoreticalTable.h"
#include "TableValues/ParticleTable.h"
#include "TableValues/NucleiPropertiesCompile.h"
#include <CLHEP/Units/PhysicalConstants.h>

FermiFloat NucleiProperties::GetNuclearMass(uint32_t mass_number, uint32_t charge_number) {
//  if (mass_proton <= 0.0) {
//    const G4ParticleDefinition* nucleus = 0;
//    nucleus = G4ParticleTable::GetParticleTable()->FindParticle("proton"); /// proton
//    if (nucleus != 0) mass_proton = nucleus->GetPDGMass();
//    nucleus = G4ParticleTable::GetParticleTable()->FindParticle("neutron"); /// neutron
//    if (nucleus != 0) mass_neutron = nucleus->GetPDGMass();
//    nucleus = G4ParticleTable::GetParticleTable()->FindParticle("deuteron"); /// deuteron
//    if (nucleus != 0) mass_deuteron = nucleus->GetPDGMass();
//    nucleus = G4ParticleTable::GetParticleTable()->FindParticle("triton"); /// triton
//    if (nucleus != 0) mass_triton = nucleus->GetPDGMass();
//    nucleus = G4ParticleTable::GetParticleTable()->FindParticle("alpha"); /// alpha
//    if (nucleus != 0) mass_alpha = nucleus->GetPDGMass();
//    nucleus = G4ParticleTable::GetParticleTable()->FindParticle("He3"); /// He3
//    if (nucleus != 0) mass_He3 = nucleus->GetPDGMass();
//
//  }

  if (IsInvalidNuclei(mass_number, charge_number)) { /// TODO Charge might be negative???
    std::cerr << "G4NucleiProperties::GetNuclearMass: Wrong values for A = " << mass_number
              << " and Z = " << charge_number << std::endl;
    return 0.0;
  }

  if (charge_number <= 2) {  ///
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

  if (NucleiPropertiesTable::IsInTable(mass_number, charge_number)) {
    /// AME 03 table
    return NucleiPropertiesTable::GetNuclearMass(mass_number, charge_number);
  }

  if (NucleiPropertiesTheoreticalTable::IsInTable(mass_number, charge_number)) {
    /// Theoretical table
    return NucleiPropertiesTheoreticalTable::GetNuclearMass(mass_number, charge_number);
  }

  /// Raw calculation
  return NuclearMass(FermiFloat(mass_number), FermiFloat(charge_number));

  return 0;
}

bool NucleiProperties::IsStable(uint32_t mass_number, uint32_t charge_number) {
  if (IsInvalidNuclei(mass_number, charge_number)) {
    if (ParticleTable::GetParticleTable()->GetVerboseLevel() > 0) {
      std::cerr << "G4NucleiProperties::IsInStableTable: Wrong values for A = "
                << mass_number << " and Z = " << charge_number << std::endl;
    }
    return false;
  }

  return NucleiPropertiesTable::IsInTable(mass_number, charge_number);
}

FermiFloat NucleiProperties::AtomicMass(FermiFloat mass_number, FermiFloat charge_number) {
  return 0;
}

FermiFloat NucleiProperties::NuclearMass(FermiFloat mass_number, FermiFloat charge_number) {
  if (IsInvalidNuclei(mass_number, charge_number)) {
    if (ParticleTable::GetParticleTable()->GetVerboseLevel() > 0) {
      std::cerr << "G4NucleiProperties::NuclearMass: Wrong values for A = "
                << mass_number << " and Z = " << charge_number << std::endl;
    }
    return 0.0;
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
      -15.67 * mass_number                                                                                  /// nuclear volume
          + 17.23 * std::pow(mass_number, 2. / 3.)                                                          /// surface energy
          + 93.15 * ((mass_number / 2. - charge_number) * (mass_number / 2. - charge_number)) / mass_number /// asymmetry
          + 0.6984523 * std::pow(charge_number, 2) * std::pow(mass_number, -1. / 3.);                       /// coulomb
  if (N_pairing == Z_pairing) { binding += (N_pairing + Z_pairing - 1) * 12.0 / std::sqrt(mass_number); }   /// pairing

  return -binding * CLHEP::MeV;
}

bool NucleiProperties::IsInvalidNuclei(FermiFloat mass_number, FermiFloat charge_number) {
  return mass_number < 1 || charge_number < 0 || charge_number > mass_number;
}

