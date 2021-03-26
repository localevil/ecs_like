#include "transform_system.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	position_comp_t *parent_pos_comp;
	position_comp_t *trans_pos_comp;
	transform_comp_t *trans_comp;
} transform_node;

typedef struct {
	list_t *items;
} transform_system_t;

static transform_system_t  trans_sys;

static void transform_func(void* elm) {
	transform_node *node = (transform_node*)elm;
	if(node) {
		vec2f (*trans_func)(vec2f,vec2f);
		if (!node->parent_pos_comp->flip) {
			trans_func = vec2f_add;
		} else {
			trans_func = vec2f_subtract;
		}
		node->trans_pos_comp->center = trans_func(node->parent_pos_comp->center,
												  node->trans_comp->shift);
	}
}

void transform_system() {
	l_for_each(trans_sys.items, transform_func);
}

static component_type type;

static bool find_comp(void *data) {
	component *comp = (component*)data;
	return comp && comp->type == type;
}

void transform_sys_add_item(entity *parent_en, entity *trans_en) {
	type = COMP_TYPE_POS;
	component *parent_pos = (component*)l_find(parent_en->components, find_comp);
	if(!parent_pos) {
		printf("Entity %s not have position component", parent_en->name);
		return;
	}
	type = COMP_TYPE_POS;
	component *trans_pos = (component*)l_find(trans_en->components, find_comp);
	if(!trans_pos) {
		printf("Entity %s not have position component", trans_en->name);
		return;
	}
	type = COMP_TYPE_TRANSFORM;
	component *trans = (component*)l_find(trans_en->components, find_comp);
	if(!trans) {
		printf("Entity %s not have transform component", trans_en->name);
		return;
	}
	transform_node *node = (transform_node*)malloc(sizeof (transform_node));
	node->parent_pos_comp = &parent_pos->pos_comp;
	node->trans_pos_comp = &trans_pos->pos_comp;
	node->trans_comp = &trans->transform_comp;
	l_push(trans_sys.items,(void *)node);
}

uint32_t init_transform_system() {
	trans_sys.items = l_create();
	return 0;
}

static void delete_items(void *elm) {
	if(elm) free(elm);
}

void destroy_transform_system() {
	l_for_each(trans_sys.items, delete_items);
	l_delete(trans_sys.items);
}
