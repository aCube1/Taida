set(LINK_LIBRARIES 
	lua
	glad
	glfw
	GL
	X11
	pthread
	Xrandr
	Xi
	dl)

add_subdirectory("System")

if (TAIDA_BUILD_WINDOW OR TAIDA_BUILD_GRAPHICS)
	add_subdirectory("Window")
endif ()

if (TAIDA_BUILD_GRAPHICS)
	add_subdirectory("Graphics")
endif ()
