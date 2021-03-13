#include "ai_system.h"

#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>

#include <Components/component.h>
#include <List/list.h>

typedef struct {
	float delta;
	list_t *items;
} ai_system_t;

static ai_system_t ai_sys;

static void ai_func(void *elm) {
	component *pos = (component*)elm;
	if (pos && pos->type == COMP_TYPE_POS) {
		srand(time(NULL));
		uint32_t r_min = -200;
		uint32_t r_max = 200;
		uint32_t duration_x = rand() % (r_max + 1) + r_min;
		uint32_t duration_y = rand() % (r_max + 1) + r_min;
		//todo drawing compoment with width and height
		if (pos->pos_comp.center.x + duration_x > 0 && pos->pos_comp.center.x + 10 + duration_x < 640)
			pos->pos_comp.center.x += duration_x * ai_sys.delta;
		if (pos->pos_comp.center.y + duration_y > 0 && pos->pos_comp.center.y + 10 + duration_y < 480)
			pos->pos_comp.center.y += duration_y * ai_sys.delta;
	}
}

void ai_system(float delta) {
	ai_sys.delta = delta;
	l_for_each(ai_sys.items, ai_func);
}

static component_type type;

static bool find_comp(void *data) {
	component *comp = (component*)data;
	return comp && comp->type == type;
}

void ai_sys_add_item(entity *en) {
	type = COMP_TYPE_POS;
	component *pos = (component*)l_find(en->components, find_comp);
	if(!pos) {
		printf("Entity %s not have position component", en->name);
		return;
	}
	l_push(ai_sys.items,(void *)pos);
}

uint32_t init_ai_sustem() {
	ai_sys.items = l_create();
	return 0;
}

void destroy_ai_system() {
	l_delete(ai_sys.items);
}
