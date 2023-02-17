//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_INTEGERPARTITION_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_INTEGERPARTITION_H_

#include <vector>

using Partition = std::vector<uint32_t>;

class IntegerPartition {
 public:
  class Iterator;

  Iterator begin() const;

  Iterator end() const;

  IntegerPartition(uint32_t number, uint32_t terms_count, bool allow_zero = true);

 private:
  uint32_t number_;
  uint32_t terms_count_;
  bool allow_zero_;
};

/// TOOD iterator class to iterate over Partitions

class IntegerPartition::Iterator {
 public:
  friend class IntegerPartition;

  using difference_type = size_t;

  using value_type = Partition;

  using reference = const Partition&;

  using pointer = const Partition*;

  using iterator_category = std::forward_iterator_tag;

  Iterator() = delete;

  Iterator(const Iterator&) = default;

  Iterator& operator=(const Iterator&) = default;

  pointer operator->() const;

  reference operator*() const;

  Iterator& operator++();

  Iterator operator++(int);

  bool operator==(Iterator& other) const;

  bool operator!=(Iterator& other) const;

 private:
  Iterator(uint32_t terms_count);

  Iterator(uint32_t number, uint32_t terms_count, bool allow_zero);

  void NextPartition();

  Partition partition_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_INTEGERPARTITION_H_
