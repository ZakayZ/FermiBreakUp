//
// Created by Artem Novikov on 30.01.2024.
//

#include "util/Logger.h"
#include "data_source/DefaultPoolSource.h"

#include "FragmentsStorage.h"

using namespace fbu;

namespace {
  inline size_t GetSlot(AtomicMass atomicMass, ChargeNumber chargeNumber) {
    const auto mass = FermiUInt(atomicMass);
    const auto charge = FermiUInt(chargeNumber);
    return (mass * (mass + 1)) / 2 + charge;
  }
} // namespace

FragmentsStorage::FragmentsStorage()
  : FragmentsStorage(DefaultPoolSource())
{
}

size_t FragmentsStorage::Count(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (FERMI_UNLIKELY(FermiUInt(atomicMass) < FermiUInt(chargeNumber))) {
    return 0;
  }

  const auto slot = GetSlot(atomicMass, chargeNumber);
  if (FERMI_UNLIKELY(slot >= fragments_.size())) {
    return 0;
  }

  return fragments_[slot].size();
}

size_t FragmentsStorage::Count(NucleiData nuclei) const {
  return Count(nuclei.atomicMass, nuclei.chargeNumber);
}

FragmentsStorage::IteratorRange FragmentsStorage::GetFragments(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (FERMI_UNLIKELY(FermiUInt(atomicMass) < FermiUInt(chargeNumber))) {
    return {EmptyContainer_.begin(), EmptyContainer_.end()};
  }

  const auto slot = GetSlot(atomicMass, chargeNumber);
  if (slot >= fragments_.size()) {
    return {EmptyContainer_.begin(), EmptyContainer_.end()};
  }

  return {fragments_[slot].begin(), fragments_[slot].end()};
}

FragmentsStorage::IteratorRange FragmentsStorage::GetFragments(NucleiData nuclei) const {
  return GetFragments(nuclei.atomicMass, nuclei.chargeNumber);
}

void FragmentsStorage::AddFragment(const Fragment& fragment) {
  const auto slot = GetSlot(fragment.GetAtomicMass(), fragment.GetChargeNumber());
  if (slot >= fragments_.size()) {
    fragments_.resize(slot + 1);
  }
  fragments_[slot].push_back(&fragment);
}
