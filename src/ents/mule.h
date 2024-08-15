#ifndef ENTS_MULE_H
#define ENTS_MULE_H

#include "engine.h"

void mule_init(void *engine, int32_t id);
void mule_think(void *engine, int32_t id, const float delta);
void mule_hit(void *engine, int32_t id, const int16_t dmg);
void mule_task_init(engine_t* const e, const int32_t id, const mule_task_e task);

#endif
