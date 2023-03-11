cmake_minimum_required(VERSION 3.21)
project(FermiBreakUp)

set(CMAKE_CXX_STANDARD 11)

find_package(CLHEP REQUIRED)


set(Utilities
        MyFermiBreakUp/Utilities/DataTypes.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/VNucleiProperties.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/FermiNucleiProperties.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/NativeNucleiProperties.cpp
        MyFermiBreakUp/Utilities/NucleiProperties/FermiPropertiesFileBuilder.cpp
        MyFermiBreakUp/Utilities/ConfigurationProperties.cpp
        MyFermiBreakUp/Utilities/Randomizer.cpp
        MyFermiBreakUp/Utilities/PhaseDecay/VDecay.cpp
        MyFermiBreakUp/Utilities/PhaseDecay/Decay.cpp
        MyFermiBreakUp/Utilities/PhaseDecay/KopylovDecay.cpp
        MyFermiBreakUp/Utilities/TableValues/NucleiPropertiesTable.cpp
        MyFermiBreakUp/Utilities/TableValues/NucleiPropertiesTableAME12.cpp)

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
        MyFermiBreakUp/FermiFragmentPool.cpp
        MyFermiBreakUp/FermiConfigurations.cpp
        MyFermiBreakUp/FermiBreakUp.cpp)

set(Includes ${Sources} ${Fragments} ${Utilities})

add_executable(FermiBreakUp main.cpp ${Includes})

target_link_libraries(FermiBreakUp CLHEP::CLHEP)

target_include_directories(FermiBreakUp PUBLIC MyFermiBreakUp)

target_include_directories(FermiBreakUp PUBLIC MyFermiBreakUp/Utilities)

target_include_directories(FermiBreakUp PUBLIC MyFermiBreakUp/Fragments)

############################################ Testing

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

set(Tests
        MyFermiBreakUp/Test/PartitionTest.cpp
        MyFermiBreakUp/Test/TableTests.cpp)

add_executable(CTest ${Tests} ${Includes})

target_link_libraries(CTest CLHEP::CLHEP)
target_link_libraries(CTest GTest::GTest GTest::Main)

target_include_directories(CTest PUBLIC MyFermiBreakUp)
target_include_directories(CTest PUBLIC MyFermiBreakUp/Utilities)
target_include_directories(CTest PUBLIC MyFermiBreakUp/Fragments)

gtest_discover_tests(CTest)