#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "List/list.h"

#include "Systems/ai_system.h"
#include "Systems/drawing_system.h"
#include "Systems/collision_system.h"
#include "Systems/moving_system.h"
#include "Systems/event_system.h"
#include "Systems/transform_system.h"

#include "Entitys/entity.h"

void init_systems() {
	if(init_drawing_system(640, 480))
	{
		printf("drawing system has`t been created");
	}
	init_moving_sustem();
	init_ai_system();
	init_moving_sustem();
	init_collision_system(10);
	init_transform_system();
}

void destroy_systems() {
	destroy_collison_system();
	destroy_ai_system();
	destroy_moving_system();
	destroy_drawing_system();
	destroy_transform_system();
}

int main() {
	init_systems();

	entity player = { .name = "Player", .components = l_create()};

	component player_position_comp = {
		.type = COMP_TYPE_POS,
		.pos_comp = { .center = {.x = 0, .y = 0 }}
	};
	l_push(player.components, (void*)&player_position_comp);

	component player_physics_comp = {
		.type = COMP_TYPE_PHYSICS,
		.physics_comp = {
			.type = PHYSIC_TYPE_DYNAMIC,
			.speed = {.x = 100, .y = 100 },
			.halfSize = {.x = 16, .y = 24}
		}
	};
	l_push(player.components, (void*)&player_physics_comp);

	component player_texture_comp = {
		.type = COMP_TYPE_TEXTURE,
		.texture_comp = {
			.texture = drawing_sys_add_texture("Assets/characters.png"),
			.pos = { .x = 0, .y = 32 },
			.texture_size = { .x = 32, .y = 32 },
			.draw_size = { .x = 64, .y = 64 }
		}
	};
	l_push(player.components, (void*)&player_texture_comp);

	entity enemy = { .name = "Enemy", .components = l_create() };

	component enemy_position_comp = {
		.type = COMP_TYPE_POS,
		.pos_comp = { .center = { .x = 640 / 2, .y = 480 / 2 } }
	};
	l_push(enemy.components, (void*)&enemy_position_comp);

	component enemy_physics_comp = {
		.type = COMP_TYPE_PHYSICS,
		.physics_comp = {
			.type = PHYSIC_TYPE_DYNAMIC,
			.speed = {.x = 50, .y = 50},
			.halfSize = {.x = 16, .y = 24 }
		}
	};
	l_push(enemy.components, (void*)&enemy_physics_comp);

	component enemy_texture_comp = {
		.type = COMP_TYPE_TEXTURE,
		.texture_comp = {
			.texture = drawing_sys_add_texture("Assets/characters.png"),
			.pos = { .x = 0, .y = 64},
			.texture_size = { .x = 32, .y = 32 },
			.draw_size = { .x = 64, .y = 64 }
		}
	};
	l_push(enemy.components, (void*)&enemy_texture_comp);

	entity wall = { .name = "Wall", .components = l_create() };

	component wall_position_comp = {
		.type = COMP_TYPE_POS,
		.pos_comp = { .center.x = 205, .center.y = 300 }
	};
	l_push(wall.components, (void*)&wall_position_comp);

	component wall_texture_comp = {
		.type = COMP_TYPE_TEXTURE,
		.texture_comp = {
			.texture = NULL,
			.draw_size = {.x = 10, .y = 200 }
		}
	};
	l_push(wall.components, (void*)&wall_texture_comp);

	component wall_physics_comp = {
		.type = COMP_TYPE_PHYSICS,
		.physics_comp = {
			.type = PHYSIC_TYPE_STATIC,
			.speed = { .x = 0, .y = 0 },
			.halfSize = { .x = 5, .y = 100}
		}
	};
	l_push(wall.components, (void*)&wall_physics_comp);

	entity dot = { .name = "Dot", .components = l_create()};

	component dot_pos_component = { .type = COMP_TYPE_POS };
	l_push(dot.components, (void*)&dot_pos_component);

	component dot_trans_component = {
		.type = COMP_TYPE_TRANSFORM,
		.transform_comp = {
			.shift.x = 30,
			.shift.y = 0
		}
	};
	l_push(dot.components, (void*)&dot_trans_component);

	component dot_texture_component = {
		.type = COMP_TYPE_TEXTURE,
		.texture_comp = {
			.texture = NULL,
			.draw_size = { .x = 5, .y = 5}
		}
	};
	l_push(dot.components, (void*)&dot_texture_component);

	drawing_sys_add_item(&player);
	drawing_sys_add_item(&enemy);
	drawing_sys_add_item(&wall);
	drawing_sys_add_item(&dot);

	moving_sys_add_item(&player);

	ai_sys_add_item(&enemy);

	collision_sys_add_item(&player);
	collision_sys_add_item(&enemy);
	collision_sys_add_item(&wall);

	transform_sys_add_item(&player, &dot);

	uint32_t prev_time = 0;
	while(1){
		uint32_t current_time;
		if(event_system(&current_time)) {
			break;
		}

		float delta = (float)(current_time - prev_time) / 1000;

		ai_system(delta);

		moving_system(delta);
		transform_system();
		collision_system();

		drawing_system();
		prev_time = current_time;
	}

	destroy_systems();

	return 0;
}
