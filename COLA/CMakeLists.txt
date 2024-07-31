cmake_minimum_required(VERSION 3.21)
project(COLA_G4Handler VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

# Find COLA package
find_package(COLA)

# Include CMake module for config file generation
include(CMakePackageConfigHelpers)

# Modules can be installed whenever you please, however grouping them all in COLA directory is neat and
# makes further adjustments to CMAKE_PREFIX_PATH unnecessary. It is also advised to put module files to corresponding
# directories to avoid pollution.
set(CMAKE_INSTALL_PREFIX ${COLA_DIR})
set(COLA_MODULE_NAME G4HandlerModule)

# Add library target
set(srcs
        src/FermiFactory.cpp
        src/FermiConverter.cpp
        src/G4HandlerConverter.cpp
        src/G4HandlerFactory.cpp
)

add_library(G4HandlerModule SHARED ${srcs})

target_include_directories(G4HandlerModule PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/${COLA_MODULE_NAME}>
)

# Set public header
set_target_properties(G4HandlerModule PROPERTIES PUBLIC_HEADER include/G4HandlerModule.hh)

# Link against COLA
target_link_libraries(G4HandlerModule PUBLIC COLA)

# Link G4Handler library implementation
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Handler Handler)
target_link_libraries(G4HandlerModule PRIVATE Handler)

# Configure config files
configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/data/G4HandlerModuleConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/G4HandlerModuleConfig.cmake"
        INSTALL_DESTINATION cmake
        #PATH_VARS, etc.
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/G4HandlerModuleConfigVersion.cmake
        COMPATIBILITY AnyNewerVersion)

# Install library
install(TARGETS G4HandlerModule
        EXPORT G4HandlerModuleExport
        LIBRARY DESTINATION lib/${COLA_MODULE_NAME}
        PUBLIC_HEADER DESTINATION include/${COLA_MODULE_NAME}
        INCLUDES DESTINATION include/${COLA_MODULE_NAME}) # Necessary for proper EXPORT generation

# Install includes
install(DIRECTORY include/
        DESTINATION include/${COLA_MODULE_NAME})

# Install export file and config files
install(EXPORT G4HandlerModuleExport
        DESTINATION cmake)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/G4HandlerModuleConfigVersion.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/G4HandlerModuleConfigVersion.cmake"
        DESTINATION cmake)
