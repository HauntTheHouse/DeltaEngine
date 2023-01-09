cmake_minimum_required(VERSION 3.20)
project(vendor)

add_subdirectory(glfw)

add_library(glad STATIC
    glad/include/glad/glad.h
    glad/include/KHR/khrplatform.h
    glad/src/glad.c
)
target_include_directories(glad PUBLIC "glad/include")

add_subdirectory(spdlog)

add_library(imgui STATIC
    imgui/imgui.h
    imgui/backends/imgui_impl_glfw.h
    imgui/backends/imgui_impl_opengl3.h
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)
target_link_libraries(imgui glfw)
target_include_directories(imgui PUBLIC "imgui")
