project "glfw"
    kind "StaticLib"
    language "C"

    targetdir (BUILD_DIR .. "/bin/" .. CONFIG_NAME .. "/%{prj.name}")
	objdir (BUILD_DIR .. "/obj/" .. CONFIG_NAME .. "/%{prj.name}")

    files {
        "glfw/include/GLFW/*.h",
        "glfw/src/context.c",
        "glfw/src/egl_context.*",
        "glfw/src/init.c",
        "glfw/src/input.c",
        "glfw/src/internal.h",
        "glfw/src/monitor.c",
        "glfw/src/null*.*",
        "glfw/src/osmesa_context.*",
        "glfw/src/platform.c",
        "glfw/src/vulkan.c",
        "glfw/src/window.c",
    }
    includedirs {
        "glfw/include"
    }
    filter "system:windows"
        defines "_GLFW_WIN32"
        files {
            "glfw/src/win32_*.*",
            "glfw/src/wgl_context.*"
        }
    filter "system:linux"
        defines "_GLFW_X11"
        files {
            "glfw/src/glx_context.*",
            "glfw/src/linux*.*",
            "glfw/src/posix*.*",
            "glfw/src/x11*.*",
            "glfw/src/xkb*.*"
        }
    filter "system:macosx"
        defines "_GLFW_COCOA"
        files {
            "glfw/src/cocoa_*.*",
            "glfw/src/posix_thread.h",
            "glfw/src/nsgl_context.h",
            "glfw/src/egl_context.h",
            "glfw/src/osmesa_context.h",

            "glfw/src/posix_thread.c",
            "glfw/src/nsgl_context.m",
            "glfw/src/egl_context.c",
            "glfw/src/nsgl_context.m",
            "glfw/src/osmesa_context.c",
        }

    filter "action:vs*"
        defines "_CRT_SECURE_NO_WARNINGS"


project "spdlog"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir (BUILD_DIR .. "/bin/" .. CONFIG_NAME .. "/%{prj.name}")
	objdir (BUILD_DIR .. "/obj/" .. CONFIG_NAME .. "/%{prj.name}")

    includedirs {
        "spdlog/include"
    }

    filter "action:vs*"
        buildoptions { "/Zc:__cplusplus" }
        defines {
            "_CRT_SECURE_NO_WARNINGS",
        }


project "glad"
    kind "StaticLib"
    language "C"

    targetdir (BUILD_DIR .. "/bin/" .. CONFIG_NAME .. "/%{prj.name}")
	objdir (BUILD_DIR .. "/obj/" .. CONFIG_NAME .. "/%{prj.name}")

    files {
        "glad/include/glad/glad.h",
        "glad/include/KHR/khrplatform.h",
        "glad/src/glad.c",
    }
    includedirs { "glad/include" }

project "imgui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++11"

    targetdir (BUILD_DIR .. "/bin/" .. CONFIG_NAME .. "/%{prj.name}")
	objdir (BUILD_DIR .. "/obj/" .. CONFIG_NAME .. "/%{prj.name}")

    files {
        "imgui/imgui.h",
        "imgui/backends/imgui_impl_glfw.h",
        "imgui/imgui.cpp",
        "imgui/imgui_demo.cpp",
        "imgui/imgui_draw.cpp",
        "imgui/imgui_tables.cpp",
        "imgui/imgui_widgets.cpp",
        "imgui/backends/imgui_impl_glfw.cpp",
        "imgui/backends/imgui_impl_opengl3.h",
        "imgui/backends/imgui_impl_opengl3.cpp",
    }
    includedirs {
        "imgui",
        "glfw/include"
    }
    links { "glfw" }

project "stb_image"
    kind "StaticLib"
    language "C"

    targetdir (BUILD_DIR .. "/bin/" .. CONFIG_NAME .. "/%{prj.name}")
	objdir (BUILD_DIR .. "/obj/" .. CONFIG_NAME .. "/%{prj.name}")

    files "stb/stb_image.h"
    includedirs "stb"
