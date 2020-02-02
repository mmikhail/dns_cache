cmake_minimum_required(VERSION 3.5)

project(dns_cache_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} dns_cache pthread)

add_subdirectory(cache)

enable_testing()
add_subdirectory(tests)