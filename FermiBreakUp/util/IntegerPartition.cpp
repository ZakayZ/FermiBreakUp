//
// Created by Artem Novikov on 17.02.2023.
//

#include "IntegerPartition.h"

using namespace fermi;

IntegerPartition::IntegerPartition(uint32_t number, uint32_t termsCount, uint32_t base)
  : number_(number)
  , termsCount_(termsCount)
  , base_(base)
{
}

IntegerPartition::Iterator IntegerPartition::begin() const {
  return {number_, termsCount_, base_};
}

IntegerPartition::Iterator IntegerPartition::end() const {
  return {0};
}

///////////////////////////////// // ITERATOR//////////////////////////////

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

bool IntegerPartition::Iterator::operator==(const IntegerPartition::Iterator& other) const {
  return partition_ == other.partition_;
}

bool IntegerPartition::Iterator::operator!=(const IntegerPartition::Iterator& other) const {
  return partition_ != other.partition_;
}

IntegerPartition::Iterator::Iterator(uint32_t termsCount) {
  partition_.resize(termsCount, 0); // end partition
}

IntegerPartition::Iterator::Iterator(uint32_t number, uint32_t termsCount, uint32_t base) : Iterator(termsCount) {
  // No possible partitions
  if (number < base * termsCount || termsCount == 0 || number == 0) { return; }

  std::fill(partition_.begin(), partition_.end(), base);
  partition_[0] = number - base * (termsCount - 1);
}

void IntegerPartition::Iterator::NextPartition() {
  uint32_t accumulated = 0;
  for (auto partitionLast = std::next(partition_.begin()); partitionLast != partition_.end(); ++partitionLast) {
    if (partition_.front() >= *partitionLast + 2) {
      --partition_.front();
      ++(*partitionLast);

      auto newValue = *partitionLast;
      std::fill(std::next(partition_.begin()), partitionLast, newValue);
      partition_.front() += accumulated - newValue * (std::distance(partition_.begin(), partitionLast) - 1);
      return;
    }
    accumulated += *partitionLast;
  }

  // last partition
  partition_.clear();
}
