cmake_minimum_required(VERSION 3.20)
project(DeltaPhysicsHub)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /Zc:__cplusplus")

add_subdirectory(DeltaPhysics)
add_subdirectory(Example)
