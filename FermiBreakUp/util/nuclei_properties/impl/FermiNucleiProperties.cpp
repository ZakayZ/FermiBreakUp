//
// Created by Artem Novikov on 18.02.2024.
//

#include <CLHEP/Units/PhysicalConstants.h>

#include "util/nuclei_properties/data_storage/DefaultNuclearMass.h"
#include "util/Logger.h"

#include "FermiNucleiProperties.h"

using namespace fermi;

namespace {
  FermiFloat WeitzsaeckerBindingEnergy(AtomicMass atomicMass, ChargeNumber chargeNumber) {
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
      binding += 12.0 * (nucleiParity + chargeParity - 1) / std::sqrt(FermiFloat(atomicMass)); // pairing
    }

    return -binding * CLHEP::MeV;
  }

  FermiFloat EstimateAtomicWeight(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    constexpr FermiFloat hydrogenMassExcess = 7.28897;
    constexpr FermiFloat neutronMassExcess = 8.07132;

    return FermiFloat(FermiInt(atomicMass) - FermiInt(chargeNumber)) * neutronMassExcess
        + FermiFloat(chargeNumber) * hydrogenMassExcess - WeitzsaeckerBindingEnergy(atomicMass, chargeNumber)
        + FermiFloat(atomicMass) * CLHEP::amu_c2;
  }

  FermiFloat EstimateNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    auto mass = EstimateAtomicWeight(atomicMass, chargeNumber);

    // atomic mass is converted to nuclear mass according formula in AME03
    mass -= FermiFloat(chargeNumber) * CLHEP::electron_mass_c2;
    mass += (
      14.4381 * std::pow(FermiFloat(chargeNumber), 2.39) 
      + 1.55468e-6 * std::pow(FermiFloat(chargeNumber), 5.35)
    ) * CLHEP::eV;

    return mass;
  }
} // namespace

FermiNucleiProperties::FermiNucleiProperties()
  : FermiNucleiProperties(DefaultNuclearMass())
{
}

FermiFloat FermiNucleiProperties::GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  ASSERT_MSG(FermiInt(atomicMass) >= FermiInt(chargeNumber),
             "invalid nuclei A = " << atomicMass << ", Z = " << chargeNumber);

  auto slot = GetSlot(atomicMass, chargeNumber);
  if (slot < nucleiMasses_.size() && nucleiMasses_[slot].isCached) {
    return nucleiMasses_[slot].mass;
  }

  LOG_DEBUG("Unknown particle: A = " << atomicMass << ", Z = " << chargeNumber);

  if (slot >= nucleiMasses_.size()) {
    nucleiMasses_.resize(slot + FermiUInt(atomicMass));
  }

  nucleiMasses_[slot] = MassData{
    EstimateNuclearMass(atomicMass, chargeNumber), // mass
    false, // isStable
    true, // isCached
  };
  return nucleiMasses_[slot].mass;
}

bool FermiNucleiProperties::IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (atomicMass < 1_m || chargeNumber < 0_c || FermiUInt(chargeNumber) > FermiUInt(atomicMass)) {
    LOG_DEBUG("Unknown particle: A = " << atomicMass << ", Z = " << chargeNumber);
    return false;
  }

  auto slot = GetSlot(atomicMass, chargeNumber);

  return slot < nucleiMasses_.size() && nucleiMasses_[slot].isStable;
}

void FermiNucleiProperties::AddStableNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiFloat mass) {
  ASSERT_MSG(FermiInt(atomicMass) >= FermiInt(chargeNumber),
             "invalid particle: A = " << atomicMass << ", Z = " << chargeNumber);

  auto slot = GetSlot(atomicMass, chargeNumber);
  if (slot >= nucleiMasses_.size()) {
    nucleiMasses_.resize(slot + FermiUInt(atomicMass));
  }

  nucleiMasses_[slot] = MassData{
    mass, // mass
    true, // isStable
    true, // isCached
  };
}

void FermiNucleiProperties::AddStableNuclei(NucleiData nucleiData, FermiFloat mass) {
  return AddStableNuclei(nucleiData.atomicMass, nucleiData.chargeNumber, mass);
}

size_t FermiNucleiProperties::GetSlot(AtomicMass atomicMass, ChargeNumber chargeNumber) {
  auto mass = FermiInt(atomicMass);
  auto charge = FermiInt(chargeNumber);
  return (mass * (mass + 1)) / 2 + charge;
}
