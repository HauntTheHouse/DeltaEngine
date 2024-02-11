ENGINE_DIR = _WORKING_DIR .. "/DeltaEngine"
VENDOR_DIR = ENGINE_DIR .. "/Vendor"

ENGINE_PUBLIC_INCLUDES = {
    ENGINE_DIR .. "/Include",
    VENDOR_DIR .. "/spdlog/include",
    VENDOR_DIR .. "/imgui",
}

require "Vendor/Vendor"

project "DeltaEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

	targetdir (BUILD_DIR .. "/bin/" .. CONFIG_NAME .. "/%{prj.name}")
	objdir (BUILD_DIR .. "/obj/" .. CONFIG_NAME .. "/%{prj.name}")

    files {
        "Include/DeltaEngine/**.hpp",
        "Source/DeltaEngine/*.cpp",
        "Source/DeltaEngine/Render/*.cpp",
        "Source/DeltaEngine/Render/OpenGL/*.cpp"
    }
    includedirs {
		"Include",
        VENDOR_DIR .. "/glfw/include",
        VENDOR_DIR .. "/glad/include",
        VENDOR_DIR .. "/spdlog/include",
        VENDOR_DIR .. "/imgui",
        VENDOR_DIR .. "/stb"
    }
    links {
        "glfw",
        "glad",
        "imgui",
    }
    defines {
        "STB_IMAGE_IMPLEMENTATION",
        "USING_OPENGL=1",
    }