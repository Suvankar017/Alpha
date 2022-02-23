project "stb"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir (tdir)
	objdir (odir)

	files {
        "include/stb/stb_image.h",
        "src/stb_image.c"
    }

    includedirs {
        "include"
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
