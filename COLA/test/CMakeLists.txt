cmake_minimum_required(VERSION 3.22)
project(ColaLibTest)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

# Handler library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_BINARY_DIR}/COLALibrary)

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

set(Tests
        test.cpp
)

add_executable(ColaLibTest ${Tests})

target_link_libraries(ColaLibTest G4HandlerModule)
target_link_libraries(ColaLibTest GTest::GTest GTest::Main)

# default config
FILE(CREATE_LINK ${PROJECT_SOURCE_DIR}/data/config.xml config.xml)

gtest_discover_tests(ColaLibTest)
