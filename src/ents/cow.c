#include "ents/cow.h"
#include "ai_common.h"
#include "quake.h"
#include "text.h"

#define TOO_CLOSE 4

static void cow_task_none(engine_t* const e, int32_t id, const float delta) {
#ifdef VERBOSE
	myprintf("[cow_task_none] [%d]\n", id);
#endif
	ecs_t* const ecs = &e->ecs;
	cow_t* const cow = &ecs->custom0[id].cow;
	/* is player nearby? */
	const i32 player_id = ecs->player_id;
	const vec3s player_pos = ecs->pos[player_id];
	const float dist = glm_vec3_distance(ecs->pos[id].raw, (float*)player_pos.raw);
	if (dist > TOO_CLOSE) {
		cow->nav_target = player_pos;
		cow->basic.state = MOB_STATE_NAV;
		anim_set(&ecs->anim[id], &e->assets.models_anim[MODELS_ANIM_COW].anims[COW_ANIM_WALK], NULL);
	}
}

static void cow_think_idle(engine_t* const e, int32_t id, const float delta) {
#ifdef VERBOSE
	myprintf("[cow_think_idle] [%d]\n", id);
#endif
	ecs_t* const ecs = &e->ecs;
	cow_t* const cow = &ecs->custom0[id].cow;

	switch (cow->basic.task.cow) {
		case COW_TASK_NONE:
			cow_task_none(e, id, delta);
			break;
		default:
			break;
	}
}

static void cow_think_nav(engine_t* const e, int32_t id, const float delta) {
#ifdef VERBOSE
	myprintf("[cow_think_nav] [%d]\n", id);
#endif
	ecs_t* const ecs = &e->ecs;
	edict_t* const ent = ecs->edict[id].edict;

	vec3 forward = {0,0,1};
	vec3s dir;
	glm_quat_rotatev(e->ecs.rot[id].raw, forward, dir.raw);
	trace_t trace = {0};
#if 0
	float scale = 5;
	bbox_t move;
	move.min = e->ecs.pos[id];
	print_vec3("dir", dir);
	move.max.x = dir.x * scale + move.min.x;
	move.max.y = move.min.y;
	move.max.z = dir.x * scale + move.min.z;
	print_vec3("min", move.min);
	print_vec3("max", move.max);
	TraceLine(e, &e->assets.map.qmods[0].hulls[0], &move, &trace, id);
	myprintf("%f %f %f %f %d %d %f %p\n", trace.plane.normal.x, trace.plane.normal.y, trace.plane.normal.z, trace.plane.dist, trace.contents, trace.allsolid, trace.fraction, trace.ent);
#endif
	const float speed = 150;
	SV_MoveToGoal(e, ent, &trace, dir, speed, delta);
	if (trace.contents == CONTENTS_SOLID && trace.plane.dist < 0.1) {
		vec3 new_dir;
		rand_vec3(&e->seed, new_dir);
		glm_vec3_normalize(new_dir);
		vec3 up = {0,1,0};
		glm_quat_for(new_dir, up, ecs->rot[id].raw);
	}
	/* myprintf("%f %f %f %f %d %d\n", trace., trace.plane.normal.y, trace.plane.normal.z, trace.plane.dist, trace.contents, trace.allsolid); */
}

void cow_think(void *engine, int32_t id, const float delta) {
#ifdef VERBOSE
	myprintf("[cow_think] [%d]\n", id);
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

	cow_t* const cow = &ecs->custom0[id].cow;
	ai_flicker_update(&ecs->flags[id], &cow->basic.flicker_cooldown, delta);

	switch (cow->basic.state) {
		case MOB_STATE_IDLE:
			cow_think_idle(e, id, delta);
			break;
		case MOB_STATE_NAV:
			cow_think_nav(e, id, delta);
			break;
		default:
			cow_think_idle(e, id, delta);
	}
}

void cow_hit(void *engine, int32_t id, const int16_t dmg) {
	engine_t* const e = engine;
	ecs_t* const ecs = &e->ecs;
#ifndef NDEBUG
	myprintf("[cow_hit] [%d] hp:%d, dmg:%d\n", id, ecs->hp[id].hp, dmg);
#endif
	ecs->hp[id].hp -= dmg;
	cow_t* const cow = &ecs->custom0[id].cow;
	cow->basic.flicker_cooldown = 0.1f;
}

void cow_init(void *engine, int32_t id) {
#ifndef NDEBUG
	engine_t* const e = engine;
	ecs_t* const ecs = &e->ecs;
	myprintf("[cow_init] [%d] HP:%d\n", id, ecs->hp[id].hp);
#endif
}

void cow_task_init(engine_t* const e, const int32_t id, const cow_task_e task) {
	ecs_t* const ecs = &e->ecs;
	ecs->custom0[id].cow.basic.task.cow = task;
	switch (task) {
		default:
			break;
	}
}
