//
// Created by Artem Novikov on 17.02.2023.
//

#include "IntegerPartition.h"

IntegerPartition::IntegerPartition(uint32_t number, uint32_t terms_count, bool allow_zero)
    : number_(number), terms_count_(terms_count), allow_zero_(allow_zero) {}

IntegerPartition::Iterator IntegerPartition::begin() const {
  return IntegerPartition::Iterator(number_, terms_count_, allow_zero_);
}

IntegerPartition::Iterator IntegerPartition::end() const {
  return IntegerPartition::Iterator(0);
}

//////////////////////////////////////////////////////ITERATOR////////////////////////////////////////////

IntegerPartition::Iterator::pointer IntegerPartition::Iterator::operator->() const {
  return &partition_;
}

IntegerPartition::Iterator::reference IntegerPartition::Iterator::operator*() const {
  return partition_;
}

IntegerPartition::Iterator& IntegerPartition::Iterator::operator++() {
  NextPartition();
  return *this;
}

IntegerPartition::Iterator IntegerPartition::Iterator::operator++(int) {
  auto copy = *this;
  NextPartition();
  return copy;
}

bool IntegerPartition::Iterator::operator==(IntegerPartition::Iterator& other) const {
  return partition_ == other.partition_;
}

bool IntegerPartition::Iterator::operator!=(IntegerPartition::Iterator& other) const {
  return partition_ != other.partition_;
}

IntegerPartition::Iterator::Iterator(uint32_t terms_count) {
  partition_.resize(terms_count, 0); /// end partition
}

IntegerPartition::Iterator::Iterator(uint32_t number, uint32_t terms_count, bool allow_zero) : Iterator(terms_count) {
  if (number < terms_count && !allow_zero || terms_count == 0 || number == 0) { return; } /// No possible partitions

  if (allow_zero) {
    partition_[0] = number;
    return;
  }

  std::fill(partition_.begin(), partition_.end(), 1);
  partition_[0] = number - terms_count + 1;
}

void IntegerPartition::Iterator::NextPartition() {
  /// TODO store last update position, might improve performance
  for (auto it = partition_.rbegin(); it != partition_.rend(); ++it) {
    auto prev = it;
    ++prev;

    if (prev == partition_.rend()) { /// It was last partition
      partition_.clear();
      return;
    }

    if (*prev >= *it + 2) {
      *prev -= 1;
      *it += 1;
      return;
    }
  }
}