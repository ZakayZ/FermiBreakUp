cmake_minimum_required(VERSION 3.16)
project(FermiBreakUpTest)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

set(LibPath ${CMAKE_CURRENT_SOURCE_DIR}/..)
add_subdirectory(${LibPath} ${CMAKE_BINARY_DIR}/G4FermiBreakUp)

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

set(Tests
    G4FermiSplitTest.cc
    G4FermiPartitionTest.cc
    G4FermiBreakUpTest.cc
)

add_executable(FermiTest ${Tests})

target_link_libraries(FermiTest G4FermiBreakUp)
target_link_libraries(FermiTest GTest::GTest GTest::Main)

target_include_directories(FermiTest PUBLIC ${LibPath})

gtest_discover_tests(FermiTest)
