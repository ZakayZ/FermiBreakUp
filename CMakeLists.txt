cmake_minimum_required(VERSION 3.16)
project(G4FermiBreakUp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

find_package(Geant4 REQUIRED)

set(Util
    util/G4FermiDataTypes.cc
    util/G4FermiIntegerPartition.cc
    util/G4FermiParticle.cc
    util/G4FermiRandomizer.cc
    util/G4FermiLogger.cc

    util/nuclei_properties/impl/FermiNucleiProperties.cc
    util/nuclei_properties/data_storage/G4FermiCopyMass.cc
    util/nuclei_properties/data_storage/G4FermiDefaultNuclearMass.cc
)

set(PhaseSpace
    phase_decay/G4FermiKopylovDecay.cc
)

set(FragmentPool
    fragment_pool/G4FermiFragmentsStorage.cc
    fragment_pool/data_source/G4FermiDefaultPoolSource.cc
    fragment_pool/fragments/G4FermiFragment.cc
    fragment_pool/fragments/G4FermiStableFragment.cc
    fragment_pool/fragments/G4FermiUnstableFragment.cc
)

set(FermiBreakUpModel
    G4FermiSplitter.cc
    G4FermiBreakUp.cc
)

set(Sources 
    ${FermiBreakUpModel}
    ${FragmentPool}
    ${Util}
    ${PhaseSpace}
)

# default config
FILE(CREATE_LINK ${PROJECT_SOURCE_DIR}/data/small_nuclei_data.csv small_nuclei_data.csv)

add_library(G4FermiBreakUp ${Sources})

target_link_libraries(G4FermiBreakUp ${Geant4_LIBRARIES})

target_include_directories(G4FermiBreakUp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR} ${Geant4_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR} ${Geant4_INCLUDE_DIR}>
)
