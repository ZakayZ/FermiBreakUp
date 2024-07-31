cmake_minimum_required(VERSION 3.16)
project(FermiBreakUp)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

find_package(CLHEP REQUIRED)

set(Tables
        TableValues/NucleiPropertiesTable.cpp
        TableValues/NucleiPropertiesTableAME12.cpp
)

set(Utilities
        Utilities/DataTypes.cpp
        Utilities/IntegerPartition.cpp
        Utilities/NucleiProperties/VNucleiProperties.cpp
        Utilities/NucleiProperties/Impl/FermiNucleiProperties.cpp
        Utilities/NucleiProperties/Impl/FastNucleiProperties.cpp
        Utilities/NucleiProperties/Impl/NativeNucleiProperties.cpp
        Utilities/NucleiProperties/DataStorage/CSVNuclearMass.cpp
        Utilities/NucleiProperties/DataStorage/DefaultNuclearMass.cpp
        Utilities/ConfigurationProperties.cpp
        Utilities/Randomizer.cpp
)

set(PhaseSpace
        PhaseDecay/VDecay.cpp
        PhaseDecay/Decay.cpp
        PhaseDecay/KopylovDecay.cpp
)

set(FragmentPool
        FragmentPool/FragmentsStorage.cpp
        FragmentPool/DataSource/DefaultPoolSource.cpp
        FragmentPool/Fragments/Fragment.cpp
        FragmentPool/Fragments/StableFragment.cpp
        FragmentPool/Fragments/UnstableFragment.cpp
        FragmentPool/Fragments/B9Fragment.cpp
        FragmentPool/Fragments/Be8Fragment.cpp
        FragmentPool/Fragments/Li5Fragment.cpp
        FragmentPool/Fragments/He5Fragment.cpp
)

set(Configurations
        Configurations/Configurations.cpp
        Configurations/CachedConfigurations.cpp
        Configurations/FastConfigurations.cpp
)

set(FermiBreakUpModel
        VFermiBreakUp.cpp
        Particle.cpp
        Split.cpp
        FermiBreakUp.cpp
        VConfigurations.cpp
)

set(Sources ${FermiBreakUpModel} ${FragmentPool} ${Utilities} ${PhaseSpace} ${Tables} ${Configurations})

# default config
FILE(CREATE_LINK ${PROJECT_SOURCE_DIR}/Data/small_nuclei_data.csv small_nuclei_data.csv)

add_library(FermiBreakUp STATIC ${Sources})

target_link_libraries(FermiBreakUp CLHEP::CLHEP)

target_include_directories(FermiBreakUp PUBLIC ${PROJECT_SOURCE_DIR})

set_target_properties(FermiBreakUp PROPERTIES POSITION_INDEPENDENT_CODE True)
