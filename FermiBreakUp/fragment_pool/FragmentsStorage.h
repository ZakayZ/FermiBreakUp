//
// Created by Artem Novikov on 30.01.2024.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTSSTORAGE_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTSSTORAGE_H

#include <vector>

#include "util/DataTypes.h"
#include "fragments/Fragment.h"

namespace fermi {

  class FragmentsStorage {
  private:
    using Container = std::vector<const Fragment*>;

  public:
    using RangeIterators = std::pair<Container::const_iterator, Container::const_iterator>;

    FragmentsStorage();

    template <typename DataSource>
    FragmentsStorage(const DataSource& dataSource);

    template <typename Iter>
    FragmentsStorage(Iter begin, Iter end);

    [[nodiscard]] size_t Count(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    [[nodiscard]] size_t Count(NucleiData nuclei) const;

    [[nodiscard]] RangeIterators GetFragments(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    [[nodiscard]] RangeIterators GetFragments(NucleiData nuclei) const;

    void AddFragment(const Fragment& fragment);

  private:
    [[nodiscard]] static size_t GetSlot(AtomicMass atomicMass, ChargeNumber chargeNumber);

    std::vector<Container> fragments_;
  };

} // namespace fermi

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTSSTORAGE_H
