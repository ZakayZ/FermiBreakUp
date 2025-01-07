//
// Created by Artem Novikov on 09.03.2023.
//

#include <CLHEP/Units/PhysicalConstants.h>

#include "NativeNucleiProperties.h"
#include "TableValues/NucleiPropertiesTable.h"
#include "TableValues/NucleiPropertiesTableAME12.h"

namespace properties {

const FermiFloat NativeNucleiProperties::protonMass = CLHEP::proton_mass_c2;

const FermiFloat NativeNucleiProperties::neutronMass = CLHEP::neutron_mass_c2;

const FermiFloat NativeNucleiProperties::deuteronMass = 1.875613 * CLHEP::GeV;

const FermiFloat NativeNucleiProperties::tritonMass = 2.808921 * CLHEP::GeV;

const FermiFloat NativeNucleiProperties::alphaMass = 3.727379 * CLHEP::GeV;

const FermiFloat NativeNucleiProperties::He3Mass = 2.808391 * CLHEP::GeV;

FermiFloat NativeNucleiProperties::GetNuclearMass(MassNumber massNumber, ChargeNumber chargeNumber) const {
  if (IsInvalidNuclei(massNumber, chargeNumber)) {
    std::cerr << "NucleiProperties::GetNuclearMass: Wrong values for A = " << massNumber
              << " and Z = " << chargeNumber << std::endl;
    return 0;
  }

  if (chargeNumber <= 2_c) {
    if (chargeNumber == 1_c && massNumber == 1_m) {
      return protonMass;
    }
    if (chargeNumber == 0_c && massNumber == 1_m) {
      return neutronMass;
    }
    if (chargeNumber == 1_c && massNumber == 2_m) {
      return deuteronMass;
    }
    if (chargeNumber == 1_c && massNumber == 3_m) {
      return tritonMass;
    }
    if (chargeNumber == 2_c && massNumber == 4_m) {
      return alphaMass;
    }
    if (chargeNumber == 2_c && massNumber == 3_m) {
      return He3Mass;
    }
  }

  NucleiPropertiesTableAME12 tableAME12;
  if (tableAME12.ContainsParticle(massNumber, chargeNumber)) {
    // AME 03 table
    return tableAME12.GetNuclearMass(massNumber, chargeNumber);
  }

  NucleiPropertiesTable tableTheoretical;
  if (tableTheoretical.ContainsParticle(massNumber, chargeNumber)) {
    // Theoretical table
    return tableTheoretical.GetNuclearMass(massNumber, chargeNumber);
  }

  // Raw calculation
  return NuclearMass(massNumber, chargeNumber);
}

bool NativeNucleiProperties::IsStable(MassNumber massNumber, ChargeNumber chargeNumber) const {
  if (IsInvalidNuclei(massNumber, chargeNumber)) {
    std::cerr << "NucleiProperties::IsInStableTable: Wrong values for A = "
              << massNumber << " and Z = " << chargeNumber << std::endl;
    return false;
  }

  return NucleiPropertiesTable().ContainsParticle(massNumber, chargeNumber);
}

FermiFloat NativeNucleiProperties::AtomicMass(MassNumber massNumber, ChargeNumber chargeNumber) {
  NucleiPropertiesTableAME12 tableAME12;
  const FermiFloat hydrogenMassExcess = tableAME12.GetMassExcess(1_m, 1_c);
  const FermiFloat neutronMassExcess  = tableAME12.GetMassExcess(1_m, 0_c);

  FermiFloat mass = FermiFloat(FermiUInt(massNumber) - FermiUInt(chargeNumber)) * neutronMassExcess
      + FermiFloat(chargeNumber) * hydrogenMassExcess - BindingEnergy(massNumber, chargeNumber)
      + FermiFloat(massNumber) * CLHEP::amu_c2;

  return mass;
}

FermiFloat NativeNucleiProperties::NuclearMass(MassNumber massNumber, ChargeNumber chargeNumber) {
  if (IsInvalidNuclei(massNumber, chargeNumber)) {
    std::cerr << "NativeNucleiProperties::NuclearMass: Wrong values for A = "
              << massNumber << " and Z = " << chargeNumber << std::endl;
    return 0;
  }

  FermiFloat mass = AtomicMass(massNumber, chargeNumber);
  // atomic mass is converted to nuclear mass according formula in AME03
  mass -= FermiFloat(chargeNumber) * CLHEP::electron_mass_c2;
  mass += (14.4381 * std::pow(chargeNumber, 2.39) + 1.55468 * 1e-6 * std::pow(chargeNumber, 5.35)) * CLHEP::eV;

  return mass;
}

FermiFloat NativeNucleiProperties::BindingEnergy(MassNumber massNumber, ChargeNumber chargeNumber) {
  // Weitzsaecker's Mass formula
  FermiUInt NPairing = (FermiUInt(massNumber) - FermiUInt(chargeNumber)) % 2;                      // pairing
  FermiUInt ZPairing = FermiUInt(chargeNumber) % 2;

  FermiFloat binding =
          - 15.67 * FermiFloat(massNumber)                                                           // nuclear volume
          + 17.23 * std::pow(massNumber, 2. / 3.)                                                    // surface energy
          + 93.15 * ((FermiFloat(massNumber) / 2. - FermiFloat(chargeNumber))
          * (FermiFloat(massNumber) / 2. - FermiFloat(chargeNumber))) / FermiFloat(massNumber)     // asymmetry
          + 0.6984523 * std::pow(FermiUInt(chargeNumber), 2) * std::pow(massNumber, -1. / 3.);      // coulomb

  if (NPairing == ZPairing) {
    binding += (NPairing + ZPairing - 1) * 12.0 / std::sqrt(FermiFloat(massNumber));               // pairing
  }

  return -binding * CLHEP::MeV;
}

bool NativeNucleiProperties::IsInvalidNuclei(MassNumber massNumber, ChargeNumber chargeNumber) {
  return massNumber < 1_m || chargeNumber < 0_c || FermiUInt(chargeNumber) > FermiUInt(massNumber);
}

} // namespace properties
