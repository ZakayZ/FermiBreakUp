cmake_minimum_required(VERSION 3.16)
project(FermiBreakUp)

string(REPLACE "-O2" "-O0" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
string(REPLACE "-O2" "-O0" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

find_package(CLHEP REQUIRED)

set(Tables
    table_values/NucleiPropertiesTable.cpp
    table_values/NucleiPropertiesTableAME12.cpp
)

set(util
    util/DataTypes.cpp
    util/IntegerPartition.cpp
    util/nuclei_properties/VNucleiProperties.cpp
    util/nuclei_properties/impl/FermiNucleiProperties.cpp
    util/nuclei_properties/impl/FastNucleiProperties.cpp
    util/nuclei_properties/impl/NativeNucleiProperties.cpp
    util/nuclei_properties/data_storage/CSVNuclearMass.cpp
    util/nuclei_properties/data_storage/DefaultNuclearMass.cpp
    util/Particle.cpp
    util/Randomizer.cpp
    util/Logger.cpp
)

set(PhaseSpace
    phase_decay/Helper.cpp
    phase_decay/Decay.cpp
    phase_decay/KopylovDecay.cpp
)

set(fragment_pool
    fragment_pool/FragmentsStorage.cpp
    fragment_pool/data_source/DefaultPoolSource.cpp
    fragment_pool/fragments/Fragment.cpp
    fragment_pool/fragments/StableFragment.cpp
    fragment_pool/fragments/UnstableFragment.cpp
)

set(FermiBreakUpModel
    Split.cpp
    FermiBreakUp.cpp
)

set(Sources ${FermiBreakUpModel} ${fragment_pool} ${util} ${PhaseSpace} ${Tables})

# default config
FILE(CREATE_LINK ${PROJECT_SOURCE_DIR}/data/small_nuclei_data.csv small_nuclei_data.csv)

add_library(FermiBreakUp ${Sources})

target_link_libraries(FermiBreakUp CLHEP::CLHEP)

target_include_directories(FermiBreakUp PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${PROJECT_SOURCE_DIR}/>
)

# include(CMakePackageConfigHelpers)
# configure_package_config_file( 
#     "${PROJECT_SOURCE_DIR}/Config.cmake.in" 
#     "${CMAKE_CURRENT_BINARY_DIR}/FermiBreakUpConfig.cmake"
#     INSTALL_DESTINATION lib/cmake/FermiBreakUp
# )

# write_basic_package_version_file(
#     ${CMAKE_CURRENT_BINARY_DIR}/FermiBreakUpConfigVersion.cmake
#     VERSION 1.0.0
#     COMPATIBILITY SameMajorVersion
# )

# install(
#     TARGETS FermiBreakUp
#     EXPORT FermiBreakUpExport
#     LIBRARY DESTINATION lib/FermiBreakUp
#     PUBLIC_HEADER DESTINATION include/FermiBreakUp
#     INCLUDES DESTINATION include/FermiBreakUp
# )

# # Install includes
# install(
#     DIRECTORY ./
#     DESTINATION include/FermiBreakUp
#     FILES_MATCHING
#         PATTERN "*.h"
#         PATTERN "build/*" EXCLUDE
# )

# install(EXPORT FermiBreakUpExport
#         DESTINATION lib/cmake/FermiBreakUp
# )

# ### Install Config and ConfigVersion files
# install(
#     FILES "${CMAKE_CURRENT_BINARY_DIR}/FermiBreakUpConfig.cmake"
#           "${CMAKE_CURRENT_BINARY_DIR}/FermiBreakUpConfigVersion.cmake"
#     DESTINATION lib/cmake/FermiBreakUp
# )
