#pragma once

#include <list>
#include <unordered_map>

namespace lru {

template <typename TKey, typename TValue>
class TLruCache final {
public:
    explicit TLruCache(size_t capacity = 0);
    ~TLruCache() = default;

    bool insert(const TKey& key, const TValue& value);
    void upsert(const TKey& key, const TValue& value);
    void erase(const TKey& key);

    std::optional<TValue> find(const TKey& key) const;
    std::optional<TValue> updated_find(const TKey& key);


    size_t size() const noexcept;

private:
    using TItem = std::pair<TKey, TValue>;
    using TListIterator = typename std::list<TItem>::iterator;

    const size_t Capacity;
    std::list<TItem> List;
    std::unordered_map<TKey, TListIterator> Map;
};

} // namespace lru

#include "lru_cache.hpp"
