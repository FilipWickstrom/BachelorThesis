project "Game"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    targetdir("build/bin/" .. outputdir)
    objdir("build/bin-int/" .. outputdir)
	openmp "On"

	
	-- Define the location of pre-compiled header.
    pchheader "PCH.h"
		pchsource "src/PCH.cpp"

    -- Define the location(s) of files.
    files {
        "src/**.h",
		"src/**.cpp"
    }


    -- Define any includes of folder(s).
    -- Useful to remove any "../folder/file.h" in code.
    includedirs {
        "src",
        "../Engine/src",
        "../ThirdParty/SFML/include/"
    }
	libdirs {
		"../ThirdParty/SFML/lib/"
	}
	links { 
			"opengl32.lib", 
			"freetype.lib", 
			"winmm.lib", 
			"gdi32.lib", 
			"openal32.lib", 
			"flac.lib", 
			"vorbisenc.lib", 
			"vorbisfile.lib", 
			"vorbis.lib", 
			"ogg.lib", 
			"ws2_32.lib" 
	}

    vpaths {
		["Singletons"]		= { "**SFMLTon.*" },
		["ECS"] 			= {"**Components.*"},
		["Game"]			= {"**Game.*"},
		["REAL ECS"]		= {"**ECS.*"},
		["Objects"]			= {"**GameObject.*", "**PlayerObject.*", "**FoodObject.*", "**EnemyObject.*"}
    }

    filter {"system:windows"}
        defines {
			"GAME_PLATFORM_WINDOWS",
			"NOMINMAX" 
			--"WIN32",
			--"_CRT_SECURE_NO_WARNINGS",
			--"SFML_STATIC"
        }

    filter {"configurations:Debug"}
        kind "ConsoleApp"
        staticruntime "on"
        runtime "Debug"
        defines{"_DEBUG", "_UNICODE", "UNICODE"}
        symbols "on"
		links { 
				"sfml-audio-d.lib", 
				"sfml-graphics-d.lib", 
				"sfml-network-d.lib", 
				"sfml-system-d.lib", 
				"sfml-window-d.lib" 
		}
		--Windows specific for now
        postbuildcommands {
			{ "copy ..\\ThirdParty\\SFML\\bin\\openal32.dll 			build\\bin\\" .. outputdir .. "\\openal32.dll" 			},
			{ "copy ..\\ThirdParty\\SFML\\bin\\sfml-audio-d-2.dll 		build\\bin\\" .. outputdir .. "\\sfml-audio-d-2.dll" 	},
			{ "copy ..\\ThirdParty\\SFML\\bin\\sfml-graphics-d-2.dll 	build\\bin\\" .. outputdir .. "\\sfml-graphics-d-2.dll" },
			{ "copy ..\\ThirdParty\\SFML\\bin\\sfml-network-d-2.dll 	build\\bin\\" .. outputdir .. "\\sfml-network-d-2.dll" 	},
			{ "copy ..\\ThirdParty\\SFML\\bin\\sfml-system-d-2.dll 		build\\bin\\" .. outputdir .. "\\sfml-system-d-2.dll" 	},
			{ "copy ..\\ThirdParty\\SFML\\bin\\sfml-window-d-2.dll 		build\\bin\\" .. outputdir .. "\\sfml-window-d-2.dll" 	}
        }

    filter {"configurations:Release"}
        kind "ConsoleApp"
        staticruntime "on"
        runtime "Release"
        defines{"NDEBUG", "_UNICODE", "UNICODE"}
        optimize "on"
		links { 
				"sfml-audio.lib", 
				"sfml-graphics.lib", 
				"sfml-network.lib", 
				"sfml-system.lib", 
				"sfml-window.lib" 
		}
		--Windows specific for now
        postbuildcommands {
			{ "copy ..\\ThirdParty\\SFML\\bin\\openal32.dll 			build\\bin\\" .. outputdir .. "\\openal32.dll" 			},
			{ "copy ..\\ThirdParty\\SFML\\bin\\sfml-audio-2.dll 		build\\bin\\" .. outputdir .. "\\sfml-audio-2.dll" 		},
			{ "copy ..\\ThirdParty\\SFML\\bin\\sfml-graphics-2.dll 		build\\bin\\" .. outputdir .. "\\sfml-graphics-2.dll" 	},
			{ "copy ..\\ThirdParty\\SFML\\bin\\sfml-network-2.dll 		build\\bin\\" .. outputdir .. "\\sfml-network-2.dll" 	},
			{ "copy ..\\ThirdParty\\SFML\\bin\\sfml-system-2.dll 		build\\bin\\" .. outputdir .. "\\sfml-system-2.dll" 	},
			{ "copy ..\\ThirdParty\\SFML\\bin\\sfml-window-2.dll 		build\\bin\\" .. outputdir .. "\\sfml-window-2.dll" 	}
        }