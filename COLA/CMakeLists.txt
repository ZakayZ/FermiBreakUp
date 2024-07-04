cmake_minimum_required(VERSION 3.21)
project(COLA_Fermi VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# Find COLA package
find_package(COLAlib)

# Include CMake module for config file generation
include(CMakePackageConfigHelpers)

# Modules can be installed whenever you please, however grouping them all in COLA directory is neat and
# makes further adjustments to CMAKE_PREFIX_PATH unnecessary. It is also advised to put module files to corresponding
# directories to avoid pollution.
set(CMAKE_INSTALL_PREFIX ${COLA_DIR})
set(COLA_MODULE_NAME FermiBreakUpModule)

# Add library target
set(srcs src/FermiFactory.cpp src/FermiFilter.cpp)
add_library(FermiBreakUpModule SHARED ${srcs})

target_include_directories(FermiBreakUpModule PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/${COLA_MODULE_NAME}>
)

# Set public header
set_target_properties(FermiBreakUpModule PROPERTIES PUBLIC_HEADER include/FermiBreakUpModule.hh)

# Link against COLA
target_link_libraries(FermiBreakUpModule PUBLIC COLAlib)

# Link Fermi Break Up library implementation
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../FermiBreakUp FermiBreakUP)
target_link_libraries(FermiBreakUpModule PRIVATE FermiBreakUp)

# Configure config files
configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/data/FermiModuleConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/FermiModuleConfig.cmake"
        INSTALL_DESTINATION cmake
        #PATH_VARS, etc.
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/FermiModuleConfigVersion.cmake
        COMPATIBILITY AnyNewerVersion)

# Install library
install(TARGETS FermiBreakUpModule
        EXPORT FermiBreakUpModuleExport
        LIBRARY DESTINATION lib/${COLA_MODULE_NAME}
        PUBLIC_HEADER DESTINATION include/${COLA_MODULE_NAME}
        INCLUDES DESTINATION include/${COLA_MODULE_NAME}) # Necessary for proper EXPORT generation

# Install includes
install(DIRECTORY include/
        DESTINATION include/${COLA_MODULE_NAME})

# Install export file and config files
install(EXPORT FermiBreakUpModuleExport
        DESTINATION cmake)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/FermiModuleConfigVersion.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/ExModuleConfigVersion.cmake"
        DESTINATION cmake)
