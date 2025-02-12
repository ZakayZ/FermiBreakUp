cmake_minimum_required(VERSION 3.16)
project(G4FermiBreakUp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

find_package(Geant4 REQUIRED)

set(Util
    src/G4FermiDataTypes.cc
    src/G4FermiIntegerPartition.cc
    src/G4FermiParticle.cc
    src/G4FermiRandomizer.cc
    src/G4FermiLogger.cc

    src/G4FermiFastNucleiProperties.cc
    src/G4FermiCopyMass.cc
    src/G4FermiDefaultNuclearMass.cc
)

set(PhaseSpace
    src/G4FermiKopylovDecay.cc
)

set(FragmentPool
    src/G4FermiFragmentsStorage.cc
    src/G4FermiDefaultPoolSource.cc
    src/G4FermiVFragment.cc
    src/G4FermiStableFragment.cc
    src/G4FermiUnstableFragment.cc
)

set(FermiBreakUpModel
    src/G4FermiSplitter.cc
    src/G4FermiBreakUpAN.cc
)

set(Sources 
    ${FermiBreakUpModel}
    ${FragmentPool}
    ${Util}
    ${PhaseSpace}
)

add_library(G4FermiBreakUp ${Sources})

target_link_libraries(G4FermiBreakUp ${Geant4_LIBRARIES})

target_include_directories(G4FermiBreakUp PUBLIC
    $<BUILD_INTERFACE:include ${Geant4_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include ${Geant4_INCLUDE_DIR}>
)
