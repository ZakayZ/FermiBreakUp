//
// Created by Artem Novikov on 18.02.2024.
//

#include "util/nuclei_properties/data_storage/DefaultNuclearMass.h"

#include "util/Logger.h"

#include "FastNucleiProperties.h"

using namespace fermi;

FastNucleiProperties::FastNucleiProperties()
  : FastNucleiProperties(DefaultNuclearMass())
{
}

FermiFloat FastNucleiProperties::GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
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

bool FastNucleiProperties::IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (atomicMass < 1_m || chargeNumber < 0_c || FermiUInt(chargeNumber) > FermiUInt(atomicMass)) {
    LOG_DEBUG("Unknown particle: A = " << atomicMass << ", Z = " << chargeNumber);
    return false;
  }

  auto slot = GetSlot(atomicMass, chargeNumber);

  return slot < nucleiMasses_.size() && nucleiMasses_[slot].isStable;
}

void FastNucleiProperties::AddStableNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiFloat mass) {
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

void FastNucleiProperties::AddStableNuclei(NucleiData nucleiData, FermiFloat mass) {
  return AddStableNuclei(nucleiData.atomicMass, nucleiData.chargeNumber, mass);
}

size_t FastNucleiProperties::GetSlot(AtomicMass atomicMass, ChargeNumber chargeNumber) {
  auto mass = FermiInt(atomicMass);
  auto charge = FermiInt(chargeNumber);
  return (mass * (mass + 1)) / 2 + charge;
}
