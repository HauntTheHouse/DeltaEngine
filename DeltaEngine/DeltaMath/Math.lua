project "DeltaMath"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files {
        "include/DeltaMath/**.hpp",
        "include/DeltaMat/**.inl",
    }
    includedirs { "include" }
