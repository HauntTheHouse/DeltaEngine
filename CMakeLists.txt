cmake_minimum_required(VERSION 3.20)
project(Delta)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /Zc:__cplusplus")

add_subdirectory(DeltaGraphics)
add_subdirectory(DeltaPhysics)
add_subdirectory(DeltaMath)
add_subdirectory(vendor)
add_subdirectory(Demo)
