//
// Created by Artem Novikov on 09.03.2023.
//

#include <CLHEP/Units/PhysicalConstants.h>

#include "NativeNucleiProperties.h"
#include "table_values/NucleiPropertiesTable.h"
#include "table_values/NucleiPropertiesTableAME12.h"

namespace properties {
  constexpr FermiFloat ProtonMass = CLHEP::proton_mass_c2;
  constexpr FermiFloat NeutronMass = CLHEP::neutron_mass_c2;
  constexpr FermiFloat DeuteronMass = 1.875613 * CLHEP::GeV;
  constexpr FermiFloat TritonMass = 2.808921 * CLHEP::GeV;
  constexpr FermiFloat AlphaMass = 3.727379 * CLHEP::GeV;
  constexpr FermiFloat He3Mass = 2.808391 * CLHEP::GeV;

  constexpr int HashNuclei(const AtomicMass atomicMass, const ChargeNumber chargeNumber) {
    return static_cast<int>(atomicMass) * 100 + static_cast<int>(chargeNumber);
  }

  FermiFloat NativeNucleiProperties::GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
    if (IsInvalidNuclei(atomicMass, chargeNumber)) {
      std::cerr << "NucleiProperties::GetNuclearMass: Wrong values for A = " << atomicMass
                << " and Z = " << chargeNumber << std::endl;
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
    if (IsInvalidNuclei(atomicMass, chargeNumber)) {
      std::cerr << "NucleiProperties::IsInStableTable: Wrong values for A = "
                << atomicMass << " and Z = " << chargeNumber << std::endl;
      return false;
    }

    return NucleiPropertiesTable().ContainsParticle(atomicMass, chargeNumber);
  }

  FermiFloat NativeNucleiProperties::AtomicWeight(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    NucleiPropertiesTableAME12 tableAME12;
    FermiFloat hydrogenMassExcess = tableAME12.GetMassExcess(1_m, 1_c);
    FermiFloat NeutronMassExcess  = tableAME12.GetMassExcess(1_m, 0_c);

    FermiFloat mass = FermiFloat(FermiUInt(atomicMass) - FermiUInt(chargeNumber)) * NeutronMassExcess
        + FermiFloat(chargeNumber) * hydrogenMassExcess - BindingEnergy(atomicMass, chargeNumber)
        + FermiFloat(atomicMass) * CLHEP::amu_c2;

    return mass;
  }

  FermiFloat NativeNucleiProperties::NuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    if (IsInvalidNuclei(atomicMass, chargeNumber)) {
      std::cerr << "NativeNucleiProperties::NuclearMass: Wrong values for A = "
                << atomicMass << " and Z = " << chargeNumber << std::endl;
      return 0;
    }

    FermiFloat mass = AtomicWeight(atomicMass, chargeNumber);
    // atomic mass is converted to nuclear mass according formula in AME03
    mass -= FermiFloat(chargeNumber) * CLHEP::electron_mass_c2;
    mass += (14.4381 * std::pow(chargeNumber, 2.39) + 1.55468 * 1e-6 * std::pow(chargeNumber, 5.35)) * CLHEP::eV;

    return mass;
  }

  FermiFloat NativeNucleiProperties::BindingEnergy(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    // Weitzsaecker's Mass formula
    FermiUInt NPairing = (FermiUInt(atomicMass) - FermiUInt(chargeNumber)) % 2;                      // pairing
    FermiUInt ZPairing = FermiUInt(chargeNumber) % 2;

    FermiFloat binding =
            - 15.67 * FermiFloat(atomicMass)                                                           // nuclear volume
            + 17.23 * std::pow(atomicMass, 2. / 3.)                                                    // surface energy
            + 93.15 * ((FermiFloat(atomicMass) / 2. - FermiFloat(chargeNumber))
            * (FermiFloat(atomicMass) / 2. - FermiFloat(chargeNumber))) / FermiFloat(atomicMass)     // asymmetry
            + 0.6984523 * std::pow(FermiUInt(chargeNumber), 2) * std::pow(atomicMass, -1. / 3.);      // coulomb

    if (NPairing == ZPairing) {
      binding += (NPairing + ZPairing - 1) * 12.0 / std::sqrt(FermiFloat(atomicMass));               // pairing
    }

    return -binding * CLHEP::MeV;
  }

  bool NativeNucleiProperties::IsInvalidNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    return atomicMass < 1_m || chargeNumber < 0_c || FermiUInt(chargeNumber) > FermiUInt(atomicMass);
  }

} // namespace properties
