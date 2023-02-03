cmake_minimum_required(VERSION 3.20)
project(DeltaMath)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    "include/*.hpp"
)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE "include/")
target_sources(${PROJECT_NAME} INTERFACE ${SRC_LIST})
