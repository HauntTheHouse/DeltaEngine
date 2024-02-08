BUILD_DIR = _WORKING_DIR .. "/build_" .. _ACTION
if _OPTIONS["cc"] ~= nil then
	BUILD_DIR = BUILD_DIR .. "_" .. _OPTIONS["cc"]
end

CONFIG_NAME = "%{cfg.buildcfg}_%{cfg.architecture}"

workspace "DeltaEngine"
    targetdir (BUILD_DIR)
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
require "Demo/Demo"
