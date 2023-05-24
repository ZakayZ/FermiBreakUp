cmake_minimum_required(VERSION 3.21)
project(FermiBreakUp)

set(CMAKE_CXX_STANDARD 17)

find_package(CLHEP REQUIRED)


set(Utilities
        MyFermiBreakUp/Utilities/DataTypes.cpp
        MyFermiBreakUp/Utilities/IntegerPartition.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/VNucleiProperties.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/FermiNucleiProperties.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/NativeNucleiProperties.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/CSVBuilder.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/DefaultBuilder.cpp
        MyFermiBreakUp/Utilities/ConfigurationProperties.cpp
        MyFermiBreakUp/Utilities/Randomizer.cpp
        )

set(PhaseSpace
        MyFermiBreakUp/PhaseDecay/VDecay.cpp
        MyFermiBreakUp/PhaseDecay/Decay.cpp
        MyFermiBreakUp/PhaseDecay/KopylovDecay.cpp
        )

set(TableValues
        MyFermiBreakUp/TableValues/NucleiPropertiesTable.cpp
        MyFermiBreakUp/TableValues/NucleiPropertiesTableAME12.cpp
        )

set(Fragments
        MyFermiBreakUp/Fragments/FermiFragment.cpp
        MyFermiBreakUp/Fragments/StableFermiFragment.cpp
        MyFermiBreakUp/Fragments/UnstableFermiFragment.cpp
        MyFermiBreakUp/Fragments/B9FermiFragment.cpp
        MyFermiBreakUp/Fragments/Be8FermiFragment.cpp
        MyFermiBreakUp/Fragments/Li5FermiFragment.cpp
        MyFermiBreakUp/Fragments/He5FermiFragment.cpp)

set(FermiBreakUp
        MyFermiBreakUp/VFermiBreakUp.cpp
        MyFermiBreakUp/FermiParticle.cpp
        MyFermiBreakUp/FermiSplit.cpp
        MyFermiBreakUp/FermiFragmentPool.cpp
        MyFermiBreakUp/FermiConfigurations.cpp
        MyFermiBreakUp/CachedFermiConfigurations.cpp
        MyFermiBreakUp/FermiBreakUp.cpp)

set(Handler
        MyFermiBreakUp/VFermiBreakUp.cpp
        MyFermiBreakUp/VFermiConfigurations.cpp
        MyFermiBreakUp/FermiParticle.cpp
        MyFermiBreakUp/FermiSplit.cpp
        MyFermiBreakUp/FermiFragmentPool.cpp
        MyFermiBreakUp/FermiConfigurations.cpp
        MyFermiBreakUp/CachedFermiConfigurations.cpp
        MyFermiBreakUp/FermiBreakUp.cpp)

set(Sources ${FermiBreakUp} ${Fragments} ${Utilities} ${TableValues} ${PhaseSpace})

add_executable(FermiBreakUp main.cpp ${Sources})

target_link_libraries(FermiBreakUp CLHEP::CLHEP)

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