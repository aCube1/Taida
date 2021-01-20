#include <stdlib.h>
#include "Taida/taida.h"

taida_t *taida_create(taida_options_t options, taida_callbacks_t callbacks)
{
	if (glfwInit() == GLFW_FALSE) {
		taida_log_error("TAIDA - GLFW Not Initialized");

		return NULL;
	}
	taida_log_debug("TAIDA - GLFW Initialized");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	taida_t *taida = malloc(sizeof(taida_t));
	if (taida == NULL) {
		taida_log_error("TAIDA - Can\'t Create Engine Bases");
		
		taida_destroy(taida);
		return NULL;
	}

	taida->window = glfwCreateWindow(options.width, options.height, options.title, NULL, NULL);
	if (taida->window == NULL) {
		taida_log_error("TAIDA - OpenGL Window Not Created");
		
		taida_destroy(taida);
		return NULL;
	}
	taida_log_debug("TAIDA - OpenGL Window Created");
	glfwMakeContextCurrent(taida->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		taida_log_error("TAIDA - GLAD Not Initialized");
		
		taida_destroy(taida);
		return NULL;
	}
	taida_log_debug("TAIDA - GLAD Initialized");

	taida->lua = luaL_newstate();
	if (taida->lua == NULL) {
		taida_log_error("TAIDA - Lua Not Initialized");
		
		taida_destroy(taida);
		return NULL;
	}
	taida_log_debug("TAIDA - Lua Initialized");
	luaL_openlibs(taida->lua);

	taida->callbacks = callbacks;
	if (taida->callbacks.init != NULL)
		taida->callbacks.init();
	
	taida->max_fps = 60;
	taida_log_debug("TAIDA - Engine Created");

	return taida;
}

void taida_destroy(taida_t *taida)
{
	if (taida != NULL) {
		if (taida->window != NULL)
			glfwDestroyWindow(taida->window);
		
		if (taida->lua != NULL)
			lua_close(taida->lua);

		if (taida->callbacks.destroy != NULL)
			taida->callbacks.destroy();

		free(taida);
	}

	glfwTerminate();
	taida_log_debug("TAIDA - Engine Closed and Destroyed");
}

void taida_run_loop(taida_t *taida)
{
	while (taida->running) {
		taida->callbacks.update();
		taida->callbacks.render();

		glfwSwapBuffers(taida->window);
		glfwPollEvents();
	}
}

