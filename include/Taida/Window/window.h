#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Taida/System/log.h"
#include "Taida/System/core.h"

taida_t *taida_create(taida_options_t options, taida_callbacks_t callbacks);
void taida_destroy(taida_t *taida);

void taida_loop(taida_t *taida);

bool taida_window_isopen(taida_t *taida);

#endif /* _WINDOW_H_ */
