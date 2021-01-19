project(taida VERSION 0.0.1 LANGUAGES C)

file(GLOB SRCS "src/*.c" "src/utils/*.c")

add_library(${PROJECT_NAME} STATIC ${SRCS})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory("ext/lua")
add_subdirectory("ext/glad")
add_subdirectory("ext/glfw")

target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_link_libraries(${PROJECT_NAME} lua glad glfw GL X11 pthread Xrandr Xi dl)
