#ifndef ENTS_TROON_H
#define ENTS_TROON_H

#include "engine.h"

void troon_init(void *engine, int32_t id);
void troon_think(void *engine, int32_t id, const float delta);
void troon_hit(void *engine, int32_t id, const int16_t dmg);
void troon_task_init(engine_t* const e, const int32_t id, const troon_task_e task);

#endif
#define ENTS_TROON_H
