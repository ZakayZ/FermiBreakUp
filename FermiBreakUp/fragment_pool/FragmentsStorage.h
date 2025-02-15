//
// Created by Artem Novikov on 30.01.2024.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTSSTORAGE_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTSSTORAGE_H

#include <vector>

#include "FermiBreakUp/fragment_pool/fragments/Fragment.h"
#include "FermiBreakUp/util/DataTypes.h"

namespace fbu {
  class FragmentsStorage {
  private:
    using Container = std::vector<const Fragment*>;

  public:
    class IteratorRange {
    public:
      using const_iterator = Container::const_iterator;

      IteratorRange(const_iterator begin, const_iterator end)
        : begin_(begin)
        , end_(end)
      {
      }

      const_iterator begin() const { return begin_; }
      const_iterator end() const { return end_; }

    private:
      const_iterator begin_;
      const_iterator end_;
    };

    FragmentsStorage();

    template <typename DataSource>
    FragmentsStorage(const DataSource& dataSource)
      : FragmentsStorage(dataSource.begin(), dataSource.end())
    {
    }

    template <typename Iter>
    FragmentsStorage(Iter begin, Iter end) {
      static_assert(std::is_same_v<typename Iter::value_type, const Fragment*>, "invalid iterator");
      for (auto it = begin; it != end; ++it) {
        AddFragment(**it);
      }
    }

    size_t Count(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    size_t Count(NucleiData nuclei) const;

    IteratorRange GetFragments(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    IteratorRange GetFragments(NucleiData nuclei) const;

    void AddFragment(const Fragment& fragment);

  private:
    static inline const Container EmptyContainer_ = {};

    std::vector<Container> fragments_;
  };
} // namespace fbu

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTSSTORAGE_H
