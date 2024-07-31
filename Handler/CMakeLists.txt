cmake_minimum_required(VERSION 3.16)
project(Handler)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

set(Sources
        ExcitationHandler.cpp
        AAMCCFermiBreakUp.cpp
)

find_package(Geant4 REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../FermiBreakUp ${CMAKE_BINARY_DIR}/FermiBreakUp)

add_library(Handler STATIC ${Sources})

target_link_libraries(Handler PUBLIC FermiBreakUp ${Geant4_LIBRARIES})
target_include_directories(Handler PUBLIC ${PROJECT_SOURCE_DIR})
set_target_properties(Handler PROPERTIES POSITION_INDEPENDENT_CODE True)
