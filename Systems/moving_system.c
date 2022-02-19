#include "moving_system.h"
#include <stdlib.h>
#include "system.h"

typedef struct {
	position_comp_t *pos_comp;
	physics_comp_t *physics_comp;
} moving_node;

typedef struct {
	float delta;
	list_t *items;
} moving_system_t;

static moving_system_t move_sys;

static void moving_func(void *elm) {
	moving_node *node = (moving_node *)elm;
	if (node == NULL)
		return;

	vec2f duration = node->pos_comp->duration;
	node->pos_comp->duration.x = 0;
	node->pos_comp->duration.y = 0;
	if(duration.x < 0)
		node->pos_comp->flip = true;
	else if (duration.x > 0)
		node->pos_comp->flip = false;

	node->pos_comp->center = vec2f_add(
								vec2f_multiply_scalar(
									vec2f_multiply(
										duration,
										node->physics_comp->speed),
									move_sys.delta),
								node->pos_comp->center);
}

void moving_system(float delta) {
	move_sys.delta = delta;
	l_for_each(move_sys.items, moving_func);
}

uint32_t init_moving_sustem() {
	move_sys.items = l_create();
	return 0;
}

void moving_sys_add_item(entity *en) {
	type = COMP_TYPE_POS;
	component *pos = (component*)l_find(en->components, find_comp);
	if(!pos) {
		printf("Entity %s not have position component", en->name);
		return;
	}
	type = COMP_TYPE_PHYSICS;
	component *physics = (component*)l_find(en->components, find_comp);
	if(!physics) {
		printf("Entity %s not have physics component", en->name);
		return;
	}
	moving_node *node = (moving_node*)malloc(sizeof (moving_node));
	node->pos_comp = &pos->pos_comp;
	node->physics_comp = &physics->physics_comp;
	l_push(move_sys.items,(void *)node);
}

static void delete_items(void *elm) {
	if(elm) free(elm);
}

void destroy_moving_system() {
	l_for_each(move_sys.items, delete_items);
	l_delete(move_sys.items);
}
