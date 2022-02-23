workspace "Alpha"
    architecture "x64"
    startproject "AlphaEditor"

    configurations {
        "Debug",
        "Release"
    }

    flags {
        "MultiProcessorCompile"
    }

-- Output Directories
tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
odir = "bin-obj/%{cfg.buildcfg}/%{prj.name}"

-- External Dependencies
externals = {}
externals["GLFW"] = "external/GLFW"
externals["glad"] = "external/glad"
externals["spdlog"] = "external/spdlog"
externals["imgui"] = "external/imgui"
externals["glm"] = "external/glm"
externals["stb"] = "external/stb"

-- Include External Premake5.lua Files
include "external/GLFW"
include "external/glad"
include "external/imgui"
include "external/stb"

-- Engine Project
project "Alpha"
    location "Alpha"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    -- Build Directories
    targetdir (tdir)
    objdir (odir)

    pchheader "pch.h"
    pchsource "%{prj.name}/src/pch.cpp"

    -- Files and Libraries Directories
    files {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/include",
        "%{externals.GLFW}/include",
        "%{externals.glad}/include",
        "%{externals.spdlog}/include",
        "%{externals.imgui}/include",
        "%{externals.glm}/include",
        "%{externals.stb}/include"
    }

    -- Flags
    flags {
        "FatalWarnings"
    }

    filter { "system:*", "configurations:*" }
        defines {
            "AP_ENGINE"
        }

    -- Windows Filters
    filter { "system:windows" }
        systemversion "latest"
        defines {
            "AP_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }
        links {
            "glad",
            "GLFW",
            "opengl32",
            "imgui",
            "stb"
        }
    
    -- Mac Filters
    filter { "system:macosx" }
        xcodebuildsettings {
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
            ["UseModernBuildSystem"] = "NO"
        }
        defines {
            "AP_PLATFORM_MAC"
        }
        links {
            "glad.framework",
            "GLFW.framework",
            "opengl32.framework",
            "imgui.framework",
            "stb.framework"
        }

    -- Linux Filters
    filter { "system:linux" }
        defines {
            "AP_PLATFORM_LINUX"
        }
        links {
            "glad",
            "GLFW",
            "opengl32",
            "imgui",
            "stb"
        }

    -- Debug Filters
    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "on"
        buildoptions "/MTd"
        defines {
            "AP_DEBUG"
        }

    -- Release Filters
    filter { "configurations:Release" }
        runtime "Release"
        symbols "off"
        optimize "on"
        buildoptions "/MT"
        defines {
            "AP_RELEASE"
        }

-- Editor Project
project "AlphaEditor"
    location "AlphaEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    -- Build Directories
    targetdir (tdir)
    objdir (odir)

    -- Files and Libraries Directories
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Alpha/include",
        "%{externals.spdlog}/include",
        "%{externals.imgui}/include",
        "%{externals.glm}/include",
        "%{externals.stb}/include"
    }

    links {
        "Alpha"
    }

    -- Flags
    flags {
        "FatalWarnings"
    }

    -- Windows Filters
    filter { "system:windows" }
        systemversion "latest"
        defines {
            "AP_PLATFORM_WINDOWS"
        }

    -- Mac Filters
    filter { "system:macosx" }
        xcodebuildsettings {
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
            ["UseModernBuildSystem"] = "NO"
        }
        defines {
            "AP_PLATFORM_MAC"
        }
        
    -- Linux Filters
    filter { "system:linux" }
        defines {
            "AP_PLATFORM_LINUX"
        }
    
    -- Debug Filters
    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "on"
        buildoptions "/MTd"
        defines {
            "AP_DEBUG"
        }

    -- Release Filters
    filter { "configurations:Release" }
        runtime "Release"
        symbols "off"
        optimize "on"
        buildoptions "/MT"
        defines {
            "AP_RELEASE"
        }
