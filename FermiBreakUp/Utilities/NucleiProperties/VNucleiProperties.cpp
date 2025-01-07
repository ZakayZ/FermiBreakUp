//
// Created by Artem Novikov on 09.03.2023.
//

#include <CLHEP/Units/PhysicalConstants.h>

#include "VNucleiProperties.h"

namespace properties {

VNucleiProperties::~VNucleiProperties() = default;

FermiFloat VNucleiProperties::AtomicMass(MassNumber massNumber, ChargeNumber chargeNumber) {
  static const FermiFloat hydrogenMassExcess = 7.28897;
  static const FermiFloat neutronMassExcess = 8.07132;

  FermiFloat mass = FermiFloat(FermiUInt(massNumber) - FermiUInt(chargeNumber)) * neutronMassExcess
      + FermiFloat(chargeNumber) * hydrogenMassExcess - BindingEnergy(massNumber, chargeNumber)
      + FermiFloat(massNumber) * CLHEP::amu_c2;

  return mass;
}

FermiFloat VNucleiProperties::NuclearMass(MassNumber massNumber, ChargeNumber chargeNumber) {
  FermiFloat mass = AtomicMass(massNumber, chargeNumber);
  // atomic mass is converted to nuclear mass according formula in AME03
  mass -= FermiFloat(chargeNumber) * CLHEP::electron_mass_c2;
  mass += (14.4381 * std::pow(chargeNumber, 2.39) + 1.55468 * 1e-6 * std::pow(chargeNumber, 5.35)) * CLHEP::eV;

  return mass;
}

FermiFloat VNucleiProperties::BindingEnergy(MassNumber massNumber, ChargeNumber chargeNumber) {
  // Weitzsaecker's Mass formula
  FermiInt NPairing = (FermiInt(massNumber) - FermiInt(chargeNumber)) % 2;                      // pairing
  FermiInt ZPairing = FermiInt(chargeNumber) % 2;

  FermiFloat binding =
      -15.67 * FermiFloat(massNumber)                                                           // nuclear volume
          + 17.23 * std::pow(massNumber, 2. / 3.)                                                    // surface energy
          + 93.15 * std::pow(FermiFloat(massNumber) / 2. - FermiFloat(chargeNumber), 2)
              / FermiFloat(massNumber)                                                                   // asymmetry
          + 0.6984523 * std::pow(FermiUInt(chargeNumber), 2) * std::pow(massNumber, -1. / 3.);      // coulomb

  if (NPairing == ZPairing) {
    binding += (NPairing + ZPairing - 1) * 12.0 / std::sqrt(FermiFloat(massNumber));               // pairing
  }

  return -binding * CLHEP::MeV;
}

bool VNucleiProperties::IsInvalidNuclei(MassNumber massNumber, ChargeNumber chargeNumber) {
  return massNumber < 1_m || chargeNumber < 0_c || FermiUInt(chargeNumber) > FermiUInt(massNumber);
}

void VNucleiProperties::PrintInvalidNuclei(MassNumber massNumber, ChargeNumber chargeNumber) {
  std::cerr << "Unsupported values for A = " << massNumber << " and Z = " << chargeNumber << std::endl;
}

} // namespace properties
