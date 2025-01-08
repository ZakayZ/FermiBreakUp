//
// Created by Artem Novikov on 18.02.2024.
//

#include "utilities/nuclei_properties/data_storage/DefaultNuclearMass.h"

#include "FastNucleiProperties.h"

namespace properties {

FastNucleiProperties::FastNucleiProperties() : FastNucleiProperties(DefaultNuclearMass()) {}

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
  return NuclearMass(atomicMass, chargeNumber);
}

FermiFloat FastNucleiProperties::GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) {
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
  nucleiMasses_[slot] = MassData{.mass=NuclearMass(atomicMass, chargeNumber), .isValid=false, .isCached=true};
  return nucleiMasses_[slot].mass;
}

bool FastNucleiProperties::IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (IsInvalidNuclei(atomicMass, chargeNumber)) {
    PrintInvalidNuclei(atomicMass, chargeNumber);
    return false;
  }

  auto slot = GetSlot(atomicMass, chargeNumber);
  if (slot >= nucleiMasses_.size() || !nucleiMasses_[slot].isValid) {
    return false;
  }

  return true;
}

void FastNucleiProperties::AddMass(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiFloat mass) {
  auto slot = GetSlot(atomicMass, chargeNumber);
  if (slot >= nucleiMasses_.size()) {
    nucleiMasses_.resize(slot + 1);
  }
  nucleiMasses_[slot] = MassData{.mass=mass, .isValid=true, .isCached=true};
}

void FastNucleiProperties::AddMass(NucleiData nucleiData, FermiFloat mass) {
  return AddMass(nucleiData.atomicMass, nucleiData.chargeNumber, mass);
}

size_t FastNucleiProperties::GetSlot(AtomicMass atomicMass, ChargeNumber chargeNumber) {
  auto mass = FermiInt(atomicMass);
  auto charge = FermiInt(chargeNumber);
  return (mass * (mass + 1)) / 2 + charge;
}

} // properties
