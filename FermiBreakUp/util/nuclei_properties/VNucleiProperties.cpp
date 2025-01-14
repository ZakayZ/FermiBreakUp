//
// Created by Artem Novikov on 09.03.2023.
//

#include <CLHEP/Units/PhysicalConstants.h>

#include "VNucleiProperties.h"

namespace properties {
  FermiFloat VNucleiProperties::AtomicWeight(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    constexpr FermiFloat hydrogenMassExcess = 7.28897;
    constexpr FermiFloat neutronMassExcess = 8.07132;

    FermiFloat mass = FermiFloat(FermiUInt(atomicMass) - FermiUInt(chargeNumber)) * neutronMassExcess
        + FermiFloat(chargeNumber) * hydrogenMassExcess - BindingEnergy(atomicMass, chargeNumber)
        + FermiFloat(atomicMass) * CLHEP::amu_c2;

    return mass;
  }

  FermiFloat VNucleiProperties::NuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    auto mass = AtomicWeight(atomicMass, chargeNumber);
    // atomic mass is converted to nuclear mass according formula in AME03
    mass -= FermiFloat(chargeNumber) * CLHEP::electron_mass_c2;
    mass += (14.4381 * std::pow(chargeNumber, 2.39) + 1.55468 * 1e-6 * std::pow(chargeNumber, 5.35)) * CLHEP::eV;

    return mass;
  }

  FermiFloat VNucleiProperties::BindingEnergy(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    // Weitzsaecker's Mass formula
    FermiInt nucleiParity = (FermiInt(atomicMass) - FermiInt(chargeNumber)) % 2;                  // pairing
    FermiInt chargeParity = FermiInt(chargeNumber) % 2;

    FermiFloat binding =
        -15.67 * FermiFloat(atomicMass)                                                           // nuclear volume
            + 17.23 * std::pow(atomicMass, 2. / 3.)                                               // surface energy
            + 93.15 * std::pow(FermiFloat(atomicMass) / 2. - FermiFloat(chargeNumber), 2)
                / FermiFloat(atomicMass)                                                          // asymmetry
            + 0.6984523 * std::pow(FermiUInt(chargeNumber), 2) * std::pow(atomicMass, -1. / 3.);  // coulomb

    if (nucleiParity == chargeParity) {
      binding += (nucleiParity + chargeParity - 1) * 12.0 / std::sqrt(FermiFloat(atomicMass));    // pairing
    }

    return -binding * CLHEP::MeV;
  }

  bool VNucleiProperties::IsInvalidNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    return atomicMass < 1_m || chargeNumber < 0_c || FermiUInt(chargeNumber) > FermiUInt(atomicMass);
  }

  void VNucleiProperties::PrintInvalidNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    std::cerr << "Unsupported values for A = " << atomicMass << " and Z = " << chargeNumber << std::endl;
  }

} // namespace properties
