workspace "C-Engine"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "EngineLib"
	location "EngineLib"
	kind "StaticLib"
	language "C"
	cdialect "C11"

	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir)

	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.c"

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.c"
	}

	includedirs
	{
		"%{prj.name}/include"
	}

	filter "system:windows"
		defines "PLATFORM_WINDOWS"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "on"
		staticruntime "on"

	filter "configurations:Dist"
		defines "DIST"
		optimize "on"
		staticruntime "on"

project "EngineDLL"
	location "EngineDLL"
	kind "SharedLib"
	language "C"
	cdialect "C11"

	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir)

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.c"
	}

	includedirs
	{
		"EngineLib/include"
	}

	defines
	{
		"ENGINE_DLL_EXPORTS"
	}

	links
	{
		"EngineLib"
	}

	filter "system:windows"
		defines "PLATFORM_WINDOWS"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "on"
		staticruntime "on"

	filter "configurations:Dist"
		defines "DIST"
		optimize "on"
		staticruntime "on"

project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C"
	cdialect "C11"

	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir)

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.c"
	}

	includedirs
	{
		"EngineDLL/include"
	}

	links
	{
		"EngineDLL"
	}

	filter "system:windows"
		defines "PLATFORM_WINDOWS"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "on"
		staticruntime "on"

	filter "configurations:Dist"
		defines "DIST"
		optimize "on"
		staticruntime "on"

project "Test"
	location "Test"
	kind "ConsoleApp"
	language "C"
	cdialect "C11"

	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir)

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.c"
	}

	includedirs
	{
		"EngineDLL/include",
		"EngineLib/include"
	}

	links
	{
		"EngineLib"
	}

	filter "system:windows"
		defines "PLATFORM_WINDOWS"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "on"
		staticruntime "on"

	filter "configurations:Dist"
		defines "DIST"
		optimize "on"
		staticruntime "on"