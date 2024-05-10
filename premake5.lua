workspace "mnl"
	configurations {"Debug", "Release", "Distribute"}
	platforms{"x64"}
	startproject "tests"
	filter { "platforms:x64" }
	architecture "x86_64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


include "third_party/Catch2"
include "tests"

project "mnl"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"

	targetdir ("bin/" .. outputdir .. "%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",
	}

	includedirs
	{
		"src",
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines {
			"MON_DEBUG"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines {
			"MON_RELEASE"
		}

	filter "configurations:Distribute"
		runtime "Release"
		optimize "on"
		defines {
			"MON_DISTRIBUTE"
		}
	