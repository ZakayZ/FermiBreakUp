cmake_minimum_required(VERSION 3.21)
project(FermiBreakUp)

set(CMAKE_CXX_STANDARD 11)

find_package(CLHEP REQUIRED)


set(Utilities
        MyFermiBreakUp/Utilities/NucleiProperties.cpp
        MyFermiBreakUp/Utilities/ConfigurationProperties.cpp)

set(Fragments
        MyFermiBreakUp/Fragments/FermiFragment.cpp
        MyFermiBreakUp/Fragments/StableFermiFragment.cpp
        MyFermiBreakUp/Fragments/UnstableFermiFragment.cpp
        MyFermiBreakUp/Fragments/B9FermiFragment.cpp
        MyFermiBreakUp/Fragments/Be8FermiFragment.cpp
        MyFermiBreakUp/Fragments/Li5FermiFragment.cpp
        MyFermiBreakUp/Fragments/He5FermiFragment.cpp)

set(Sources
        MyFermiBreakUp/IntegerPartition.cpp
        MyFermiBreakUp/FermiParticle.cpp
        MyFermiBreakUp/FermiSplit.cpp
        MyFermiBreakUp/FermiFragmentPool.cpp)

add_executable(FermiBreakUp main.cpp ${Sources} ${Fragments} ${Utilities})

target_link_libraries(FermiBreakUp CLHEP::CLHEP)

target_include_directories(FermiBreakUp PUBLIC MyFermiBreakUp)

target_include_directories(FermiBreakUp PUBLIC MyFermiBreakUp/Utilities)

target_include_directories(FermiBreakUp PUBLIC MyFermiBreakUp/Fragments)