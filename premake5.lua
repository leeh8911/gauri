project "gauri"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("${wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("${wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "gauri_pch.h"
    pchsource "src/gauri_pch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
        "include/**.h",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    includedirs
    {
        "src",
        "include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.ImGui}",
    }

    links
    {
        "GLFW",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
        }

        links
        {
            "%{Library.winSock}",
            "%{Library.winMM}",
            "%{Library.WinVersion}",
            "%{Library.BCrypt}"
        }


	filter "configurations:Debug"
		defines "GR_DEBUG"
		runtime "Debug"
		symbols "on"

		links
		{
		}

	filter "configurations:Release"
		defines "GR_RELEASE"
		runtime "Release"
		optimize "on"

		links
		{
		}

	filter "configurations:Dist"
		defines "GR_DIST"
		runtime "Release"
		optimize "on"

		links
		{
		}
