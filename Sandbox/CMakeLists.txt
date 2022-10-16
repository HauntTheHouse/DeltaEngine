cmake_minimum_required(VERSION 3.12)
project(Sandbox VERSION 0.0.1)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    include/*.hpp
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/DeltaPhysics/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} DeltaPhysics)
