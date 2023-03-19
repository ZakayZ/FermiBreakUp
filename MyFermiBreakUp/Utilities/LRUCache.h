//
// Created by Artem Novikov on 17.03.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_LRUCACHE_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_LRUCACHE_H_

#include <map>
#include <list>

template <typename Key, typename Value>
class LRUCache {
 public:
  LRUCache(size_t memory_limit) : memory_limit_(memory_limit) {}

  void Insert(const Key& key, const Value& value) {
    auto pos = key_map_.find(key);
    if (pos != key_map_.end()) {
      values_.push_front({key, std::move(pos->second->second)});
      values_.erase(pos->second);
      pos->second = values_.begin();
      return;
    }

    if (values_.size() == memory_limit_) {
      key_map_.erase(values_.back().first);
      values_.pop_back();
    }

    values_.push_front({key, value});
    key_map_.insert({key, values_.begin()});
  }

  void Insert(const Key& key, Value&& value) {
    auto pos = key_map_.find(key);
    if (pos != key_map_.end()) {
      if (pos->second != values_.begin()) {
        values_.push_front({key, std::move(value)});
        values_.erase(pos->second);
        pos->second = values_.begin();
      }
      return;
    }

    if (values_.size() == memory_limit_) {
      key_map_.erase(values_.back().first);
      values_.pop_back();
    }

    values_.push_front({key, std::move(value)});
    key_map_.insert({key, values_.begin()});
  }

  bool Contains(const Key& key) const {
    return key_map_.find(key) != key_map_.end();
  }

  const Value& Get(const Key& key) const {
    return key_map_.at(key)->second;
  }

  void UpdateLimit(size_t new_limit) {
    while (new_limit < values_.size()) {
      key_map_.erase(values_.back().first);
      values_.pop_back();
    }

    memory_limit_ = new_limit;
  }

  void Clear() {
    values_.clear();
    key_map_.clear();
  }

 private:
  using List = std::list<std::pair<Key, Value>>;
  using Map = std::map<Key, typename List::iterator>;

  size_t memory_limit_;
  List values_;
  Map key_map_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_LRUCACHE_H_
