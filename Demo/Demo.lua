project "Demo"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir (BUILD_DIR .. "/bin/" .. CONFIG_NAME .. "/%{prj.name}")
	objdir (BUILD_DIR .. "/obj/" .. CONFIG_NAME .. "/%{prj.name}")

    includedirs {
		"include",
        ENGINE_DIR .. "/Include",
        VENDOR_DIR .. "/imgui",
	}
    files {
        "include/**.hpp",
        "src/**.cpp",
        "assets/**",
    }
    links { "DeltaEngine" }
