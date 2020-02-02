cmake_minimum_required(VERSION 3.5)

add_library(dns_cache STATIC dns_cache.cpp)
add_library(lru_cache STATIC lru_cache.cpp)

target_link_libraries(lru_cache pthread)
target_link_libraries(dns_cache lru_cache pthread)