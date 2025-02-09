cmake_minimum_required(VERSION 3.16)
project(FermiBreakUp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(CLHEP REQUIRED)

set(UTIL
    FermiBreakUp/util/DataTypes.cpp
    FermiBreakUp/util/IntegerPartition.cpp
    FermiBreakUp/util/Particle.cpp
    FermiBreakUp/util/Randomizer.cpp
    FermiBreakUp/util/Logger.cpp
)

set(NUCLEI_PROPERTIES
    FermiBreakUp/nuclei_properties/impl/FermiNucleiProperties.cpp
    FermiBreakUp/nuclei_properties/data_storage/CSVNuclearMass.cpp
    FermiBreakUp/nuclei_properties/data_storage/DefaultNuclearMass.cpp
)

set(PHASE_SPACE
    FermiBreakUp/phase_decay/KopylovPhaseDecay.cpp
)

set(FRAGMENT_POOL
    FermiBreakUp/fragment_pool/FragmentsStorage.cpp
    FermiBreakUp/fragment_pool/data_source/DefaultPoolSource.cpp
    FermiBreakUp/fragment_pool/fragments/Fragment.cpp
    FermiBreakUp/fragment_pool/fragments/StableFragment.cpp
    FermiBreakUp/fragment_pool/fragments/UnstableFragment.cpp
)

set(FERMI_BREAK_UP_MODEL
    FermiBreakUp/Splitter.cpp
    FermiBreakUp/FermiBreakUp.cpp
)

set(SOURCES
    ${FERMI_BREAK_UP_MODEL}
    ${FRAGMENT_POOL}
    ${UTIL}
    ${PHASE_SPACE}
    ${NUCLEI_PROPERTIES}
)

add_library(FermiBreakUp ${SOURCES})

target_link_libraries(FermiBreakUp PUBLIC CLHEP::CLHEP)

target_compile_options(FermiBreakUp PRIVATE -Wall -Wextra -Wpedantic -Werror)
set_property(TARGET FermiBreakUp PROPERTY CXX_STANDARD 17)
set_property(TARGET FermiBreakUp PROPERTY CXX_STANDARD_REQUIRED On)

target_include_directories(FermiBreakUp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:>
)

# Install the library and headers
install(TARGETS FermiBreakUp
    EXPORT FermiBreakUpExport
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(
    DIRECTORY FermiBreakUp
    DESTINATION include
    FILES_MATCHING
        PATTERN "*.h"
)

# Generate and install the package configuration file
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/FermiBreakUpConfig.cmake
    INSTALL_DESTINATION lib/cmake/FermiBreakUp
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/FermiBreakUpConfigVersion.cmake
    VERSION ${FermiBreakUp_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/FermiBreakUpConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/FermiBreakUpConfigVersion.cmake
    DESTINATION lib/cmake/FermiBreakUp
)

# Export the targets
install(EXPORT FermiBreakUpExport
    FILE FermiBreakUpExport.cmake
    DESTINATION lib/cmake/FermiBreakUp
)
