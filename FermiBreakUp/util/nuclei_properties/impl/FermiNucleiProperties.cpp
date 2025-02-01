//
// Created by Artem Novikov on 18.02.2024.
//

#include <CLHEP/Units/PhysicalConstants.h>

#include "util/nuclei_properties/data_storage/DefaultNuclearMass.h"
#include "util/Logger.h"

#include "FermiNucleiProperties.h"

using namespace fbu;

namespace {
  FermiFloat WeitzsaeckerBindingEnergy(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    // Weitzsaecker's Mass formula
    const auto nucleiParity = (FermiInt(atomicMass) - FermiInt(chargeNumber)) % 2;            // pairing
    const auto chargeParity = FermiInt(chargeNumber) % 2;

    const auto atomicMassF = FermiFloat(atomicMass);
    const auto chargeNumberF = FermiFloat(chargeNumber);

    FermiFloat binding =
            -15.67 * atomicMassF                                                              // nuclear volume
            + 17.23 * std::pow(atomicMassF, 2. / 3.)                                          // surface energy
            + 93.15 * std::pow(atomicMassF / 2. - chargeNumberF, 2)
                / atomicMassF                                                                 // asymmetry
            + 0.6984523 * std::pow(chargeNumberF, 2) / std::cbrt(atomicMassF);                // coulomb

    if (nucleiParity == chargeParity) {
      binding += 12.0 * (nucleiParity + chargeParity - 1) / std::sqrt(atomicMassF);    // pairing
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

  inline size_t GetSlot(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    const auto mass = FermiUInt(atomicMass);
    const auto charge = FermiUInt(chargeNumber);
    return (mass * (mass + 1)) / 2 + charge;
  }
} // namespace

FermiNucleiProperties::FermiNucleiProperties()
  : FermiNucleiProperties(DefaultNuclearMass())
{
}

FermiFloat FermiNucleiProperties::GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  ASSERT_MSG(FermiUInt(atomicMass) >= FermiUInt(chargeNumber),
             "invalid nuclei A = " << atomicMass << ", Z = " << chargeNumber);

  const auto slot = GetSlot(atomicMass, chargeNumber);
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

  const auto slot = GetSlot(atomicMass, chargeNumber);

  return slot < nucleiMasses_.size() && nucleiMasses_[slot].isStable;
}

void FermiNucleiProperties::AddStableNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiFloat mass) {
  ASSERT_MSG(FermiUInt(atomicMass) >= FermiUInt(chargeNumber),
             "invalid particle: A = " << atomicMass << ", Z = " << chargeNumber);

  const auto slot = GetSlot(atomicMass, chargeNumber);
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
