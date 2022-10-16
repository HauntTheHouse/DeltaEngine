cmake_minimum_required(VERSION 3.12)
project(DeltaPhysics VERSION 0.0.1)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    src/*.hpp
    src/*.cpp
)

message(${SRC_LIST})

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

include_directories(${PROJECT_NAME} PRIVATE src)
