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
  /// No possible partitions
  if (number < terms_count && !allow_zero || terms_count == 0 || number == 0) { return; }

  if (allow_zero) {
    partition_[0] = number;
    return;
  }

  std::fill(partition_.begin(), partition_.end(), 1);
  partition_[0] = number - terms_count + 1;
}

void IntegerPartition::Iterator::NextPartition() {
  uint32_t accumulated = 0;
  for (auto partition_last = std::next(partition_.begin()); partition_last != partition_.end(); ++partition_last) {
    if (partition_.front() >= *partition_last + 2) {
      --partition_.front();
      ++(*partition_last);

      auto new_value = *partition_last;
      std::fill(std::next(partition_.begin()), partition_last, new_value);
      partition_.front() += accumulated - new_value * (std::distance(partition_.begin(), partition_last) - 1);
      return;
    }
    accumulated += *partition_last;
  }

  /// last partition
  partition_.clear();
}