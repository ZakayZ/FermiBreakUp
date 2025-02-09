cmake_minimum_required(VERSION 3.16)
project(Runner)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

set(LibPath ${CMAKE_CURRENT_SOURCE_DIR}/..)
add_subdirectory(${LibPath} ${CMAKE_BINARY_DIR}/FermiBreakUp)

add_executable(Runner main.cpp)

target_link_libraries(Runner PRIVATE FermiBreakUp)
