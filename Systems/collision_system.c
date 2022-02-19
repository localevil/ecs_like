#include "collision_system.h"

#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "system.h"

typedef struct {
	position_comp_t *pos_comp;
	physics_comp_t *physics_comp;
} collision_node;

typedef struct {
	uint32_t size;
	uint32_t max;
	collision_node *items;
} collision_system_t;

static collision_system_t collision_sys;

static bool check_collision(collision_node *go1, collision_node *go2) {
	vec2f dist = vec2f_abs(
			vec2f_subtract(go1->pos_comp->center, go2->pos_comp->center));
	vec2f size = vec2f_add(go1->physics_comp->halfSize, go2->physics_comp->halfSize);
	if (dist.x > size.x)
		return false;
	if (dist.y > size.y)
		return false;
	return true;
}

vec2f collision_depth(collision_node *n1, vec2f d1,
					  collision_node *n2, vec2f d2) {
	vec2f vec1_x = {n1->physics_comp->halfSize.x, 0};
	float dot = vec2f_dot(vec1_x, d1);
	float cos_a = dot / (vec2f_module(vec1_x) * vec2f_module(d1));
	float size1_x = n1->physics_comp->halfSize.x / cos_a;

	vec2f vec1_y = {0, n1->physics_comp->halfSize.y};
	dot = vec2f_dot(vec1_y, d1);
	cos_a = dot / (vec2f_module(vec1_y) * vec2f_module(d1));
	float size1_y = n1->physics_comp->halfSize.y / cos_a;

	vec2f vec2_x = {n2->physics_comp->halfSize.x, 0};
	dot = vec2f_dot(vec2_x, d2);
	cos_a = dot / (vec2f_module(vec2_x) * vec2f_module(d2));
	float size2_x = n2->physics_comp->halfSize.x / cos_a;

	vec2f vec2_y = {0, n2->physics_comp->halfSize.y};
	dot = vec2f_dot(vec2_y, d2);
	cos_a = dot / (vec2f_module(vec2_y) * vec2f_module(d2));
	float size2_y = n2->physics_comp->halfSize.y / cos_a;

	vec2f result = {fabs(size1_x) + fabs(size2_x), fabs(size1_y) + fabs(size2_y)};

	return result;
}

void collision_system() {
	for (uint32_t i = 0; i < collision_sys.size; i++) {
		for (uint32_t j = i + 1; j < collision_sys.size ; j++) {

			collision_node *first = &collision_sys.items[i];
			collision_node *second = &collision_sys.items[j];

			if(check_collision(first, second)) {
				vec2f first_push_vector = vec2f_normalize(
							vec2f_subtract(first->pos_comp->center,
										   second->pos_comp->center));
				vec2f second_push_vector = vec2f_normalize(
							vec2f_subtract(second->pos_comp->center,
										   first->pos_comp->center));

				vec2f min_dist = collision_depth(first, second_push_vector,
												 second, first_push_vector);

				float real_dist = vec2f_module(vec2f_abs(
							vec2f_subtract(first->pos_comp->center,
										   second->pos_comp->center)));

				float dist_move_x = min_dist.x - real_dist;
				float dist_move_y = min_dist.y - real_dist;

				float dist_move = (dist_move_x < dist_move_y
								   ? dist_move_x
								   : dist_move_y) + 0.1;
				if (first->physics_comp->type == PHYSIC_TYPE_STATIC)
				{
					second->pos_comp->center = vec2f_add(
								vec2f_multiply_scalar(second_push_vector,
													  dist_move),
								second->pos_comp->center);
				} else if (second->physics_comp->type == PHYSIC_TYPE_STATIC) {
					first->pos_comp->center = vec2f_add(
								vec2f_multiply_scalar(first_push_vector,
													  dist_move),
								first->pos_comp->center);
				} else {
					second->pos_comp->center = vec2f_add(
								vec2f_multiply_scalar(second_push_vector,
											   dist_move/ 2),
								second->pos_comp->center);
					first->pos_comp->center = vec2f_add(
								vec2f_multiply_scalar(first_push_vector,
											   dist_move / 2),
								first->pos_comp->center);
				}
			}
		}
	}
}

uint32_t init_collision_system(uint32_t max) {
	collision_sys.size = 0;
	collision_sys.max = max;
	collision_sys.items = calloc(collision_sys.max,sizeof (collision_node));
	return 0;
}

void collision_sys_add_item(entity *en) {
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
	if (collision_sys.size > collision_sys.max) {
		printf("Entity %s not added to collision system. Array is full\n", en->name);
		return;
	}
	collision_node *node = &collision_sys.items[collision_sys.size];
	node->physics_comp = &physics->physics_comp;
	node->pos_comp = &pos->pos_comp;
	collision_sys.size++;
}

void destroy_collison_system() {
	free(collision_sys.items);
}
