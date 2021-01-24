#include <stdio.h>
#include "Taida/System/log.h"

void taida_log(int const priority, char const *msg)
{
	switch (priority) {
		case LOGP_ERROR:
			fprintf(stderr, "[ERROR] %s\n", msg);
			break;
		case LOGP_WARNNING:
			fprintf(stderr, "[WARN] %s\n", msg);
			break;
		case LOGP_DEBUG:
			fprintf(stderr, "[DEBUG] %s\n", msg);
			break;
		case LOGP_INFO:
			fprintf(stderr, "[INFO] %s\n", msg);
			break;
	}
}
