#include "drawing_system.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Components/position_component.h>

struct drawing_system{
   SDL_Renderer *ren;
   SDL_Window *win;
   list_t *textures;
};

static drawing_system_t *draw_sys;

static void drawing_func(void *elm){
	position_comp_t *pos = (position_comp_t *)elm;
	if (pos)
	{
		SDL_Rect to_draw;
		to_draw.x = pos->x;
		to_draw.y = pos->y;
		//todo drawing component
		to_draw.w = 10;
		to_draw.h = 10;
		SDL_RenderFillRect(draw_sys->ren, &to_draw);
	}
}

void drawing_system_process(list_t *draw_list)
{
	SDL_RenderClear(draw_sys->ren);
	SDL_SetRenderDrawColor(draw_sys->ren, 255,255,255, 0);
	l_for_each(draw_list, drawing_func);
	SDL_SetRenderDrawColor(draw_sys->ren, 0, 0, 0, 0);
	SDL_RenderPresent(draw_sys->ren);
}

void* drawing_sys_add_texture(const char *path)
{
	void *texture = (void*)IMG_LoadTexture(draw_sys->ren, path);
	l_push(draw_sys->textures, texture);
	return texture;
}

uint32_t create_drawing_system(uint32_t w, uint32_t h)
{
	if (draw_sys) {
		return 1;
	}
	drawing_system_t *d = {0};
	int32_t res = SDL_Init(SDL_INIT_VIDEO);
	if (res)
	{
		return 2;
	}
	res = SDL_CreateWindowAndRenderer(w, h, 0, &d->win, &d->ren);
	if (res)
	{
		return 3;
	}
	return 0;
}


void destroy_drawing_system()
{
	l_delete(draw_sys->textures);
	SDL_DestroyRenderer(draw_sys->ren);
	SDL_DestroyWindow(draw_sys->win);
	free(draw_sys);
	SDL_Quit();
}
