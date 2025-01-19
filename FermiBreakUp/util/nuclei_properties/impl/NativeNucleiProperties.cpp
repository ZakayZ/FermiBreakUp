//
// Created by Artem Novikov on 09.03.2023.
//

#include <CLHEP/Units/PhysicalConstants.h>

#include "util/Logger.h"
#include "table_values/NucleiPropertiesTable.h"
#include "table_values/NucleiPropertiesTableAME12.h"

#include "NativeNucleiProperties.h"

using namespace fermi;

constexpr FermiFloat ProtonMass = CLHEP::proton_mass_c2;
constexpr FermiFloat NeutronMass = CLHEP::neutron_mass_c2;
constexpr FermiFloat DeuteronMass = 1.875613 * CLHEP::GeV;
constexpr FermiFloat TritonMass = 2.808921 * CLHEP::GeV;
constexpr FermiFloat AlphaMass = 3.727379 * CLHEP::GeV;
constexpr FermiFloat He3Mass = 2.808391 * CLHEP::GeV;

constexpr FermiUInt HashNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber) {
  return static_cast<FermiUInt>(atomicMass) * 10'000 + static_cast<FermiUInt>(chargeNumber);
}

FermiFloat NativeNucleiProperties::GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (atomicMass < 1_m || chargeNumber < 0_c || FermiUInt(chargeNumber) > FermiUInt(atomicMass)) {
    LOG_DEBUG("Unsupported values for A = " << atomicMass << " and Z = " << chargeNumber);
    return 0;
  }

  switch (HashNuclei(atomicMass, chargeNumber)) {
    case HashNuclei(1_m, 1_c): return ProtonMass;
    case HashNuclei(1_m, 0_c): return NeutronMass;
    case HashNuclei(2_m, 1_c): return DeuteronMass;
    case HashNuclei(3_m, 1_c): return TritonMass;
    case HashNuclei(4_m, 2_c): return AlphaMass;
    case HashNuclei(3_m, 2_c): return He3Mass;
  }

  NucleiPropertiesTableAME12 tableAME12;
  if (tableAME12.ContainsParticle(atomicMass, chargeNumber)) {
    // AME 03 table
    return tableAME12.GetNuclearMass(atomicMass, chargeNumber);
  }

  NucleiPropertiesTable tableTheoretical;
  if (tableTheoretical.ContainsParticle(atomicMass, chargeNumber)) {
    // Theoretical table
    return tableTheoretical.GetNuclearMass(atomicMass, chargeNumber);
  }

  // Raw calculation
  return NuclearMass(atomicMass, chargeNumber);
}

bool NativeNucleiProperties::IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (atomicMass < 1_m || chargeNumber < 0_c || FermiUInt(chargeNumber) > FermiUInt(atomicMass)) {
    LOG_DEBUG("Unsupported values for A = " << atomicMass << " and Z = " << chargeNumber);
    return false;
  }

  return NucleiPropertiesTable().ContainsParticle(atomicMass, chargeNumber);
}

FermiFloat NativeNucleiProperties::AtomicWeight(AtomicMass atomicMass, ChargeNumber chargeNumber) {
  NucleiPropertiesTableAME12 tableAME12;
  FermiFloat hydrogenMassExcess = tableAME12.GetMassExcess(1_m, 1_c);
  FermiFloat NeutronMassExcess  = tableAME12.GetMassExcess(1_m, 0_c);

  FermiFloat mass = FermiFloat(FermiUInt(atomicMass) - FermiUInt(chargeNumber)) * NeutronMassExcess
      + FermiFloat(chargeNumber) * hydrogenMassExcess - WeitzsaeckerBindingEnergy(atomicMass, chargeNumber)
      + FermiFloat(atomicMass) * CLHEP::amu_c2;

  return mass;
}

FermiFloat NativeNucleiProperties::NuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) {
  if (atomicMass < 1_m || chargeNumber < 0_c || FermiUInt(chargeNumber) > FermiUInt(atomicMass)) {
    LOG_DEBUG("Unsupported values for A = " << atomicMass << " and Z = " << chargeNumber);
    return 0;
  }

  FermiFloat mass = AtomicWeight(atomicMass, chargeNumber);
  // atomic mass is converted to nuclear mass according formula in AME03
  mass -= FermiFloat(chargeNumber) * CLHEP::electron_mass_c2;
  mass += (14.4381 * std::pow(chargeNumber, 2.39) + 1.55468 * 1e-6 * std::pow(chargeNumber, 5.35)) * CLHEP::eV;

  return mass;
}
