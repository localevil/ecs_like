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

int main()
{
	if(init_drawing_system(640, 480))
	{
		printf("drawing system has been created");
	}

	init_moving_sustem();

	component player_position_comp;
	player_position_comp.type = COMP_TYPE_POS;
	player_position_comp.pos_comp.pos.x = 0;
	player_position_comp.pos_comp.pos.y = 0;
	player_position_comp.pos_comp.size.x = 10;
	player_position_comp.pos_comp.size.y = 10;

//	component player_texture_comp;
//	player_position_comp.type = TEXTURE_COMP;
//	player_position_comp.texture_comp = texture_comp_create("characters.png", 32, 32);

	component enemy_position_comp;
	enemy_position_comp.type = COMP_TYPE_POS;
	enemy_position_comp.pos_comp.pos.x = 630 / 2;
	enemy_position_comp.pos_comp.pos.y = 470 / 2;
	enemy_position_comp.pos_comp.size.x = 10;
	enemy_position_comp.pos_comp.size.y = 10;
//	game_object_t enemy;
//	enemy.components = l_create();
//	l_push(enemy.components, (void *) &enemy_position_comp);

	list_t* drawing = l_create();
	list_t* moving = l_create();
	list_t* ai = l_create();
	component* collision[10] = {0};

	l_push(drawing,(void *)&player_position_comp);
	l_push(drawing,(void *)&enemy_position_comp);

	l_push(moving, (void *) &player_position_comp);

//	l_push(ai,(void *)&enemy_position_comp.pos_comp);

	collision[0] = &player_position_comp;
	collision[1] = &enemy_position_comp;

	uint32_t prev_time = 0;
	while(1){
		uint32_t current_time;
		if(event_system(&current_time)) {
			break;
		}

//		ai_system(ai);
		collision_system(collision);

		moving_system(moving);
		if (current_time - prev_time > 15)
		{
			drawing_system_process(drawing);
			prev_time = current_time;
		}

	}
	l_delete(drawing);
	l_delete(ai);
	l_delete(moving);
	destroy_drawing_system();

	return 0;
}
