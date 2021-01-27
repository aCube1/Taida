project(draw_rectangle)

file(GLOB SRCS "src/*.c")

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} Taida_system Taida_window Taida_graphics)
