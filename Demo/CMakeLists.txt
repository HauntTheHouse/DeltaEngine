cmake_minimum_required(VERSION 3.20)
project(Demo)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    include/*.hpp
    src/*.cpp
)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} DeltaGraphics DeltaPhysics DeltaMath)
target_include_directories(${PROJECT_NAME} PRIVATE "include")
