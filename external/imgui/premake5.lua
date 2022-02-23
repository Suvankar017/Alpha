project "imgui"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir (tdir)
	objdir (odir)

	files {
        "include/imgui/**.h",
        "include/imgui/**.cpp",
        "debuggers/imgui.natvis"
    }

    includedirs {
        "include/imgui/**.h",
        "../GLFW/include"
    }

    filter "system:windows"
        systemversion "latest"
    
    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "on"
        buildoptions "/MTd"

    filter { "configurations:Release" }
        runtime "Release"
        optimize "on"
        buildoptions "/MT"
