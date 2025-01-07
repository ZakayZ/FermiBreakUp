//
// Created by Artem Novikov on 18.02.2024.
//

#include "Utilities/NucleiProperties/DataStorage/DefaultNuclearMass.h"

#include "FastNucleiProperties.h"

namespace properties {

FastNucleiProperties::FastNucleiProperties() : FastNucleiProperties(DefaultNuclearMass()) {}

FermiFloat FastNucleiProperties::GetNuclearMass(MassNumber massNumber, ChargeNumber chargeNumber) const {
#if _Cplusplus >= 202002L
  if (FermiInt(massNumber) < FermiInt(chargeNumber)) [[unlikely]] {
#else
  if (FermiInt(massNumber) < FermiInt(chargeNumber)) {
#endif
    throw std::runtime_error(
        "invalid nuclei A = " + std::to_string(massNumber) + ", Z = " + std::to_string(chargeNumber));
  }

  auto slot = GetSlot(massNumber, chargeNumber);
  if (slot < nucleiMasses_.size() && nucleiMasses_[slot].isCached) {
    return nucleiMasses_[slot].mass;
  }

#ifdef DEBUG
  std::cerr << "Unknown particle A = " + std::to_string(massNumber) + ", Z = " + std::to_string(chargeNumber) << '\n';
#endif
  return NuclearMass(massNumber, chargeNumber);
}

FermiFloat FastNucleiProperties::GetNuclearMass(MassNumber massNumber, ChargeNumber chargeNumber) {
#if _Cplusplus >= 202002L
  if (FermiInt(massNumber) < FermiInt(chargeNumber)) [[unlikely]] {
#else
  if (FermiInt(massNumber) < FermiInt(chargeNumber)) {
#endif
    throw std::runtime_error(
        "invalid nuclei A = " + std::to_string(massNumber) + ", Z = " + std::to_string(chargeNumber));
  }

  auto slot = GetSlot(massNumber, chargeNumber);
  if (slot < nucleiMasses_.size() && nucleiMasses_[slot].isCached) {
    return nucleiMasses_[slot].mass;
  }

#ifdef DEBUG
  std::cerr << "Unknown particle A = " + std::to_string(massNumber) + ", Z = " + std::to_string(chargeNumber) << '\n';
#endif
  if (slot >= nucleiMasses_.size()) {
    nucleiMasses_.resize(slot + 1);
  }
  nucleiMasses_[slot] = MassData{.mass=NuclearMass(massNumber, chargeNumber), .isValid=false, .isCached=true};
  return nucleiMasses_[slot].mass;
}

bool FastNucleiProperties::IsStable(MassNumber massNumber, ChargeNumber chargeNumber) const {
#if _Cplusplus >= 202002L
  if (IsInvalidNuclei(massNumber, chargeNumber)) [[unlikely]] {
#else
  if (IsInvalidNuclei(massNumber, chargeNumber)) {
#endif
    PrintInvalidNuclei(massNumber, chargeNumber);
    return false;
  }

  auto slot = GetSlot(massNumber, chargeNumber);
  if (slot >= nucleiMasses_.size() || !nucleiMasses_[slot].isValid) {
    return false;
  }

  return true;
}

void FastNucleiProperties::AddMass(MassNumber massNumber, ChargeNumber chargeNumber, FermiFloat mass) {
  auto slot = GetSlot(massNumber, chargeNumber);
  if (slot >= nucleiMasses_.size()) {
    nucleiMasses_.resize(slot + 1);
  }
  nucleiMasses_[slot] = MassData{.mass=mass, .isValid=true, .isCached=true};
}

void FastNucleiProperties::AddMass(NucleiData nucleiData, FermiFloat mass) {
  return AddMass(nucleiData.massNumber, nucleiData.chargeNumber, mass);
}

size_t FastNucleiProperties::GetSlot(MassNumber massNumber, ChargeNumber chargeNumber) {
  auto mass = FermiInt(massNumber);
  auto charge = FermiInt(chargeNumber);
  return (mass * (mass + 1)) / 2 + charge;
}

} // properties
