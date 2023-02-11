cmake_minimum_required(VERSION 3.20)
project(DeltaGraphics)

file(GLOB_RECURSE INCLUDE_LIST CONFIGURE_DEPENDS
    "include/*.hpp"
)

file(GLOB SRC_LIST CONFIGURE_DEPENDS
    "src/EngineCore/*.cpp"
    "src/EngineCore/Modules/*.cpp"
)

cmrc_add_resource_library(ShaderResources
        NAMESPACE shaders
        shaders/object.vert
        shaders/object.frag)

set(LIBS_LIST glfw spdlog imgui stb_image DeltaMath ShaderResources)
set(PRIVATE_INCLUDES_LIST)
set(DEFINITIONS_LIST)

option(USE_OPENGL "Using OpenGL as rendering system" ON)
option(USE_VULKAN "Using Vulkan as rendering system" OFF)

if(USE_VULKAN)
    message("Using Vulkan as rendering system")
    find_package(Vulkan REQUIRED)
    file(GLOB VULKAN_LIST CONFIGURE_DEPENDS
        "src/EngineCore/Rendering/Vulkan/*.cpp"
    )
    list(APPEND SRC_LIST ${VULKAN_LIST})
    list(APPEND LIBS_LIST ${Vulkan_LIBRARIES})
    list(APPEND PRIVATE_INCLUDES_LIST ${Vulkan_INCLUDE_DIRS})
    list(APPEND DEFINITIONS_LIST "-DUSING_VULKAN")
elseif(USE_OPENGL)
    message("Using OpenGL as rendering system")
    file(GLOB OPENGL_LIST CONFIGURE_DEPENDS
        "src/EngineCore/Rendering/OpenGL/*.cpp"
        "shaders/*.vert"
        "shaders/*.frag"
    )
    list(APPEND SRC_LIST ${OPENGL_LIST})
    list(APPEND LIBS_LIST glad)
    list(APPEND DEFINITIONS_LIST "-DUSING_OPENGL")
else()
    message(FATAL_ERROR "No rendering system are chosen")
endif()

add_library(${PROJECT_NAME} STATIC ${INCLUDE_LIST} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${LIBS_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_include_directories(${PROJECT_NAME} PRIVATE ${PRIVATE_INCLUDES_LIST})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${DEFINITIONS_LIST})

target_precompile_headers(${PROJECT_NAME} PUBLIC "include/EngineCore/PCH.hpp")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${INCLUDE_LIST} ${SRC_LIST})
