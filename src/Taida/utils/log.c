#include <stdio.h>
#include "Taida/utils/log.h"

void taida_log(int const priority, char const *msg)
{
	switch (priority) {
		case LOGP_ERROR:
			fprintf(stderr, "[ERROR] %s\n", msg);
			break;
		case LOGP_WARNNING:
			fprintf(stderr, "[WARNNING] %s\n", msg);
			break;
		case LOGP_DEBUG:
			fprintf(stderr, "[DEBUG] %s\n", msg);
			break;
		default:
			fprintf(stderr, "[LOG] %s\n", msg);
			break;
	}
}
