project "DeltaGraphics"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files {
      "include/EngineCore/**.hpp",
      "src/EngineCore/*.cpp",
      "src/EngineCore/Rendering/*.cpp",
      "src/EngineCore/Rendering/OpenGL/*.cpp"
    }
    includedirs {
		  "include",
      MATH_DIR .. "/include",
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
      "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
    }
