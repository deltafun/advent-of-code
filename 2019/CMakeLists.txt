cmake_minimum_required (VERSION 3.13.4)
project (aoc-2019)

add_executable(rocket-equation 01/rocket-equation.cpp)
add_executable(program-alert 02/program-alert.cpp)
add_executable(crossed-wires 03/crossed-wires.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-sign-compare")
