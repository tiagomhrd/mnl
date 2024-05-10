project "tests"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"
	systemversion "latest"

	targetdir ("bin/" .. outputdir .. "%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "%{prj.name}")

	IncludeDir = {}
	IncludeDir["Catch2"] = "../third_party/Catch2"
	IncludeDir["Monomials"] = "../src"

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",
	}

	includedirs
	{
		"src",
		"%{IncludeDir.Catch2}",
		"%{IncludeDir.Monomials}",
	}

	links {
		"Catch2"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"