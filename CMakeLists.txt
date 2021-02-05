cmake_minimum_required(VERSION 3.1.8)
project(Taida VERSION 0.0.1 LANGUAGES C)

set(${PROJECT_NAME} CMAKE_C_FLAGS "-pedantic")
set(${PROJECT_NAME} CMAKE_C_STARDAND 99)

if (POLICY CMP0054)
	cmake_policy(SET CMP0054 NEW)
endif ()

if (POLICY CMP0077)
	cmake_policy(SET CMP0077 NEW)
endif ()

file(GLOB SRCS "src/Taida/*.c" "src/Taida/utils/*.c")

option(BUILD_SHARED_LIBS "Build Taida as a Dynamic Library" OFF)
option(BUILD_DEMOS "Build Demo Folder" ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory("ext/lua")
add_subdirectory("ext/glad")
add_subdirectory("ext/glfw")

set(BUILD_TESTING OFF)

set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
if (BUILD_SHARED_LIBS)
	# Building openal-soft Static Library
	set(LIBTYPE "STATIC")
endif ()
add_subdirectory("ext/openal-soft")

set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(BUILD_PROGRAMS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ENABLE_EXTERNAL_LIBS ON)
set(ENABLE_STATIC_RUNTIME ON)
add_subdirectory("ext/libsndfile")

if (SHARED_LIBS)
	message(STATUS "Building Taida Dynamic Library")
	add_library(${PROJECT_NAME} SHARED ${SRCS})
else ()
	message(STATUS "Building Taida Static Library")
	add_library(${PROJECT_NAME} STATIC ${SRCS})
endif ()

if (BUILD_DEMOS)
	add_subdirectory("demos/open_window")
	add_subdirectory("demos/audio_player")
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC "include")

# Todo: Setup MSVC better
if (MSVC)
	target_link_libraries(${PROJECT_NAME}
		lua
		glad
		glfw
		sndfile
		OpenAL
	)
else ()
	target_link_libraries(${PROJECT_NAME}
		lua
		glad
		glfw
		sndfile
		OpenAL
		GL
		X11
		pthread
		Xrandr
		Xi
		dl
	)
endif ()
