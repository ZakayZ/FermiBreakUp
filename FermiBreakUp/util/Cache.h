//
// Created by Artem Novikov on 15.01.2025.
//

#ifndef FERMIBREAKUP_UTILITIES_CACHE_H
#define FERMIBREAKUP_UTILITIES_CACHE_H

#include <cassert>
#include <memory>
#include <unordered_map>
#include <map>

#include "DataTypes.h"
#include "Logger.h"

namespace fermi {
  template <typename Key, typename Value>
  class LFUCache: public VCache<Key, Value> {
  public:
    LFUCache(size_t maxSize)
      : frequencyStorage_()
      , cache_()
      , maxSize_(maxSize)
    {
      ASSERT_MSG(maxSize_ > 0, "Cahce size must be positive");
    }

    std::shared_ptr<Value> Insert(const Key& key, Value&& value) override {
      if (auto it = cache_.find(key); it != cache_.end()) {
        frequencyStorage_.erase(it->second.second);
        it->second.second = frequencyStorage_.insert({1, key});
        return it->second.first;
      }

      if (cache_.size() == maxSize_) {
        auto lowestIt = frequencyStorage_.begin();
        cache_.erase(lowestIt->second);
        frequencyStorage_.erase(lowestIt);
      }

      auto it = frequencyStorage_.insert({1, key});
      auto [insertedIt, _] = cache_.emplace(key, std::make_pair(std::make_shared<Value>(std::move(value)), it));
      return insertedIt->second.first;
    }

    std::shared_ptr<Value> Get(const Key& key) override {
      if (auto it = cache_.find(key); it != cache_.end()) {
        auto& freqIter = it->second.second;
        const auto newCount = freqIter->first + 1;
        frequencyStorage_.erase(freqIter);
        it->second.second = frequencyStorage_.insert({newCount, key});
        return it->second.first;
      }

      return nullptr;
    }

  private:
    using FrequencyStorage = std::multimap<std::size_t, Key>;
    using FrequencyIter = typename FrequencyStorage::iterator;

    FrequencyStorage frequencyStorage_;
    std::unordered_map<Key, std::pair<std::shared_ptr<Value>, FrequencyIter>> cache_;
    std::size_t maxSize_;
  };

  template <typename Key, typename Value>
  class SimpleCache: public VCache<Key, Value> {
  public:
    SimpleCache() = default;

    std::shared_ptr<Value> Insert(const Key& key, Value&& value) override {
      cachedItem_ = {key, std::make_shared<Value>(std::move(value))};
      return cachedItem_->second;
    }

    std::shared_ptr<Value> Get(const Key& key) override {
      if (cachedItem_.has_value() && cachedItem_->first == key) {
        return cachedItem_->second;
      }

      return nullptr;
    }

  private:
    std::optional<std::pair<Key, std::shared_ptr<Value>>> cachedItem_;
  };
} // namespace fermi

#endif // FERMIBREAKUP_UTILITIES_CACHE_H
