cmake_minimum_required(VERSION 3.10)
project(drone_simulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(drone_simulator
    src/main.cpp
    src/drone.cpp
)