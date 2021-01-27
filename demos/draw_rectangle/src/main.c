#include <stdio.h>
#include "Taida/Window.h"
#include "Taida/System.h"
#include "Taida/Graphics.h"

taida_t *taida;

void update(void);
void render(void);

void destroy(void);

int main(int argc, char* argv[])
{
	taida_options_t options = {
		.title = "test",

		.width = 800,
		.height = 600,
	};

	taida = taida_create(options, (taida_callbacks_t) {
				.update = update,
				.render = render,

				.destroy = destroy,
			});
	while (taida_window_isopen(taida)) {
		taida_loop(taida);
	}

	taida_destroy(taida);

	return 0;
}

void update(void) {}
void render(void) {
	taida_draw_triangle(taida, 0, 0, 32, 32);
}

void destroy(void) {}
