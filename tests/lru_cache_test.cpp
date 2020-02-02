#include <gtest/gtest.h>
#include "../cache/lru_cache.h"

TEST(Lru, DefaultSize)
{
    lru::TLruCache<int, int> cache(2);
    ASSERT_EQ(cache.size(), 0);
}

TEST(Lru, Size)
{
    lru::TLruCache<std::string, std::string> cache(2);
    ASSERT_EQ(cache.size(), 0);

    cache.insert("first", "1");
    ASSERT_EQ(cache.size(), 1);

    cache.insert("second", "2");
    ASSERT_EQ(cache.size(), 2);

    cache.insert("third", "3");
    ASSERT_EQ(cache.size(), 2);
}

TEST(Lru, Insert)
{
    lru::TLruCache<std::string, std::string> cache(2);
    cache.insert("first", "1");
    cache.insert("second", "2");
    cache.insert("third", "3");

    const auto item = cache.find("third");
    ASSERT_TRUE(item.has_value());
    ASSERT_EQ(item.value(), "3");
}

TEST(Lru, Upsert)
{
    lru::TLruCache<std::string, std::string> cache(2);
    cache.upsert("first", "1");
    cache.upsert("second", "2");
    cache.upsert("first", "111");

    const auto item = cache.find("first");
    ASSERT_TRUE(item.has_value());
    ASSERT_EQ(item.value(), "111");
}

TEST(Lru, Erase)
{
    lru::TLruCache<std::string, std::string> cache(2);
    cache.upsert("first", "1");
    cache.upsert("second", "2");

    cache.erase("second");

    ASSERT_FALSE(cache.find("second").has_value());
    ASSERT_TRUE(cache.find("first").has_value());
}

TEST(Lru, Find)
{
    lru::TLruCache<std::string, std::string> cache(2);
    cache.insert("first", "1");
    cache.insert("second", "2");
    cache.insert("third", "3");

    ASSERT_TRUE(cache.find("second").has_value());
    ASSERT_FALSE(cache.find("first").has_value());
}

TEST(Lru, UpdatedFind)
{
    lru::TLruCache<std::string, std::string> cache(2);
    cache.insert("first", "1");
    cache.insert("second", "2");

    const auto value = cache.updated_find("first");
    ASSERT_EQ(value, "1");

    cache.insert("third", "3");
    ASSERT_FALSE(cache.find("second").has_value());
}