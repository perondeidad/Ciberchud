#ifndef FLAGS_H
#define FLAGS_H

#include <stdbool.h>

typedef struct {
	int map;
	unsigned int no_pointlights: 1;
	unsigned int no_shadowcasters: 1;
} init_cfg_t;

int flags(init_cfg_t *cfg, const int argc, const char* const argv[]);

#endif
