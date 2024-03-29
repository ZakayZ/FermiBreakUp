cmake_minimum_required(VERSION 3.16)
project(Handler)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

set(Handler
        Handler/ExcitationHandler.cpp
        Handler/AAMCCFermiBreakUp.cpp
)

add_executable(Handler main.cpp ${Handler})

add_subdirectory(MyFermiBreakUp)
target_link_libraries(Handler PUBLIC FermiBreakUp ${Geant4_LIBRARIES})

############################################ Testing

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

set(Tests
        Test/ConservationTest.cpp)

add_executable(HandlerTest ${Tests} ${Handler})

target_link_libraries(HandlerTest FermiBreakUp)
target_link_libraries(HandlerTest ${Geant4_LIBRARIES})
target_link_libraries(HandlerTest GTest::GTest GTest::Main)

target_include_directories(HandlerTest PUBLIC ${PROJECT_SOURCE_DIR})

gtest_discover_tests(HandlerTest)
