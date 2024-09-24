newoption {
	trigger = "to",
	value   = "path",
	description = "Set the output location for the generated files"
}

if (_ACTION == nil) then
	return
end

local locationDir = _OPTIONS["to"] or path.join("solution", _ACTION, "stratagus")

local nugetPackages = {
	"sdl2.nuget:2.28.0", "sdl2.nuget.redist:2.28.0",
	"sdl2_image.nuget:2.6.3", "sdl2_image.nuget.redist:2.6.3",
	"sdl2_mixer.nuget:2.6.3", "sdl2_mixer.nuget.redist:2.6.3",
	"sdl2_net.nuget:2.2.0", "sdl2_net.nuget.redist:2.2.0",
	"sdl2_ttf.nuget:2.20.2", "sdl2_ttf.nuget.redist:2.20.2"
}

function useGuisan()
	includedirs { "include/" }
	links { "guisan" }
end

-- ----------------------------------------------------------------------------
workspace "Guisan"
	location(locationDir)
	configurations {"Debug", "Release"}

	language "C++"
	cppdialect "C++14"

	objdir(path.join(locationDir, "obj")) -- premake adds $(configName)/$(AppName)
	targetdir(path.join(locationDir, "bin/%{cfg.buildcfg}"))

	startproject "guisan"

	externalwarnings "Off"

	warnings "Extra"
	--flags { "FatalWarnings"}

	filter { "action:vs*" }
		nuget(nugetPackages)
		defines { "_CRT_SECURE_NO_WARNINGS" } -- 4996: '$func': This function or variable may be unsafe. Consider using $func2 instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

	filter { "toolset:msc*" }
		buildoptions { "/Zc:__cplusplus" } -- else __cplusplus would be 199711L
		-- buildoptions {"/Za"} -- Disable language extensions
		-- Error from <winnt.h>
			--"2133", -- '%array_var': unknown size
			--"2467", -- illegal declaration of anonymous struct
		disablewarnings {
			"4018", -- '<': signed/unsigned mismatch
			"4100", -- '%var': unreferenced formal parameter
			"4127", -- conditional expression is constant
			"4189", -- '%var': local variable is initialized but not referenced
			"4244", -- '=': conversion from '$type1' to '$type2', possible loss of data
			"4458", -- declaration of '$var' hides class member
		}
	filter { "configurations:Debug" }
		symbols "On"
		defines { "DEBUG" }
		optimize "Off"

	filter { "configurations:Release" }
		symbols "Off"
		defines { "NDEBUG" }
		optimize "On"

	filter "system:windows"
		defines { "NOMINMAX", "WIN32", "USE_WIN32" }

-- ----------------------------------------------------------------------------
project "guisan"
	kind "StaticLib"
	targetname "guisan"

	files { "src/**.cpp", "include/**.hpp" }
	files { "src/SConscript" }
	files { "*.*"}

	includedirs { "include" }

-- ----------------------------------------------------------------------------
group "examples"
-- ----------------------------------------------------------------------------
project "opengl_helloworld"
	kind "WindowedApp"
	targetname "opengl_helloworld"

	files { "examples/openglhelloworld.cpp", "examples/opengl_helper.hpp", "examples/helloworld_example.hpp" }

	includedirs { "include" }
	links { "guisan" }
	links {"opengl32"}

	debugdir "examples"

-- ----------------------------------------------------------------------------
project "opengl_widgets"
	kind "WindowedApp"
	targetname "opengl_widgets"

	files { "examples/openglwidgets.cpp", "examples/opengl_helper.hpp", "examples/widgets_example.hpp" }

	includedirs { "include" }
	links { "guisan" }
	links {"opengl32"}

	debugdir "examples"

-- ----------------------------------------------------------------------------
project "sdl_action"
	kind "WindowedApp"
	targetname "sdl_action"

	files { "examples/sdlaction.cpp", "examples/sdl_helper.hpp", "examples/action_example.hpp" }

	includedirs { "include" }
	links { "guisan" }

	debugdir "examples"

-- ----------------------------------------------------------------------------
project "sdl_hello"
	kind "WindowedApp"
	targetname "sdl_hello"

	files { "examples/sdlhelloworld.cpp", "examples/sdl_helper.hpp", "examples/helloworld_example.hpp" }

	includedirs { "include" }
	links { "guisan" }

	debugdir "examples"

-- ----------------------------------------------------------------------------
project "sdl_rickroll"
	kind "WindowedApp"
	targetname "sdl_rickroll"

	files { "examples/sdlrickroll.cpp", "examples/sdl_helper.hpp", "examples/rickroll_example.hpp" }

	includedirs { "include" }
	links { "guisan" }

	debugdir "examples"

-- ----------------------------------------------------------------------------
project "sdl_widgets"
	kind "WindowedApp"
	targetname "sdl_widgets"

	files { "examples/sdlwidgets.cpp", "examples/sdl_helper.hpp", "examples/widgets_example.hpp" }

	includedirs { "include" }
	links { "guisan" }

	debugdir "examples"

-- ----------------------------------------------------------------------------
project "sdl2_widgets"
	kind "WindowedApp"
	targetname "sdl2_widgets"

	files { "examples/sdl2widgets.cpp", "examples/sdl2_helper.hpp", "examples/widgets_example.hpp" }

	includedirs { "include" }
	links { "guisan" }

	debugdir "examples"

-- ----------------------------------------------------------------------------
group "Demo"
-- ----------------------------------------------------------------------------
project "Demo_ff"
	kind "WindowedApp"
	targetname "Demo"

	files { "Demo/ff/**.*" }
	includedirs { "Demo/ff/include" }

	includedirs { "include" }
	links { "guisan" }

	links {"opengl32"}

	debugdir "Demo/ff"
