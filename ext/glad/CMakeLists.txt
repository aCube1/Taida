project(glad LANGUAGES C)

set(GLAD_SRC src/glad.c)

add_library(${PROJECT_NAME} STATIC ${GLAD_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC "include")