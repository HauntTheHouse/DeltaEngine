cmake_minimum_required(VERSION 3.12)
project(RenderFramework)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    include/*.hpp
    src/*.cpp
)

add_subdirectory(vendor)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE
	"include"
	"${CMAKE_SOURCE_DIR}/DeltaPhysics/DeltaMath/include"
	"vendor/glfw/include"
	"vendor/glad/include"
)

target_link_libraries(${PROJECT_NAME} DeltaMath glfw glad)

target_precompile_headers(${PROJECT_NAME} PUBLIC "include/PCH.hpp")
