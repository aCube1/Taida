#ifndef _CORE_H_
#define _CORE_H_

#include <stdbool.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

typedef struct taida_callbacks {
	void (*update)(void);
	void (*render)(void);

	void (*destroy)(void);
} taida_callbacks_t;

typedef struct taida {
	GLFWwindow *window;

	lua_State *lua;

	taida_callbacks_t callbacks;

	int max_fps;
	int start_frame;
	float delta_time;
} taida_t;

typedef struct taida_options {
	char *title;

	int x, y;
	int width, height;
} taida_options_t;

#endif /* _CORE_H_ */
