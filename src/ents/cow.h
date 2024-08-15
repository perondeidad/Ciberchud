#ifndef ENTS_COW_H
#define ENTS_COW_H

#include "engine.h"

void cow_init(void *engine, int32_t id);
void cow_think(void *engine, int32_t id, const float delta);
void cow_hit(void *engine, int32_t id, const int16_t dmg);
void cow_task_init(engine_t* const e, const int32_t id, const cow_task_e task);

#endif
