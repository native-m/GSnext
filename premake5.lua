workspace "GSnext"
	location "build"
	configurations { "Debug", "Release" }

	project "GSnext"
		kind "StaticLib"
		language "C++"
		targetdir "bin/%{cfg.buildcfg}/lib"
		includedirs {
			"3rdparty/spdlog/include",
			"3rdparty/Vulkan-Headers/include",
			"include/",
		}

		files { 
			"src/**.h",
			"include/gsnext/**.h",
			"src/**.cpp"
		}

		configuration "Debug"
			symbols "On"
			defines { "_DEBUG" }
			targetname "%{prj.name}-d"
	
		configuration "Release"
			defines { "NDEBUG" }

	project "GSnextPCSX2"
		kind "SharedLib"
		language "C++"
		targetdir "bin/%{cfg.buildcfg}/plugins"
		
		includedirs {
			"3rdparty/spdlog/include",
			"3rdparty/pcsx2/include",
			"include/",
		}

		files {
			"plugin/**.h",
			"plugin/**.cpp"
		}

		links { "GSnext" }

		if string.find(_ACTION, "vs") then
			linkoptions { "/DEF:\"..\\plugin\\GS.def\"" }
		end

		defines { "_CRT_SECURE_NO_WARNINGS" }

		configuration "Debug"
			symbols "On"
			defines { "_DEBUG" }
			targetname "%{prj.name}-d"
	
		configuration "Release"
			defines { "NDEBUG" }

	project "GSnextTest"
		kind "ConsoleApp"
		language "C++"
		targetdir "bin/%{cfg.buildcfg}/plugins"

		includedirs {
			"3rdparty/spdlog/include",
			"3rdparty/pcsx2/include",
			"include/",
			"plugin/"
		}

		files {
			"test/**.h",
			"test/**.cpp"
		}

		links { "GSnextPCSX2" }

		configuration "Debug"
			symbols "On"
			defines { "_DEBUG" }
			targetname "%{prj.name}-d"
	
		configuration "Release"
			defines { "NDEBUG" }
