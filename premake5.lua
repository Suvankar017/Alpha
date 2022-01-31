workspace "Alpha"
    architecture "x64"
    startproject "AlphaEditor"

    configurations {
        "Debug",
        "Release"
    }

-- Output Directories
tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
odir = "bin-obj/%{cfg.buildcfg}/%{prj.name}"

-- External Dependencies
externals = {}
externals["GLFW"] = "external/GLFW"

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

    -- Files and Libraries Directories
    files {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/include/Alpha",
        "%{externals.GLFW}/include"
    }

    libdirs {
        "%{externals.GLFW}/lib/%{cfg.buildcfg}"
    }

    -- Flags
    flags {
        "FatalWarnings"
    }

    -- Windows Filters
    filter { "system:windows" }
        systemversion "latest"
        defines {
            "ALPHA_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }
        links {
            "GLFW",
            "opengl32"
        }
    
    -- Mac Filters
    filter { "system:macosx" }
        xcodebuildsettings {
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
            ["UseModernBuildSystem"] = "NO"
        }
        defines {
            "ALPHA_PLATFORM_MAC"
        }
        links {
            "GLFW.framework",
            "opengl32.framework"
        }

    -- Linux Filters
    filter { "system:linux" }
        defines {
            "ALPHA_PLATFORM_LINUX"
        }
        links {
            "GLFW",
            "opengl32"
        }

    -- Debug Filters
    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "on"
        defines {
            "ALPHA_DEBUG"
        }

    -- Release Filters
    filter { "configurations:Release" }
        runtime "Release"
        symbols "off"
        optimize "on"
        defines {
            "ALPHA_RELEASE"
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
        "Alpha/include"
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
            "ALPHA_PLATFORM_WINDOWS"
        }

    -- Mac Filters
    filter { "system:macosx" }
        xcodebuildsettings {
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
            ["UseModernBuildSystem"] = "NO"
        }
        defines {
            "ALPHA_PLATFORM_MAC"
        }
        
    -- Linux Filters
    filter { "system:linux" }
        defines {
            "ALPHA_PLATFORM_LINUX"
        }
    
    -- Debug Filters
    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "on"
        defines {
            "ALPHA_DEBUG"
        }

    -- Release Filters
    filter { "configurations:Release" }
        runtime "Release"
        symbols "off"
        optimize "on"
        defines {
            "ALPHA_RELEASE"
        }
