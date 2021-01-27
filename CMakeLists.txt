cmake_minimum_required(VERSION 3.1.8)
project(Taida VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_FLAGS "-pedantic")
set(CMAKE_C_STARDAND 99)

# if (POLICY CMP0054)
#	cmake_policy(SET CMP0054 NEW)
# endif ()

# if (POLICY CMP0077)
#	cmake_policy(SET CMP0077 NEW)
# endif ()

option(BUILD_SHARED_LIBS "Build Taida as a Dynamic Library" OFF)
option(BUILD_DEMOS "Build Demo Folder" ON)
option(TAIDA_BUILD_WINDOW "Build Window Module" ON)
option(TAIDA_BUILD_GRAPHICS "Build Graphics Module" ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory("ext/lua")
add_subdirectory("ext/glad")

if (BUILD_SHARED_LIBS)
	message(STATUS "Building GLFW Shared Library")
	set(BUILD_SHARED_LIBS ON)
else ()
	message(STATUS "Building GLFW Static Library")	
endif ()
add_subdirectory("ext/glfw")

add_subdirectory("src/Taida")

if (BUILD_DEMOS)
	add_subdirectory("demos/open_window")
	add_subdirectory("demos/draw_rectangle")
endif ()
