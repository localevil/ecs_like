#include "moving_system.h"
#include <SDL2/SDL.h>

#include "Components/position_component.h"

const uint8_t *keys;

static void moving_func(void *elm) {
	static uint32_t moving_last_time = 0;
	uint32_t current_time = SDL_GetTicks();
	if (current_time > moving_last_time + 15)
	{
		position_comp_t *pos = (position_comp_t *)elm;
		if (pos)
		{
			if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
			{
				pos->x--;
			}
			if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
			{
				pos->x++;
			}
			if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W])
			{
				pos->y--;
			}
			if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S])
			{
				pos->y++;
			}
			moving_last_time = current_time;
		}
	}
}

void init_moving_sustem()
{
	keys = SDL_GetKeyboardState(NULL);
}

void moving_system(list_t *moving_list)
{
	l_for_each(moving_list, moving_func);
}

//bool moving_compare(void *data1, void *data2) {
//	moving_struct_t *ob1 = (moving_struct_t *)data1;
//	moving_struct_t *ob2 = (moving_struct_t *)data2;
//	if (ob1->elm->id == ob2->elm->id)
//		return true;
//	return false;
//}
