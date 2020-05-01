#include "moving_system.h"
#include <SDL2/SDL.h>

static void moving_func(void *elm) {
	static uint32_t moving_last_time = 0;
	uint32_t current_time = SDL_GetTicks();
	if (current_time > moving_last_time + 15)
	{
		moving_struct_t *move = (moving_struct_t *)elm;
		if (move->elm)
		{
			position_comp_t *p = move->elm;
			if (move->keys[SDL_SCANCODE_LEFT] || move->keys[SDL_SCANCODE_A])
			{
				p->x--;
			}
			if (move->keys[SDL_SCANCODE_RIGHT] || move->keys[SDL_SCANCODE_D])
			{
				p->x++;
			}
			if (move->keys[SDL_SCANCODE_UP] || move->keys[SDL_SCANCODE_W])
			{
				p->y--;
			}
			if (move->keys[SDL_SCANCODE_DOWN] || move->keys[SDL_SCANCODE_S])
			{
				p->y++;
			}
			moving_last_time = current_time;
		}
	}
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
