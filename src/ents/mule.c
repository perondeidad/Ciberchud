#include "ents/mule.h"
#include "quake.h"
#include "text.h"

#define TOO_CLOSE 4

static void mule_task_none(engine_t* const e, int32_t id, const float delta) {
#ifdef VERBOSE
	myprintf("[mule_task_none] [%d]\n", id);
#endif
	ecs_t* const ecs = &e->ecs;
	mule_t* const mule = &ecs->custom0[id].mule;
	/* is player nearby? */
	const i32 player_id = ecs->player_id;
	const vec3s player_pos = ecs->pos[player_id];
	const float dist = glm_vec3_distance(ecs->pos[id].raw, (float*)player_pos.raw);
	if (dist > TOO_CLOSE) {
		mule->nav_target = player_pos;
		mule->basic.state = MOB_STATE_NAV;
		/* anim_set(&ecs->anim[id], &e->assets.models_anim[MODELS_ANIM_MULE].anims[MULE_ANIM_IDLE], NULL); */
		anim_set(&ecs->anim[id], &e->assets.models_anim[MODELS_ANIM_CHUD].anims[CHUD_ANIM_WALK], NULL);
	}
}

static void mule_think_idle(engine_t* const e, int32_t id, const float delta) {
#ifdef VERBOSE
	myprintf("[mule_think_idle] [%d]\n", id);
#endif
	ecs_t* const ecs = &e->ecs;
	mule_t* const mule = &ecs->custom0[id].mule;

	switch (mule->basic.task.mule) {
		case MULE_TASK_NONE:
			mule_task_none(e, id, delta);
	}
}

static void mule_think_nav(engine_t* const e, int32_t id, const float delta) {
#ifdef VERBOSE
	myprintf("[mule_think_nav] [%d]\n", id);
#endif
	ecs_t* const ecs = &e->ecs;
	mule_t* const mule = &ecs->custom0[id].mule;
	edict_t* const ent = ecs->edict[id].edict;

	const i32 player_id = ecs->player_id;
	const vec3s player_pos = ecs->pos[player_id];
	mule->nav_target = player_pos;

	const float dist = glm_vec3_distance(mule->nav_target.raw, ecs->pos[id].raw);

	/* return if close enough */
	if (dist < TOO_CLOSE) {
		mule->basic.state = MOB_STATE_IDLE;
		/* anim_set(&ecs->anim[id], &e->assets.models_anim[MODELS_ANIM_MULE].anims[0], NULL); */
		anim_set(&ecs->anim[id], &e->assets.models_anim[MODELS_ANIM_CHUD].anims[0], NULL);
		return;
	}

	vec3s dir;
	dir.x =  mule->nav_target.x - ecs->pos[id].x;
	dir.y = 0;
	dir.z = mule->nav_target.z - ecs->pos[id].z;
	/* glm_vec3_sub(ecs->pos[id].raw, mule->nav_target.raw, dir.raw); */
	glm_vec3_normalize(dir.raw);

	/* is player nearby? */
	trace_t trace;
	SV_MoveToGoal(e, ent, &trace, dir, dist, delta);
}

void mule_think(void *engine, int32_t id, const float delta) {
#ifdef VERBOSE
	myprintf("[mule_think] [%d]\n", id);
#endif
	engine_t* const e = engine;
	ecs_t* const ecs = &e->ecs;

	if (ecs->hp[id].hp <= 0) {
		for (int i=0; i<32; i++) {
			vec3s pos, vel;
			rand_vec3(&e->seed, vel.raw);
			const float particle_spread = 0.2f;
			glm_vec3_scale(vel.raw, particle_spread, pos.raw);
			const float particle_speed = 5.0f;
			glm_vec3_scale(vel.raw, particle_speed, vel.raw);
			glm_vec3_add(pos.raw, ecs->pos[id].raw, pos.raw);
			new_particle(ecs, &pos, &vel, &e->assets.models_basic[MODELS_STATIC_CUBE], 0.1f);
		}
		free_mob(ecs, id);
		return;
	}

	mule_t* const mule = &ecs->custom0[id].mule;
	if (mule->basic.flicker_cooldown > 0) {
		ecs->flags[id].highlight = 1;
	} else {
		ecs->flags[id].highlight = 0;
	}
	mule->basic.flicker_cooldown -= delta;

	/* Turn to player */
	switch (mule->basic.state) {
		case MOB_STATE_IDLE:
			mule_think_idle(e, id, delta);
			break;
		case MOB_STATE_NAV:
			mule_think_nav(e, id, delta);
			break;
		default:
			mule_think_idle(e, id, delta);
	}
}

void mule_hit(void *engine, int32_t id, const int16_t dmg) {
	engine_t* const e = engine;
	ecs_t* const ecs = &e->ecs;
#ifndef NDEBUG
	myprintf("[mule_hit] [%d] hp:%d, dmg:%d\n", id, ecs->hp[id].hp, dmg);
#endif
	ecs->hp[id].hp -= dmg;
	mule_t* const mule = &ecs->custom0[id].mule;
	mule->basic.flicker_cooldown = 0.1f;
}

void mule_init(void *engine, int32_t id) {
#ifndef NDEBUG
	engine_t* const e = engine;
	ecs_t* const ecs = &e->ecs;
	myprintf("[mule_init] [%d] HP:%d\n", id, ecs->hp[id].hp);
#endif
}

void mule_task_init(engine_t* const e, const int32_t id, const mule_task_e task) {
	ecs_t* const ecs = &e->ecs;
	ecs->custom0[id].mule.basic.task.mule = task;
	switch (task) {
		default:
			/* anim_set(&ecs->anim[id], &e->assets.models_anim[MODELS_ANIM_MULE].anims[0], NULL); */
			anim_set(&ecs->anim[id], &e->assets.models_anim[MODELS_ANIM_CHUD].anims[0], NULL);
	}
}
