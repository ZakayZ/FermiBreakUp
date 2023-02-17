cmake_minimum_required(VERSION 3.21)
project(FermiBreakUp)

set(CMAKE_CXX_STANDARD 11)

find_package(CLHEP REQUIRED)

set(Sources
        MyFermiBreakUp/IntegerPartition.cpp
        MyFermiBreakUp/Fragments/FermiFragment.cpp
        MyFermiBreakUp/Fragments/StableFermiFragment.cpp
        MyFermiBreakUp/Fragments/UnstableFermiFragment.cpp)

add_executable(FermiBreakUp main.cpp ${Sources})

target_link_libraries(FermiBreakUp CLHEP::CLHEP)

target_include_directories(FermiBreakUp PUBLIC MyFermiBreakUp/Utilities)

target_include_directories(FermiBreakUp PUBLIC MyFermiBreakUp/Fragments)