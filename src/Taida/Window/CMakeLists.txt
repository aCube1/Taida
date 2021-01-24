set(MODULE_NAME Taida_window)

file(GLOB SRCS "window.c")

if (BUILD_SHARED_LIBS)
	add_library(${MODULE_NAME} SHARED ${SRCS})
else ()
	add_library(${MODULE_NAME} STATIC ${SRCS})
endif ()

target_link_libraries(${MODULE_NAME} ${LINK_LIBRARIES} Taida_system)
target_include_directories(${MODULE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
