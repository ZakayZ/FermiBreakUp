//
// Created by Artem Novikov on 30.01.2024.
//

#include "data_source/DefaultPoolSource.h"

#include "FragmentsStorage.h"

using namespace fermi;

FragmentsStorage::FragmentsStorage() : FragmentsStorage(DefaultPoolSource()) {}

template <typename DataSource>
FragmentsStorage::FragmentsStorage(const DataSource& dataSource)
  : FragmentsStorage(dataSource.begin(), dataSource.end())
{
}

template <typename Iter>
FragmentsStorage::FragmentsStorage(Iter begin, Iter end) {
  static_assert(std::is_same_v<typename Iter::value_type, const Fragment*>, "invalid iterator");
  for (auto it = begin; it != end; ++it) {
    AddFragment(**it);
  }
}

size_t FragmentsStorage::Count(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (FermiInt(atomicMass) < FermiInt(chargeNumber)) {
    return 0;
  }

  auto slot = GetSlot(atomicMass, chargeNumber);
  if (slot >= fragments_.size()) {
    return 0;
  }

  return fragments_[slot].size();
}

size_t FragmentsStorage::Count(NucleiData nuclei) const {
  return Count(nuclei.atomicMass, nuclei.chargeNumber);
}

FragmentsStorage::IteratorRange FragmentsStorage::GetFragments(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (FermiInt(atomicMass) < FermiInt(chargeNumber)) {
    return {EmptyContainer_.begin(), EmptyContainer_.end()};
  }

  auto slot = GetSlot(atomicMass, chargeNumber);
  if (slot >= fragments_.size()) {
    return {EmptyContainer_.begin(), EmptyContainer_.end()};
  }

  return {fragments_[slot].begin(), fragments_[slot].end()};
}

FragmentsStorage::IteratorRange FragmentsStorage::GetFragments(NucleiData nuclei) const {
  return GetFragments(nuclei.atomicMass, nuclei.chargeNumber);
}

void FragmentsStorage::AddFragment(const Fragment& fragment) {
  auto slot = GetSlot(fragment.GetAtomicMass(), fragment.GetChargeNumber());
  if (slot >= fragments_.size()) {
    fragments_.resize(slot + 1);
  }
  fragments_[slot].push_back(&fragment);
}

size_t FragmentsStorage::GetSlot(AtomicMass atomicMass, ChargeNumber chargeNumber) {
  auto mass = FermiInt(atomicMass);
  auto charge = FermiInt(chargeNumber);
  return (mass * (mass + 1)) / 2 + charge;
}
