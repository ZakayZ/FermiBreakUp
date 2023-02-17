cmake_minimum_required(VERSION 3.21)
project(FermiBreakUp)

set(CMAKE_CXX_STANDARD 17)

set(Sources MyFermiBreakUp/IntegerPartition.cpp)

add_executable(FermiBreakUp main.cpp ${Sources})
