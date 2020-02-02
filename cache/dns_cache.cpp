#include "dns_cache.h"
#include "lru_cache.h"

#include <mutex>
#include <shared_mutex>

namespace dns {

class TDnsCache::TThreadSafeImpl final {
public:
    explicit TThreadSafeImpl(size_t max_size = 0)
        : Cache(max_size)
    {}

    ~TThreadSafeImpl() = default;

    void update(const std::string& host, const std::string& ip) {
        std::unique_lock l(Mutex);
        Cache.upsert(host, ip);
    }

    std::optional<std::string> resolve(const std::string& host) {
        std::unique_lock l(Mutex);
        if (const auto& value = Cache.updated_find(host); value.has_value()) {
            return value.value();
        }
        return {};
    }

    size_t size() const noexcept {
        std::shared_lock l(Mutex);
        return Cache.size();
    }

private:
    lru::TLruCache<std::string, std::string> Cache;
    mutable std::shared_mutex Mutex;
};


TDnsCache::TDnsCache(size_t max_size)
    : Impl(std::make_unique<TThreadSafeImpl>(max_size))
{}

TDnsCache::~TDnsCache()
{}

void TDnsCache::update(const std::string& host, const std::string& ip) {
    Impl->update(host, ip);
}

std::optional<std::string> TDnsCache::resolve(const std::string& host) {
    return Impl->resolve(host);
}

size_t TDnsCache::size() const noexcept {
    return Impl->size();
}

}
