project "DeltaMath"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files {
        "include/**.hpp",
        "include/**.inl",
    }
    includedirs { "include" }
