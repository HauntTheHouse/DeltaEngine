local BUILD_DIR = path.join("build", _ACTION)
if _OPTIONS["cc"] ~= nil then
	BUILD_DIR = BUILD_DIR .. "_" .. _OPTIONS["cc"]
end

workspace "DeltaEngine"
    location(BUILD_DIR)
    startproject "Demo"
    configurations { "Debug", "Release" }
	if os.is64bit() and not os.istarget("windows") then
		platforms "x86_64"
	else
		platforms { "x86", "x86_64" }
	end
    filter "platforms:x86"
        architecture "x86"
    filter "platforms:x86_64"
        architecture "x86_64"
    filter "configurations:Debug*"
        defines {
            "_DEBUG",
        }
        optimize "Debug"
        symbols "On"
    filter "configurations:Release"
		defines {
			"NDEBUG",
		}
		optimize "Full"
        

require "DeltaEngine/Engine"

project "Demo"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    includedirs {
		"Demo/include",
        GRAPHICS_DIR .. "/include",
        MATH_DIR .. "/include",
        VENDOR_DIR .. "/spdlog/include",
        VENDOR_DIR .. "/imgui",
	}
    files {
        "Demo/include/**.hpp",
        "Demo/src/**.cpp"
    }
    links { "DeltaGraphics" }

    local DEMO_ASSET_SRC_DIR = _WORKING_DIR .. "/Demo/assets"
    local DEMO_ASSET_DEST_DIR = _WORKING_DIR .. "/" .. BUILD_DIR .. "/assets"

    postbuildcommands { "{COPYDIR} " .. DEMO_ASSET_SRC_DIR .. " " .. DEMO_ASSET_DEST_DIR }
