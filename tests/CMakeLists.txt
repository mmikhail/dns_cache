cmake_minimum_required(VERSION 3.10)
project(cache_test)

add_subdirectory("${PROJECT_SOURCE_DIR}/../extern/googletest" "extern/googletest")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/cache)

add_executable(${PROJECT_NAME}
    lru_cache_test.cpp
)

target_link_libraries(${PROJECT_NAME} lru_cache gtest gtest_main)