workspace "LearnOpenGL"
    configurations { "Debug", "Release" }
    startproject "LearnOpenGL"
    architecture "x64"

buildDir = "%{wks.location}/bin/%{cfg.buildcfg}"
objDir = "%{wks.location}/obj/%{cfg.buildcfg}"

group "src"
    project "LearnOpenGL"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        targetdir (buildDir)
        objdir (objDir)
        location "src/LearnOpenGL"

        files { "src/LearnOpenGL/**.h", "src/LearnOpenGL/**.cpp" }

        includedirs
        {
            "src/LearnOpenGL"
        }

        filter "configurations:Debug"
            defines { "DEBUG" }
            runtime "Debug"
            symbols "On"
        
        filter "configurations:Release"
            defines { "RELEASE" }
            runtime "Release"
            optimize "On"