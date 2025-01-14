//
// Created by Artem Novikov on 18.02.2024.
//

#include "util/nuclei_properties/data_storage/DefaultNuclearMass.h"
#include <stdexcept>

#include "FastNucleiProperties.h"

using namespace fermi;

FastNucleiProperties::FastNucleiProperties()
  : FastNucleiProperties(DefaultNuclearMass())
{
}

FermiFloat FastNucleiProperties::GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (FermiInt(atomicMass) < FermiInt(chargeNumber)) {
    throw std::runtime_error(
      "invalid nuclei A = " + std::to_string(atomicMass) + ", Z = " + std::to_string(chargeNumber));
  }

  auto slot = GetSlot(atomicMass, chargeNumber);
  if (slot < nucleiMasses_.size() && nucleiMasses_[slot].isCached) {
    return nucleiMasses_[slot].mass;
  }

#ifdef DEBUG
  std::cerr << "Unknown particle A = " + std::to_string(atomicMass) + ", Z = " + std::to_string(chargeNumber) << '\n';
#endif
  if (slot >= nucleiMasses_.size()) {
    nucleiMasses_.resize(slot + 1);
  }
  nucleiMasses_[slot] = MassData{
    NuclearMass(atomicMass, chargeNumber), // mass
    false, // isStable
    true, // isCached
  };
  return nucleiMasses_[slot].mass;
}

bool FastNucleiProperties::IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (IsInvalidNuclei(atomicMass, chargeNumber)) {
    PrintInvalidNuclei(atomicMass, chargeNumber);
    return false;
  }

  auto slot = GetSlot(atomicMass, chargeNumber);

  return slot < nucleiMasses_.size() && nucleiMasses_[slot].isStable;
}

void FastNucleiProperties::AddStableNuclei(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiFloat mass) {
  if (static_cast<FermiUInt>(chargeNumber) > static_cast<FermiUInt>(atomicMass)) {
    throw std::runtime_error(
      "Invalid particle: A = " + std::to_string(atomicMass) + ", Z = " + std::to_string(chargeNumber));
  }
  auto slot = GetSlot(atomicMass, chargeNumber);
  if (slot >= nucleiMasses_.size()) {
    nucleiMasses_.resize(slot + 1);
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
