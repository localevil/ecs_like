#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "List/list.h"

#include "Systems/ai_system.h"
#include "Systems/drawing_system.h"
#include "Systems/collision_system.h"
#include "Systems/moving_system.h"
#include "Systems/event_system.h"

#include "Entitys/entity.h"

void init_systems() {
	if(init_drawing_system(640, 480))
	{
		printf("drawing system has`t been created");
	}
	init_moving_sustem();
	init_ai_sustem();
	init_moving_sustem();
	init_collision_sustem(10);
}

void destroy_systems() {
	destroy_collison_system();
	destroy_ai_system();
	destroy_moving_system();
	destroy_drawing_system();
}

int main() {
	init_systems();

	entity player;
	player.name = "Player";
	player.components = l_create();

	component player_position_comp;
	player_position_comp.type = COMP_TYPE_POS;
	player_position_comp.pos_comp.center.x = 0;
	player_position_comp.pos_comp.center.y = 0;

	l_push(player.components, (void*)&player_position_comp);

	component player_physics_comp;
	player_physics_comp.type = COMP_TYPE_PHYSICS;
	player_physics_comp.physics_comp.type = PHYSIC_TYPE_DYNAMIC;
	player_physics_comp.physics_comp.speed.x = 100;
	player_physics_comp.physics_comp.speed.y = 100;
	player_physics_comp.physics_comp.halfSize.x = 16;
	player_physics_comp.physics_comp.halfSize.y = 24;

	l_push(player.components, (void*)&player_physics_comp);

	void *texture = drawing_sys_add_texture("characters.png");

	component player_texture_comp;
	player_texture_comp.type = COMP_TYPE_TEXTURE;
	player_texture_comp.texture_comp.texture = texture;
	player_texture_comp.texture_comp.pos.x = 0;
	player_texture_comp.texture_comp.pos.y = 32;
	player_texture_comp.texture_comp.texture_size.x = 32;
	player_texture_comp.texture_comp.texture_size.y = 32;
	player_texture_comp.texture_comp.draw_size.x = 64;
	player_texture_comp.texture_comp.draw_size.y = 64;

	l_push(player.components, (void*)&player_texture_comp);

	entity enemy;
	enemy.name = "Enemy";
	enemy.components = l_create();

	component enemy_position_comp;
	enemy_position_comp.type = COMP_TYPE_POS;
	enemy_position_comp.pos_comp.center.x = 640 / 2;
	enemy_position_comp.pos_comp.center.y = 480 / 2;

	l_push(enemy.components, (void*)&enemy_position_comp);

	component enemy_physics_comp;
	enemy_physics_comp.type = COMP_TYPE_PHYSICS;
	enemy_physics_comp.physics_comp.type = PHYSIC_TYPE_DYNAMIC;
	enemy_physics_comp.physics_comp.speed.x = 0;
	enemy_physics_comp.physics_comp.speed.y = 0;
	enemy_physics_comp.physics_comp.halfSize.x = 16;
	enemy_physics_comp.physics_comp.halfSize.y = 24;

	l_push(enemy.components, (void*)&enemy_physics_comp);

	component enemy_texture_comp;
	enemy_texture_comp.type = COMP_TYPE_TEXTURE;
	enemy_texture_comp.texture_comp.texture = texture;
	enemy_texture_comp.texture_comp.pos.x = 0;
	enemy_texture_comp.texture_comp.pos.y = 64;
	enemy_texture_comp.texture_comp.texture_size.x = 32;
	enemy_texture_comp.texture_comp.texture_size.y = 32;
	enemy_texture_comp.texture_comp.draw_size.x = 64;
	enemy_texture_comp.texture_comp.draw_size.y = 64;

	l_push(enemy.components, (void*)&enemy_texture_comp);

	entity wall;
	wall.name = "Wall";
	wall.components = l_create();

	component wall_position_comp;
	wall_position_comp.type = COMP_TYPE_POS;
	wall_position_comp.pos_comp.center.x = 205;
	wall_position_comp.pos_comp.center.y = 300;

	l_push(wall.components, (void*)&wall_position_comp);

	component wall_texture_comp;
	wall_texture_comp.type = COMP_TYPE_TEXTURE;
	wall_texture_comp.texture_comp.texture = NULL;
	wall_texture_comp.texture_comp.draw_size.x = 10;
	wall_texture_comp.texture_comp.draw_size.y = 200;

	l_push(wall.components, (void*)&wall_texture_comp);

	component wall_physics_comp;
	wall_physics_comp.type = COMP_TYPE_PHYSICS;
	wall_physics_comp.physics_comp.type = PHYSIC_TYPE_STATIC;
	wall_physics_comp.physics_comp.speed.x = 0;
	wall_physics_comp.physics_comp.speed.y = 0;
	wall_physics_comp.physics_comp.halfSize.x = 5;
	wall_physics_comp.physics_comp.halfSize.y = 100;

	l_push(wall.components, (void*)&wall_physics_comp);

	drawing_sys_add_item(&player);
	drawing_sys_add_item(&enemy);
	drawing_sys_add_item(&wall);

	moving_sys_add_item(&player);

	ai_sys_add_item(&enemy);

	collision_sys_add_item(&player);
	collision_sys_add_item(&enemy);
	collision_sys_add_item(&wall);

	uint32_t prev_time = 0;
	while(1){
		uint32_t current_time;
		if(event_system(&current_time)) {
			break;
		}

		float delta = (float)(current_time - prev_time) / 1000;

		ai_system(delta);

		moving_system(delta);
		collision_system();

		drawing_system();
		prev_time = current_time;
	}

	destroy_systems();

	return 0;
}
