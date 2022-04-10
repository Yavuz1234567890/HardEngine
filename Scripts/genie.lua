function UseConfigurations()
	configuration "Debug"
		defines { "NDEBUG", "HA_DEBUG" }
		flags { "Symbols", "ReleaseRuntime" }

	configuration "RelWithDebInfo"
		defines { "NDEBUG" }
		flags { "Symbols", "Optimize" }

	configuration "linux"
		defines { "_GLIBCXX_USE_CXX11_ABI=0" }
		links { "pthread" }

	configuration {}
end

function UseOpenGL()
	configuration { "windows" }
		links { "opengl32" }
	configuration { "not windows" }
		links { "GL" }
	configuration {}
end

solution "HardEngine"
	location ".."
	configuration { "linux" }
		buildoptions 
		{
			"-m64",
			"-fPIC",
			"-no-canonical-prefixes",
			"-Wa,--noexecstack",
			"-fstack-protector",
			"-ffunction-sections",
			"-Wunused-value",
			"-Wundef",
			"-msse2",
			"-Wno-multichar",
			"-Wno-undef",
		}
	configuration {}
	flags 
	{ 
		"Cpp17",
		"UseObjectResponseFile",
		"UseLDResponseFile",
		"LinkSupportCircularDependencies",
		"FatalWarnings", 
		"NoPCH", 
		"NoExceptions", 
		"NoRTTI", 
		"NoEditAndContinue"
	}
	includedirs { "../Source" }
	configurations { "Debug", "RelWithDebInfo" }
	platforms { "x64" }
	language "C++"
	startproject "Editor"
	targetdir "../Output"
	objdir "../Object"
	
	configuration { "not windows" }
		removefiles { "../Source/**/Windows/**" }

	configuration { "not linux" }
		removefiles { "../Source/**/Linux/**" }

	configuration { }

	project "Core"
		location "../Source/Core"
		kind "StaticLib"
		files 
		{
			"../Source/Core/**.cpp",
			"../Source/Core/**.h"
		}
		UseConfigurations()
		UseOpenGL()
	
	project "Editor"
		location "../Source/Editor"
		kind "ConsoleApp"
		files 
		{
			"../Source/Editor/**.cpp",
			"../Source/Editor/**.h"
		}
		links { "Core" }
		UseConfigurations()
		UseOpenGL()
	