cmake_minimum_required(VERSION 3.16)
project(FermiBreakUp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(CLHEP REQUIRED)

set(UTIL
    util/DataTypes.cpp
    util/IntegerPartition.cpp
    util/Particle.cpp
    util/Randomizer.cpp
    util/Logger.cpp

    util/nuclei_properties/impl/FermiNucleiProperties.cpp

    util/nuclei_properties/data_storage/CSVNuclearMass.cpp
    util/nuclei_properties/data_storage/DefaultNuclearMass.cpp
)

set(PHASE_SPACE
    phase_decay/KopylovDecay.cpp
)

set(FRAGMENT_POOL
    fragment_pool/FragmentsStorage.cpp
    fragment_pool/data_source/DefaultPoolSource.cpp
    fragment_pool/fragments/Fragment.cpp
    fragment_pool/fragments/StableFragment.cpp
    fragment_pool/fragments/UnstableFragment.cpp
)

set(FERMI_BREAK_UP_MODEL
    Splitter.cpp
    FermiBreakUp.cpp
)

set(SOURCES ${FERMI_BREAK_UP_MODEL} ${FRAGMENT_POOL} ${UTIL} ${PHASE_SPACE})

# default config
FILE(CREATE_LINK ${PROJECT_SOURCE_DIR}/data/small_nuclei_data.csv small_nuclei_data.csv)

add_library(FermiBreakUp ${SOURCES})

target_link_libraries(FermiBreakUp CLHEP::CLHEP)

target_include_directories(FermiBreakUp PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${PROJECT_SOURCE_DIR}/>
)

target_compile_options(FermiBreakUp PRIVATE -Wall -Wextra -Wpedantic -Werror)
set_property(TARGET FermiBreakUp PROPERTY CXX_STANDARD 17)
set_property(TARGET FermiBreakUp PROPERTY CXX_STANDARD_REQUIRED On)

target_include_directories(FermiBreakUp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    $<INSTALL_INTERFACE:>
)

# Install the library and headers
install(TARGETS FermiBreakUp
    EXPORT FermiBreakUpTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(
    DIRECTORY ./
    DESTINATION include
    FILES_MATCHING
        PATTERN "*.h"
        PATTERN "build/*" EXCLUDE
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
install(EXPORT FermiBreakUpTargets
    FILE FermiBreakUpTargets.cmake
    # NAMESPACE fbu::
    DESTINATION lib/cmake/FermiBreakUp
)
