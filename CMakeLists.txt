cmake_minimum_required(VERSION 3.12)
project(DeltaPhysicsHub VERSION 0.0.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /Zc:__cplusplus")

add_subdirectory(DeltaPhysics)
add_subdirectory(Example)
