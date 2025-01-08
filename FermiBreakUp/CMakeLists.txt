cmake_minimum_required(VERSION 3.16)
project(FermiBreakUp)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

find_package(CLHEP REQUIRED)

set(Tables
    table_values/NucleiPropertiesTable.cpp
    table_values/NucleiPropertiesTableAME12.cpp
)

set(utilities
    utilities/DataTypes.cpp
    utilities/IntegerPartition.cpp
    utilities/nuclei_properties/VNucleiProperties.cpp
    utilities/nuclei_properties/impl/FermiNucleiProperties.cpp
    utilities/nuclei_properties/impl/FastNucleiProperties.cpp
    utilities/nuclei_properties/impl/NativeNucleiProperties.cpp
    utilities/nuclei_properties/data_storage/CSVNuclearMass.cpp
    utilities/nuclei_properties/data_storage/DefaultNuclearMass.cpp
    utilities/ConfigurationProperties.cpp
    utilities/Randomizer.cpp
)

set(PhaseSpace
    phase_decay/VDecay.cpp
    phase_decay/Decay.cpp
    phase_decay/KopylovDecay.cpp
)

set(fragment_pool
    fragment_pool/FragmentsStorage.cpp
    fragment_pool/data_source/DefaultPoolSource.cpp
    fragment_pool/fragments/Fragment.cpp
    fragment_pool/fragments/StableFragment.cpp
    fragment_pool/fragments/UnstableFragment.cpp
    fragment_pool/fragments/B9Fragment.cpp
    fragment_pool/fragments/Be8Fragment.cpp
    fragment_pool/fragments/Li5Fragment.cpp
    fragment_pool/fragments/He5Fragment.cpp
)

set(Configurations
    configurations/Configurations.cpp
    configurations/CachedConfigurations.cpp
    configurations/FastConfigurations.cpp
)

set(FermiBreakUpModel
    VFermiBreakUp.cpp
    Particle.cpp
    Split.cpp
    FermiBreakUp.cpp
    VConfigurations.cpp
)

set(Sources ${FermiBreakUpModel} ${fragment_pool} ${utilities} ${PhaseSpace} ${Tables} ${Configurations})

# default config
FILE(CREATE_LINK ${PROJECT_SOURCE_DIR}/data/small_nuclei_data.csv small_nuclei_data.csv)

add_library(FermiBreakUp SHARED ${Sources})

target_link_libraries(FermiBreakUp CLHEP::CLHEP)

target_include_directories(FermiBreakUp PUBLIC
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
$<INSTALL_INTERFACE:${PROJECT_SOURCE_DIR}/>)

include(CMakePackageConfigHelpers)
configure_package_config_file( 
    "${PROJECT_SOURCE_DIR}/Config.cmake.in" 
    "${CMAKE_CURRENT_BINARY_DIR}/FermiBreakUpConfig.cmake"
    INSTALL_DESTINATION lib/cmake/FermiBreakUp
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/FermiBreakUpConfigVersion.cmake
    VERSION 1.0.0
    COMPATIBILITY SameMajorVersion
)

install(
    TARGETS FermiBreakUp
    EXPORT FermiBreakUpExport
    LIBRARY DESTINATION lib/FermiBreakUp
    PUBLIC_HEADER DESTINATION include/FermiBreakUp
    INCLUDES DESTINATION include/FermiBreakUp
)

# Install includes
install(
    DIRECTORY ./
    DESTINATION include/FermiBreakUp
    FILES_MATCHING
        PATTERN "*.h"
        PATTERN "build/*" EXCLUDE
)

install(EXPORT FermiBreakUpExport
        DESTINATION lib/cmake/FermiBreakUp
)

### Install Config and ConfigVersion files
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/FermiBreakUpConfig.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/FermiBreakUpConfigVersion.cmake"
    DESTINATION lib/cmake/FermiBreakUp
)
