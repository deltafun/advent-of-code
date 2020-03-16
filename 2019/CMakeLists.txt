cmake_minimum_required (VERSION 3.13.4)
project (aoc-2019)

set(CMAKE_CXX_STANDARD 20)

add_executable(rocket-equation 01/rocket-equation.cpp)
add_executable(program-alert 02/program-alert.cpp)
add_executable(crossed-wires 03/crossed-wires.cpp)
add_executable(secure-container 04/secure-container.cpp)
add_executable(sunny-with-a-chance 05/sunny-with-a-chance.cpp)
add_executable(orbits 06/orbits.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -Wall -Wno-sign-compare")

