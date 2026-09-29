cmake_minimum_required(VERSION 3.15)
project(SmartHVACSimulator CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(hvac_sim
    src/main.cpp
    src/SensorReader.cpp
)
