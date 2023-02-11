cmake_minimum_required(VERSION 3.20)
project(vendor)

add_subdirectory(glfw)
add_subdirectory(spdlog)

add_library(glad STATIC
    "glad/include/glad/glad.h"
    "glad/include/KHR/khrplatform.h"
    "glad/src/glad.c"
)
target_include_directories(glad PUBLIC "glad/include")

set(IMGUI_SRCS
    "imgui/imgui.h"
    "imgui/backends/imgui_impl_glfw.h"
    "imgui/imgui.cpp"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_tables.cpp"
    "imgui/imgui_widgets.cpp"
    "imgui/backends/imgui_impl_glfw.cpp")
set(IMGUI_PRIVATE_INCLUDES_LIST)
set(IMGUI_LIBS_LIST glfw)

if(USE_VULKAN)
    list(APPEND IMGUI_SRCS "imgui/backends/imgui_impl_vulkan.h")
    list(APPEND IMGUI_SRCS "imgui/backends/imgui_impl_vulkan.cpp")

    find_package(Vulkan REQUIRED)
    list(APPEND IMGUI_PRIVATE_INCLUDES_LIST ${Vulkan_INCLUDE_DIRS})
    list(APPEND IMGUI_LIBS_LIST ${Vulkan_LIBRARIES})
elseif(USE_OPENGL)
    list(APPEND IMGUI_SRCS "imgui/backends/imgui_impl_opengl3.h")
    list(APPEND IMGUI_SRCS "imgui/backends/imgui_impl_opengl3.cpp")
endif()

add_library(imgui STATIC ${IMGUI_SRCS})
target_link_libraries(imgui ${IMGUI_LIBS_LIST})
target_include_directories(imgui PUBLIC "imgui")
target_include_directories(imgui PRIVATE ${IMGUI_PRIVATE_INCLUDES_LIST})

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE "stb/")
target_sources(stb_image INTERFACE "stb/stb_image.h")

include(cmrc/CMakeRC.cmake)
