#pragma once


#include <string>
#include <optional>
#include <memory>
#include "singletone.h"

namespace dns {

class TDnsCache final {
public:
    static constexpr size_t DEFAULT_CAPACITY = 1000;

    explicit TDnsCache(size_t max_size = DEFAULT_CAPACITY);
    ~TDnsCache();

    void update(const std::string& host, const std::string& ip);

    std::optional<std::string> resolve(const std::string& host);

    size_t size() const noexcept;

private:
    class TThreadSafeImpl;
    std::unique_ptr<TThreadSafeImpl> Impl;
};

using TUniqueDnsCache = common::TSingleton<TDnsCache>;

} // namespace dns
