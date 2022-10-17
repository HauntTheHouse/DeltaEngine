cmake_minimum_required(VERSION 3.12)
project(DeltaPhysics VERSION 0.0.1)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    src/*.hpp
    src/*.cpp
)


add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
include_directories(${PROJECT_NAME} PRIVATE src)
