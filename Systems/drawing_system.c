#include "drawing_system.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Components/component.h>

struct drawing_system{
   SDL_Renderer *ren;
   SDL_Window *win;
   list_t *textures;
};

static drawing_system_t *draw_sys;

static void drawing_func(void *elm){
	component *pos = (component *)elm;
	if (pos != NULL && pos->type == COMP_TYPE_POS)
	{
		SDL_Rect to_draw;
		to_draw.x = pos->pos_comp.pos.x;
		to_draw.y = pos->pos_comp.pos.y;
		//todo drawing component
		to_draw.w = pos->pos_comp.size.x;
		to_draw.h = pos->pos_comp.size.y;
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
	if (!texture) {
		printf("Texture: %s not loaded\n", path);
		return NULL;
	}
		l_push(draw_sys->textures, texture);
	return texture;
}

uint32_t init_drawing_system(uint32_t w, uint32_t h)
{
	if (draw_sys) {
		return 1;
	}
	int32_t res = SDL_Init(SDL_INIT_VIDEO);
	if (res)
	{
		return 2;
	}
	draw_sys = malloc(sizeof(drawing_system_t));
	draw_sys->win = SDL_CreateWindow("Game", 0, 0, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);
	if (draw_sys->win == NULL) {
		free(draw_sys);
		return 3;
	}
	draw_sys->ren = SDL_CreateRenderer(draw_sys->win, 0,  SDL_RENDERER_ACCELERATED);
	if (draw_sys->ren == NULL) {
		free(draw_sys);
		return 4;
	}

	draw_sys->textures = l_create();
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
