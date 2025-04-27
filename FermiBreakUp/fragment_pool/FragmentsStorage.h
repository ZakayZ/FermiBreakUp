//
// Created by Artem Novikov on 30.01.2024.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTSSTORAGE_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTSSTORAGE_H

#include <any>
#include <vector>

#include "FermiBreakUp/fragment_pool/data_source/DefaultPoolSource.h"
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
    FragmentsStorage(DataSource&& dataSource)
      : data_(std::make_shared<DataSource>(std::move(dataSource)))
      , fragments_()
    {
      for (const auto& ptr: *std::any_cast<std::shared_ptr<DataSource>>(data_)) {
        AddFragment(*ptr);
      }
    }

    size_t Count(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    size_t Count(NucleiData nuclei) const;

    IteratorRange GetFragments(AtomicMass atomicMass, ChargeNumber chargeNumber) const;

    IteratorRange GetFragments(NucleiData nuclei) const;

  private:
    void AddFragment(const Fragment& fragment);

    static inline const Container EMPTY_CONTAINER_ = {};

    const std::any data_;
    std::vector<Container> fragments_;
  };
} // namespace fbu

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTSSTORAGE_H
