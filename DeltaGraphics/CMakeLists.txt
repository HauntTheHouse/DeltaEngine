cmake_minimum_required(VERSION 3.20)
project(DeltaGraphics)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    include/*.hpp
    src/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE
	"include"
	"${CMAKE_SOURCE_DIR}/vendor/glfw/include"
	"${CMAKE_SOURCE_DIR}/vendor/glad/include"
	"${CMAKE_SOURCE_DIR}/vendor/spdlog/include"
	"${CMAKE_SOURCE_DIR}/vendor/imgui"
	"${CMAKE_SOURCE_DIR}/DeltaMath/include"
)

target_link_libraries(${PROJECT_NAME} glfw glad spdlog imgui DeltaMath)

target_precompile_headers(${PROJECT_NAME} PUBLIC "include/EngineCore/PCH.hpp")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_LIST})
