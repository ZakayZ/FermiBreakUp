//
// Created by Artem Novikov on 30.01.2024.
//

#include "FragmentsStorage.h"

size_t FragmentsStorage::Count(MassNumber mass_number, ChargeNumber charge_number) const {
  if (FermiInt(mass_number) < FermiInt(charge_number)) {
    return 0;
  }

  auto slot = GetSlot(mass_number, charge_number);
  if (slot >= fragments_.size()) [[unlikely]] {
    return 0;
  }

  return fragments_[slot].size();
}

size_t FragmentsStorage::Count(NucleiData nuclei) const {
  return Count(nuclei.mass_number, nuclei.charge_number);
}

FragmentsStorage::RangeIterators FragmentsStorage::GetFragments(MassNumber mass_number,
                                                                ChargeNumber charge_number) const {
  if (FermiInt(mass_number) < FermiInt(charge_number)) {
    return {fragments_[0].end(), fragments_[0].end()};
  }

  auto slot = GetSlot(mass_number, charge_number);
  if (slot >= fragments_.size()) [[unlikely]] {
    return {fragments_[0].end(), fragments_[0].end()};
  }

  return {fragments_[slot].begin(), fragments_[slot].end()};
}

FragmentsStorage::RangeIterators FragmentsStorage::GetFragments(NucleiData nuclei) const {
  return GetFragments(nuclei.mass_number, nuclei.charge_number);
}

void FragmentsStorage::AddFragment(const FermiFragment& fragment) {
  auto slot = GetSlot(fragment.GetMassNumber(), fragment.GetChargeNumber());
  if (slot >= fragments_.size()) {
    fragments_.resize(slot + 1);
  }
  fragments_[slot].push_back(&fragment);
}

size_t FragmentsStorage::GetSlot(MassNumber mass_number, ChargeNumber charge_number) {
  auto mass = FermiInt(mass_number);
  auto charge = FermiInt(charge_number);
  return (mass * (mass + 1)) / 2 + charge;
}
