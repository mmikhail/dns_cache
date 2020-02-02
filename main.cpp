#include <iostream>
#include "cache/dns_cache.h"

int main()
{
    dns::TUniqueDnsCache::Instance().update("host", "ip");
    std::cout << dns::TUniqueDnsCache::Instance().resolve("host").value_or("nothing") << std::endl;
    return 0;
}
