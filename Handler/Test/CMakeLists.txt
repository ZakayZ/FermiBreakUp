cmake_minimum_required(VERSION 3.16)
project(Handler)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

# Handler library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_BINARY_DIR}/Handler)

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

set(Tests
        ConservationTest.cpp
)

add_executable(HandlerTest ${Tests})

target_link_libraries(HandlerTest Handler)
target_link_libraries(HandlerTest GTest::GTest GTest::Main)

gtest_discover_tests(HandlerTest)
