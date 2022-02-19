#include "ai_system.h"

#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>

#include "system.h"
#include <List/list.h>

typedef struct {
	physics_comp_t *physics_comp;
	position_comp_t *pos_comp;
}ai_node;

typedef struct {
	float delta;
	list_t *items;
} ai_system_t;

static ai_system_t ai_sys;

static float frand(float min, float max) {
	static const __int_least8_t mult = 100;
	int32_t r_min = min * mult;
	int32_t r_max = max * mult;
	return (float)(rand() % (r_max + r_max + 1) + r_min)/mult;
}

static void ai_func(void *elm) {
	ai_node *node = (ai_node*)elm;
	if (node == NULL)
		return;

	float r_min = -1;
	float r_max = 1;
	srand(time(NULL));
	vec2f duration =  {
		.x = frand(r_min, r_max),
		.y = frand(r_min, r_max)
	};

	vec2f norm_dur = vec2f_normalize(duration);
	if(norm_dur.x < 0)
		node->pos_comp->flip = true;
	else if (norm_dur.x > 0)
		node->pos_comp->flip = false;

	node->pos_comp->center = vec2f_add(vec2f_multiply_scalar(vec2f_multiply(
										norm_dur,
										node->physics_comp->speed),
									ai_sys.delta),
				node->pos_comp->center);
}

void ai_system(float delta) {
	ai_sys.delta = delta;
	l_for_each(ai_sys.items, ai_func);
}

void ai_sys_add_item(entity *en) {
	type = COMP_TYPE_POS;
	component *pos = (component*)l_find(en->components, find_comp);
	if(!pos) {
		printf("Entity %s not have position component", en->name);
		return;
	}
	type = COMP_TYPE_PHYSICS;
	component *physics = (component*)l_find(en->components, find_comp);
	if(!physics) {
		printf("Entity %s not have position component", en->name);
		return;
	}
	ai_node *node = (ai_node*)malloc(sizeof (ai_node));
	node->pos_comp = &pos->pos_comp;
	node->physics_comp = &physics->physics_comp;
	l_push(ai_sys.items,(void *)node);
}

uint32_t init_ai_system() {
	ai_sys.items = l_create();
	return 0;
}

static void delete_items(void *elm) {
	if(elm) free(elm);
}

void destroy_ai_system() {
	l_for_each(ai_sys.items, delete_items);
	l_delete(ai_sys.items);
}
