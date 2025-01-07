//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPINTEGERPARTITIONH_
#define FERMIBREAKUPMYFERMIBREAKUPINTEGERPARTITIONH_

#include <vector>
#include <cstddef>
#include <cstdint>

namespace fermi {

  using Partition = std::vector<uint32_t>;

  class IntegerPartition {
  public:
    class Iterator;

    Iterator begin() const;

    Iterator end() const;

    IntegerPartition(uint32_t number, uint32_t termsCount, uint32_t base = 1);

  private:
    uint32_t number_;
    uint32_t termsCount_;
    uint32_t base_;
  };

  class IntegerPartition::Iterator {
  public:
    friend class IntegerPartition;

    using differenceType = size_t;

    using value_type = Partition;

    using reference = const Partition&;

    using pointer = const Partition*;

    using iteratorCategory = std::forward_iterator_tag;

    Iterator() = delete;

    Iterator(const Iterator&) = default;

    Iterator& operator=(const Iterator&) = default;

    pointer operator->() const;

    reference operator*() const;

    Iterator& operator++();

    Iterator operator++(int);

    bool operator==(const Iterator& other) const;

    bool operator!=(const Iterator& other) const;

  private:
    Iterator(uint32_t termsCount);

    Iterator(uint32_t number, uint32_t termsCount, uint32_t base);

    void NextPartition();

    Partition partition_;
  };

}  // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPINTEGERPARTITIONH_
