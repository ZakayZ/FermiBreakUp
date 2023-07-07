cmake_minimum_required(VERSION 3.21)
project(FermiBreakUp)

set(CMAKE_CXX_STANDARD 17)

find_package(CLHEP REQUIRED)

set(Utilities
        MyFermiBreakUp/Utilities/DataTypes.cpp
        MyFermiBreakUp/Utilities/IntegerPartition.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/VNucleiProperties.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/FermiNucleiProperties.cpp
#        MyFermiBreakUp/Utilities/NucleiProperties/NativeNucleiProperties.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/Builder/CSVBuilder.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/Builder/DefaultBuilder.cpp
        MyFermiBreakUp/Utilities/ConfigurationProperties.cpp
        MyFermiBreakUp/Utilities/Randomizer.cpp)

set(PhaseSpace
        MyFermiBreakUp/PhaseDecay/VDecay.cpp
        MyFermiBreakUp/PhaseDecay/Decay.cpp
        MyFermiBreakUp/PhaseDecay/KopylovDecay.cpp)

set(TableValues
#        MyFermiBreakUp/TableValues/NucleiPropertiesTable.cpp
#        MyFermiBreakUp/TableValues/NucleiPropertiesTableAME12.cpp
        )

set(FragmentPool
        MyFermiBreakUp/FragmentPool/FermiFragmentPool.cpp
        MyFermiBreakUp/FragmentPool/Builder/DefaultBuilder.cpp
        MyFermiBreakUp/FragmentPool/Fragments/FermiFragment.cpp
        MyFermiBreakUp/FragmentPool/Fragments/StableFermiFragment.cpp
        MyFermiBreakUp/FragmentPool/Fragments/UnstableFermiFragment.cpp
        MyFermiBreakUp/FragmentPool/Fragments/B9FermiFragment.cpp
        MyFermiBreakUp/FragmentPool/Fragments/Be8FermiFragment.cpp
        MyFermiBreakUp/FragmentPool/Fragments/Li5FermiFragment.cpp
        MyFermiBreakUp/FragmentPool/Fragments/He5FermiFragment.cpp)

set(FermiBreakUp
        MyFermiBreakUp/VFermiBreakUp.cpp
        MyFermiBreakUp/FermiParticle.cpp
        MyFermiBreakUp/FermiSplit.cpp
        MyFermiBreakUp/FermiConfigurations.cpp
        MyFermiBreakUp/CachedFermiConfigurations.cpp
        MyFermiBreakUp/FermiBreakUp.cpp)

set(Sources ${FermiBreakUp} ${FragmentPool} ${Utilities} ${TableValues} ${PhaseSpace})

add_executable(FermiBreakUp main.cpp ${Sources})

target_link_libraries(FermiBreakUp CLHEP::CLHEP)

target_link_libraries(FermiBreakUp ${Geant4_LIBRARIES})

target_include_directories(FermiBreakUp PUBLIC MyFermiBreakUp)

############################################ Testing

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

set(Tests
        MyFermiBreakUp/Test/PartitionTest.cpp
        MyFermiBreakUp/Test/TableTests.cpp
        MyFermiBreakUp/Test/BreakUpTest.cpp
        MyFermiBreakUp/Test/LRUTest.cpp
        MyFermiBreakUp/Test/CachedBreakUpTest.cpp)

add_executable(CTest ${Tests} ${Sources})

target_link_libraries(CTest CLHEP::CLHEP)
target_link_libraries(CTest GTest::GTest GTest::Main)

target_include_directories(CTest PUBLIC MyFermiBreakUp)

gtest_discover_tests(CTest)