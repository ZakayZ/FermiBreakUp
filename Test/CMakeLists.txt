cmake_minimum_required(VERSION 3.16)
project(Handler)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

set(LibPath ${CMAKE_CURRENT_SOURCE_DIR}/..)

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

set(Handler
        ${LibPath}/Handler/ExcitationHandler.cpp
        ${LibPath}/Handler/AAMCCFermiBreakUp.cpp
)

set(Tests
        ConservationTest.cpp
)

add_executable(HandlerTest ${Tests} ${Handler})

add_subdirectory(${LibPath}/MyFermiBreakUp ${CMAKE_CURRENT_BINARY_DIR}/MyFermiBreakUp)

target_link_libraries(HandlerTest FermiBreakUp)
target_link_libraries(HandlerTest ${Geant4_LIBRARIES})
target_link_libraries(HandlerTest GTest::GTest GTest::Main)

target_include_directories(HandlerTest PUBLIC ${LibPath})

gtest_discover_tests(HandlerTest)
