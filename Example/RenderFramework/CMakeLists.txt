cmake_minimum_required(VERSION 3.12)
project(RenderFramework)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    include/*.hpp
    src/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/DeltaPhysics/DeltaMath/include")

target_link_libraries(${PROJECT_NAME} DeltaMath)
