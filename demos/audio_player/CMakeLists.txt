project(audio_player        )

file(GLOB SRCS "src/*.c")

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} Taida)
