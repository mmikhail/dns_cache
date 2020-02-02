#pragma once

namespace lru {

template <typename TKey, typename TValue>
TLruCache<TKey, TValue>::TLruCache(size_t capacity)
    : Capacity(capacity)
    , Map(capacity)
{}

template <typename TKey, typename TValue>
bool TLruCache<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    auto it = Map.find(key);

    if (it != Map.cend()) {
        return false;
    } else {
        if (!List.empty() && List.size() == Capacity) {
            Map.erase(List.back().first);
            List.pop_back();
        }
        List.emplace_front(key, value);
        Map[key] = List.begin();
    }

    return true;
}

template <typename TKey, typename TValue>
void TLruCache<TKey, TValue>::upsert(const TKey& key, const TValue& value) {
    if (auto it = Map.find(key); it != Map.cend()) {
        List.erase(it->second);
        List.emplace_front(key, value);
        it->second = List.begin();
    } else {
        insert(key, value);
    }
}

template <typename TKey, typename TValue>
void TLruCache<TKey, TValue>::erase(const TKey& key) {
    if (auto it = Map.find(key); it != Map.cend()) {
        List.erase(it->second);
        Map.erase(it);
    }
}

template <typename TKey, typename TValue>
std::optional<TValue> TLruCache<TKey, TValue>::find(const TKey& key) const {
    if (const auto it = Map.find(key); it != Map.cend()) {
        return it->second->second;
    }
    return {};
}

template <typename TKey, typename TValue>
std::optional<TValue> TLruCache<TKey, TValue>::updated_find(const TKey& key) {
    if (auto it = Map.find(key); it != Map.cend()) {
        auto value = it->second->second;
        List.erase(it->second);
        List.emplace_front(key, value);
        return it->second->second;
    }

    return {};
}

template <typename TKey, typename TValue>
size_t TLruCache<TKey, TValue>::size() const noexcept {
    return List.size();
}

} // namespace lru
