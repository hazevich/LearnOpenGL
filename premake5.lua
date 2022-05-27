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

        files { "src/LearnOpenGL/**.h", "src/LearnOpenGL/**.cpp", "src/LearnOpenGL/Shaders/**.glsl" }

        links
        {
            "glfw",
            "glad"
        }

        includedirs
        {
            "dependencies/glfw/include",
            "dependencies/glad/include",
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

group "dependencies"
    project "glfw"
        kind "StaticLib"
        language "C"
        targetdir (targetdirPath)
        objdir (objdirPath)
        location "dependencies/glfw"

        files
        {
            "dependencies/glfw/src/internal.h",
            "dependencies/glfw/src/mappings.h",
            "dependencies/glfw/src/context.c",
            "dependencies/glfw/src/init.c",
            "dependencies/glfw/src/input.c",
            "dependencies/glfw/src/monitor.c",
            "dependencies/glfw/src/vulkan.c",
            "dependencies/glfw/src/window.c",
            "dependencies/glfw/include/**.h"
        }

        filter "system:windows"
            defines 
            { 
                "_GLFW_WIN32",
                "_CRT_SECURE_NO_WARNINGS"
            }

            files
            {

                "dependencies/glfw/src/win32_platform.h",
                "dependencies/glfw/src/win32_joystick.h",
                "dependencies/glfw/src/win32_init.c",
                "dependencies/glfw/src/win32_joystick.c",
                "dependencies/glfw/src/win32_monitor.c",
                "dependencies/glfw/src/win32_time.c",
                "dependencies/glfw/src/win32_thread.c",
                "dependencies/glfw/src/win32_window.c",
                "dependencies/glfw/src/wgl_context.h",
                "dependencies/glfw/src/egl_context.h",
                "dependencies/glfw/src/osmesa_context.h",
                "dependencies/glfw/src/wgl_context.c",
                "dependencies/glfw/src/egl_context.c",
                "dependencies/glfw/src/osmesa_context.c"
            }

    project "glad"
        kind "StaticLib"
        language "C"
        targetdir (targetdirPath)
        objdir (objdirPath)
        location "dependencies/glad"

        files 
        {
            "dependencies/glad/**.h",
            "dependencies/glad/**.c"
        }

        includedirs { "dependencies/glad/include" }