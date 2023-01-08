cmake_minimum_required(VERSION 3.20)
project(DeltaEngine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(DeltaGraphics)
add_subdirectory(DeltaPhysics)
add_subdirectory(DeltaMath)
add_subdirectory(vendor)
add_subdirectory(Demo)
