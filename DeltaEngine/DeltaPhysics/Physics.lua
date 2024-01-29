project "DeltaPhysics"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files {
        "include/**.hpp",
        "src/*.cpp"
    }
    includedirs { "include" }
