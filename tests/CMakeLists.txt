cmake_minimum_required(VERSION 3.16)
project(FermiBreakUpTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

set(LibPath ${CMAKE_CURRENT_SOURCE_DIR}/..)
add_subdirectory(${LibPath} ${CMAKE_BINARY_DIR}/FermiBreakUp)

# default config
FILE(CREATE_LINK ${PROJECT_SOURCE_DIR}/data/small_nuclei_data.csv ${CMAKE_BINARY_DIR}/small_nuclei_data.csv)

enable_testing()

find_package(GTest QUIET)

if (NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
    )
    FetchContent_MakeAvailable(googletest)
endif()

include(GoogleTest)

set(Tests
    SplitTest.cpp
    PartitionTest.cpp
    TableTests.cpp
    BreakUpTest.cpp
)

add_executable(FermiTest ${Tests})

target_link_libraries(FermiTest FermiBreakUp)
if (TARGET GTest::GTest)
    target_link_libraries(FermiTest GTest::GTest GTest::Main)
elseif (TARGET gtest)
    target_link_libraries(FermiTest gtest gtest_main)
endif()

gtest_discover_tests(FermiTest)
