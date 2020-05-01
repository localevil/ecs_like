#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "List/list.h"
#include "Systems/ai_system.h"
#include "Systems/drawing_system.h"
#include "Systems/collision_system.h"
#include "Systems/moving_system.h"
#include "Entitys/game_object.h"

int main()
{
	game_object_t player;
	player.position.x = 0;
	player.position.y = 0;

	game_object_t enemy;
	enemy.position.x = 630 / 2;
	enemy.position.y = 470 / 2;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_CreateWindowAndRenderer(640, 480, 0, &win, &ren);

	const uint8_t *keys = SDL_GetKeyboardState(NULL);

	list_t* drawing = l_create();
	list_t* moving = l_create();
	list_t* ai = l_create();
	position_comp_t* collision[10] = {0};

	draw_struct_t player_drawing = {ren, &player.position};
	draw_struct_t enemy_drawing = {ren, &enemy.position};
	l_push(drawing,(void *)&player_drawing);
	l_push(drawing,(void *)&enemy_drawing);

	moving_struct_t moving_player = {keys, &player.position};
	l_push(moving, (void *) &moving_player);

	l_push(ai,(void *)&enemy.position);

	collision[0] = &player.position;
	collision[1] = &enemy.position;

	bool running = true;
	uint32_t drawing_last_time = 0, ai_last_time = 0;
	while(running){
		static SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			}
		}
		moving_system(moving);
		uint32_t current_time = SDL_GetTicks();
		if (current_time > ai_last_time + 15)
		{
			ai_system(ai);
			ai_last_time = current_time;
		}

		if (current_time > drawing_last_time + 16)
		{
			collision_system(collision);
			drawing_system(drawing, ren);
			drawing_last_time = current_time;
		}
	}
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
}
