#include "ai_common.h"

void ai_flicker_update(flag_t* const flags, float* const flicker_cooldown, const float delta) {
	if (*flicker_cooldown > 0)
		flags->highlight = 1;
	else
		flags->highlight = 0;
	*flicker_cooldown -= delta;
}
