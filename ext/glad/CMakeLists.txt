project(glad LANGUAGES C)

set(GLAD_SRC src/glad.c)

if (SHARED_LIBS)
	message (STATUS "Building GLAD Dynamic Library")
	add_library(${PROJECT_NAME} SHARED ${GLAD_SRC})
else ()
	message(STATUS "Building GLAD Static Library")
	add_library(${PROJECT_NAME} STATIC ${GLAD_SRC})
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC "include")
