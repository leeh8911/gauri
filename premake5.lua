project "gauri"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"
    externalwarnings "Off"
    -- warnings "Extra"
    -- buildoptions { "/WX" }

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    defines
    {
        "FMT_HEADER_ONLY",
        "_CRT_SECURE_NO_WARNINGS",
    }

    pchheader "grpch.h"
    pchsource "src/grpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
        "include/**.h",
        "3rdparty/stb_image/**.h",
        "3rdparty/stb_image/**.cpp",
		"3rdparty/glm/glm/**.hpp",
		"3rdparty/glm/glm/**.inl",
    }
    removefiles {"src/test/**.cpp", "src/test/**.h"}

    includedirs
    {
        "src",
        "include",
    }
    externalincludedirs 
    {
        "%{wks.location}/gauri/3rdparty/spdlog/include",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
    }

    links
    {
        "GLFW",
        "Glad",
        "imgui",
        "Dwmapi.lib", 
        "opengl32.lib",
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
        "GLFW_INCLUDE_NONE",
        }

        links
        {
            "%{Library.WinSock}",
            "%{Library.WinMM}",
            "%{Library.WinVersion}",
            "%{Library.BCrypt}"
        }


	filter "configurations:Debug"
		defines {"GR_DEBUG", "GR_ENABLE_ASSERTS"}
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


project "gauri-test"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"
    externalwarnings "Off"
    warnings "Default"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "test_grpch.h"
    pchsource "test/test_grpch.cpp"

    files
    {
        "test/**.cpp",
    }

    includedirs
    {
        "test",
        "include",
    }
    externalincludedirs 
    {
        "%{wks.location}/gauri/3rdparty/spdlog/include",
        "%{IncludeDir.gtest}",
    }

    links
    {
        "gtest"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
        }

        links
        {
            "%{Library.WinSock}",
            "%{Library.WinMM}",
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
