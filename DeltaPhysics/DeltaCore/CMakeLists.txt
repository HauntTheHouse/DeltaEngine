cmake_minimum_required(VERSION 3.20)
project(DeltaCore)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    include/*.hpp
    src/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

include_directories(${PROJECT_NAME} PRIVATE "include")
