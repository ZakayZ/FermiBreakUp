//
// Created by Artem Novikov on 30.01.2024.
//

#include "DataSource/DefaultPoolSource.h"

#include "FragmentsStorage.h"

namespace fermi {

  FragmentsStorage::FragmentsStorage() : FragmentsStorage(DefaultPoolSource()) {}

  template <typename DataSource>
  FragmentsStorage::FragmentsStorage(const DataSource& dataSource)
      : FragmentsStorage(dataSource.begin(), dataSource.end()) {}

  template <typename Iter>
  FragmentsStorage::FragmentsStorage(Iter begin, Iter end) {
    static_assert(std::is_same_v<typename Iter::value_type, const Fragment*>, "invalid iterator");
    for (auto it = begin; it != end; ++it) {
      AddFragment(**it);
    }
  }

  size_t FragmentsStorage::Count(MassNumber massNumber, ChargeNumber chargeNumber) const {
    if (FermiInt(massNumber) < FermiInt(chargeNumber)) {
      return 0;
    }

    auto slot = GetSlot(massNumber, chargeNumber);
    if (slot >= fragments_.size()) {
      return 0;
    }

    return fragments_[slot].size();
  }

  size_t FragmentsStorage::Count(NucleiData nuclei) const {
    return Count(nuclei.massNumber, nuclei.chargeNumber);
  }

  FragmentsStorage::RangeIterators FragmentsStorage::GetFragments(MassNumber massNumber,
                                                                  ChargeNumber chargeNumber) const {
    if (FermiInt(massNumber) < FermiInt(chargeNumber)) {
      return {fragments_[0].end(), fragments_[0].end()};
    }

    auto slot = GetSlot(massNumber, chargeNumber);
    if (slot >= fragments_.size()) {
      return {fragments_[0].end(), fragments_[0].end()};
    }

    return {fragments_[slot].begin(), fragments_[slot].end()};
  }

  FragmentsStorage::RangeIterators FragmentsStorage::GetFragments(NucleiData nuclei) const {
    return GetFragments(nuclei.massNumber, nuclei.chargeNumber);
  }

  void FragmentsStorage::AddFragment(const Fragment& fragment) {
    auto slot = GetSlot(fragment.GetMassNumber(), fragment.GetChargeNumber());
    if (slot >= fragments_.size()) {
      fragments_.resize(slot + 1);
    }
    fragments_[slot].push_back(&fragment);
  }

  size_t FragmentsStorage::GetSlot(MassNumber massNumber, ChargeNumber chargeNumber) {
    auto mass = FermiInt(massNumber);
    auto charge = FermiInt(chargeNumber);
    return (mass * (mass + 1)) / 2 + charge;
  }

} // namespace fermi
