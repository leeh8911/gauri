project "gauri"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("${wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("${wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "gauri_pch.h"
    pchsource "src/gauri_pch.cpp"
