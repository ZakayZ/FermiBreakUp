//
// Created by Artem Novikov on 20.03.2023.
//

#include <gtest/gtest.h>

#include "LRUCache.h"

TEST(LRUCacheTests, StoreTest) {
  LRUCache<int, int> int_cache(2);

  int_cache.Insert(1, 1);
  int_cache.Insert(2, 2);

  ASSERT_TRUE(int_cache.Contains(1));
  ASSERT_EQ(int_cache.Get(1), 1);

  ASSERT_TRUE(int_cache.Contains(2));
  ASSERT_EQ(int_cache.Get(2), 2);

  /// preserve value if nothing new
  int_cache.Insert(1, 1);
  ASSERT_TRUE(int_cache.Contains(2));
  ASSERT_EQ(int_cache.Get(2), 2);
}

TEST(LRUCacheTests, DisplacmentTest) {
  LRUCache<int, int> int_cache(2);

  int_cache.Insert(1, 1);
  int_cache.Insert(2, 2);

  ASSERT_FALSE(int_cache.Contains(3));
  int_cache.Insert(3, 3);
  ASSERT_TRUE(int_cache.Contains(3));
  ASSERT_FALSE(int_cache.Contains(1));
}

TEST(LRUCacheTests, MoveTest) {
  LRUCache<int, std::string> str_cache(2);

  str_cache.Insert(1, "hello");

  std::string s = "world";
  str_cache.Insert(2, std::move(s));

  ASSERT_TRUE(str_cache.Contains(2));
  ASSERT_EQ(str_cache.Get(2), "world");
  ASSERT_EQ(s, "");
}

TEST(LRUCacheTests, ReorderingTest) {
  LRUCache<int, int> int_cache(2);

  int_cache.Insert(1, 1);
  int_cache.Insert(2, 2);
  int_cache.Insert(1, 1);
  int_cache.Insert(3, 3);
  ASSERT_TRUE(int_cache.Contains(1));
  ASSERT_TRUE(int_cache.Contains(3));
  ASSERT_FALSE(int_cache.Contains(2));
}

TEST(LRUCacheTests, ResizingTest) {
  LRUCache<int, int> int_cache(3);

  int_cache.Insert(1, 1);
  int_cache.Insert(2, 2);
  int_cache.Insert(3, 3);

  ASSERT_TRUE(int_cache.Contains(3));
  ASSERT_TRUE(int_cache.Contains(2));
  ASSERT_TRUE(int_cache.Contains(1));

  int_cache.UpdateLimit(2);
  ASSERT_TRUE(int_cache.Contains(3));
  ASSERT_TRUE(int_cache.Contains(2));
  ASSERT_FALSE(int_cache.Contains(1));

  int_cache.Insert(4, 5);
  ASSERT_TRUE(int_cache.Contains(4));
  ASSERT_TRUE(int_cache.Contains(3));
  ASSERT_FALSE(int_cache.Contains(2));
  ASSERT_FALSE(int_cache.Contains(1));
}

TEST(LRUCacheTests, ClearTest) {
  LRUCache<int, int> int_cache(3);

  int_cache.Insert(1, 1);
  int_cache.Insert(2, 2);
  int_cache.Insert(3, 3);

  ASSERT_TRUE(int_cache.Contains(1));
  ASSERT_TRUE(int_cache.Contains(2));
  ASSERT_TRUE(int_cache.Contains(3));

  int_cache.Clear();

  ASSERT_FALSE(int_cache.Contains(1));
  ASSERT_FALSE(int_cache.Contains(2));
  ASSERT_FALSE(int_cache.Contains(3));

  int_cache.Insert(1, 1);
  int_cache.Insert(2, 2);
  int_cache.Insert(3, 3);

  ASSERT_TRUE(int_cache.Contains(1));
  ASSERT_TRUE(int_cache.Contains(2));
  ASSERT_TRUE(int_cache.Contains(3));
}