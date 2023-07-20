cmake_minimum_required(VERSION 3.21)
project(Handler)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

set(Handler
        Handler/ExcitationHandler.cpp
        Handler/AAMCCFermiBreakUp.cpp
#        Handler/AamccFermiBreakUpFunc.cpp
        )

add_executable(Handler main.cpp ${Handler})

add_subdirectory(MyFermiBreakUp)
target_link_libraries(Handler PUBLIC FermiBreakUp ${Geant4_LIBRARIES})
