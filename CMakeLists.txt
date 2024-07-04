cmake_minimum_required(VERSION 3.16)
project(Runner)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

add_executable(Runner main.cpp)

add_subdirectory(Handler)

target_link_libraries(Runner PUBLIC Handler)
