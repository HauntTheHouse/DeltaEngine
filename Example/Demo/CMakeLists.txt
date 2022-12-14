cmake_minimum_required(VERSION 3.12)
project(Demo)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    include/*.hpp
    src/*.cpp
)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_include_directories(${PROJECT_NAME} PRIVATE "../RenderFramework/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/DeltaPhysics/DeltaMath/include")

target_link_libraries(${PROJECT_NAME} RenderFramework DeltaMath)















