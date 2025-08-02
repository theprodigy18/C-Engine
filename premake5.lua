workspace "C-Engine"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release"
	}

	filter "action:gmake"
		toolset "clang"
		location "build/gmake"

	filter {"action:gmake", "configurations:Release"}
		buildoptions { "-static-libgcc", "-static-libstdc++" }
		linkoptions { "-static-libgcc", "-static-libstdc++" }

	filter {"action:vs*", "configurations:Release"}
		staticruntime "on"


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
		"%{prj.name}/include/*.h",
		"%{prj.name}/include/Graphics/*.h",
		"%{prj.name}/include/Platform/*.h",
		"%{prj.name}/src/*.c",
		"%{prj.name}/vendor/**.h"
	}

	includedirs
	{
		"%{prj.name}/include",
		"%{prj.name}/vendor"
	}

	links 
	{
		"user32",
		"opengl32"
	}

	filter "system:windows"
		files 
		{
			"%{prj.name}/include/Graphics/OpenGL/Windows/**.h",
			"%{prj.name}/src/Graphics/OpenGL/Windows/**.c",
			"%{prj.name}/include/Platform/Windows/**.h",
			"%{prj.name}/src/Platform/Windows/**.c"
		}

		defines "PLATFORM_WINDOWS"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "on"

project "EngineDLL"
	location "EngineDLL"
	kind "SharedLib"
	language "C"
	cdialect "C11"

	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir)

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.c"
	}

	includedirs
	{
		"%{prj.name}/include",
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
		"EngineDLL"
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
		"EngineDLL",
		"EngineLib/include"
	}

	links
	{
		"EngineLib",
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