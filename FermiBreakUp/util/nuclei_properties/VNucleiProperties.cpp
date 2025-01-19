//
// Created by Artem Novikov on 09.03.2023.
//

#include <CLHEP/Units/PhysicalConstants.h>

#include "VNucleiProperties.h"

using namespace fermi;

FermiFloat VNucleiProperties::WeitzsaeckerBindingEnergy(AtomicMass atomicMass, ChargeNumber chargeNumber) {
  // Weitzsaecker's Mass formula
  const auto nucleiParity = (FermiInt(atomicMass) - FermiInt(chargeNumber)) % 2;                   // pairing
  const auto chargeParity = FermiInt(chargeNumber) % 2;

  FermiFloat binding =
          -15.67 * FermiFloat(atomicMass)                                                          // nuclear volume
          + 17.23 * std::pow(atomicMass, 2. / 3.)                                                  // surface energy
          + 93.15 * std::pow(FermiFloat(atomicMass) / 2. - FermiFloat(chargeNumber), 2)
              / FermiFloat(atomicMass)                                                             // asymmetry
          + 0.6984523 * std::pow(FermiFloat(chargeNumber), 2) / std::cbrt(FermiFloat(atomicMass)); // coulomb

  if (nucleiParity == chargeParity) {
    binding += 12.0 * (nucleiParity + chargeParity - 1) / std::sqrt(FermiFloat(atomicMass));      // pairing
  }

  return -binding * CLHEP::MeV;
}

FermiFloat VNucleiProperties::EstimateAtomicWeight(AtomicMass atomicMass, ChargeNumber chargeNumber) {
  constexpr FermiFloat hydrogenMassExcess = 7.28897;
  constexpr FermiFloat neutronMassExcess = 8.07132;

  return FermiFloat(FermiInt(atomicMass) - FermiInt(chargeNumber)) * neutronMassExcess
      + FermiFloat(chargeNumber) * hydrogenMassExcess - WeitzsaeckerBindingEnergy(atomicMass, chargeNumber)
      + FermiFloat(atomicMass) * CLHEP::amu_c2;
}

FermiFloat VNucleiProperties::EstimateNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) {
  auto mass = EstimateAtomicWeight(atomicMass, chargeNumber);

  // atomic mass is converted to nuclear mass according formula in AME03
  mass -= FermiFloat(chargeNumber) * CLHEP::electron_mass_c2;
  mass += (
    14.4381 * std::pow(FermiFloat(chargeNumber), 2.39) 
    + 1.55468e-6 * std::pow(FermiFloat(chargeNumber), 5.35)
  ) * CLHEP::eV;

  return mass;
}
