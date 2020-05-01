#include "drawing_system.h"

static void drawing_func(void *elm){
	draw_struct_t *draw = (draw_struct_t *)elm;
	if (draw->elm)
	{
		SDL_Rect to_draw;
		to_draw.x = draw->elm->x;
		to_draw.y = draw->elm->y;
		//todo drawing component
		to_draw.w = 10;
		to_draw.h = 10;
		SDL_RenderFillRect(draw->ren, &to_draw);
	}
}

void drawing_system(list_t *draw_list, SDL_Renderer *ren)
{
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 255,255,255, 0);
	l_for_each(draw_list, drawing_func);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_RenderPresent(ren);
}
