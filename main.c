#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "List/list.h"

#include "Systems/ai_system.h"
#include "Systems/drawing_system.h"
#include "Systems/collision_system.h"
#include "Systems/moving_system.h"
#include "Systems/event_system.h"

#include "Entitys/game_object.h"
#include "Entitys/player_entity.h"

int main()
{
	if(create_drawing_system(640, 480))
	{
		printf("drawing system has been created");
	}

	player_t player;
	player.position.x = 0;
	player.position.y = 0;
	player.texture = texture_comp_create("texture.png", 32, 32);

	game_object_t enemy;
	enemy.position.x = 630 / 2;
	enemy.position.y = 470 / 2;

	init_moving_sustem();

	list_t* drawing = l_create();
	list_t* moving = l_create();
	list_t* ai = l_create();
	position_comp_t* collision[10] = {0};

	l_push(drawing,(void *)&player.position);
	l_push(drawing,(void *)&enemy.position);

	l_push(moving, (void *) &enemy.position);

	l_push(ai,(void *)&enemy.position);

	collision[0] = &player.position;
	collision[1] = &enemy.position;

	uint32_t prev_time = 0;
	while(1){
		uint32_t current_time;
		if(event_system(&current_time)) {
			break;
		}

		moving_system(moving);
		if (current_time - prev_time > 15)
		{
			ai_system(ai);
			collision_system(collision);
			drawing_system_process(drawing);
			prev_time = current_time;
		}
	}
	destroy_drawing_system();
}
