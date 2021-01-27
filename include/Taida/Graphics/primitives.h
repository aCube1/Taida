#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include "Taida/System/log.h"
#include "Taida/System/core.h"
#include "Taida/Window/window.h"

unsigned int taida_create_shaderProgram(const char* vertexShaderSource, const char *fragmentShaderSource);
unsigned int taida_create_VAO();

void taida_draw_triangle(taida_t *taida, float x, float y, float width, float height);

#endif /* _PRIMITIVES_H_ */
