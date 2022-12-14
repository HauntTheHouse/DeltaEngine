cmake_minimum_required(VERSION 3.12)
project(vendor)

add_subdirectory(glfw)

add_library(glad
	glad/include/glad/glad.h
	glad/include/KHR/khrplatform.h
	glad/src/glad.c
)
target_include_directories(glad PRIVATE glad/include)
