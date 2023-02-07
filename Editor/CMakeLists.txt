cmake_minimum_required(VERSION 3.20)
project(Editor)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    "include/*.hpp"
    "src/*.cpp"
    "assets/shaders/*"
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets")

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} DeltaGraphics DeltaPhysics DeltaMath)
target_include_directories(${PROJECT_NAME} PRIVATE "include")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${INCLUDE_LIST} ${SRC_LIST})
