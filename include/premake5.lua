project "mnl"
	location "../build"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"

	targetdir ("build/bin/" .. outputdir .. "%{prj.name}")
	objdir ("build/bin-int/" .. outputdir .. "%{prj.name}")

	files
	{
		"**.h",
		"**.hpp",
		"**.cpp",
	}

	includedirs
	{
		"include",
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
