#ifndef _TAIDA_H_
#define _TAIDA_H_

#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

typedef struct taida_callbacks {
	void (*init)(void);

	void (*update)(void);
	void (*render)(void);

	void (*destroy)(void);
} taida_callbacks_t;

typedef struct taida {
	GLFWwindow *window;

	lua_State *lua;

	taida_callbacks_t callbacks;

	bool running;

	int max_fps;
	int start_frame;
	float delta_time;
} taida_t;

typedef struct taida_options {
	char *title;

	int x, y;
	int width, height;
} taida_options_t;

taida_t *taida_create(taida_options_t options, taida_callbacks_t callbacks);
void taida_destroy(taida_t *taida);

void taida_run_loop(taida_t *taida);

#endif /* _TAIDA_H_ */
