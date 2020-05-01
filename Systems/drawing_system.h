#pragma once
#include <SDL2/SDL.h>
#include "List/list.h"
#include <Components/position_component.h>

typedef struct draw_struct {
	SDL_Renderer * ren;
	position_comp_t *elm;
} draw_struct_t;

void drawing_system(list_t *draw_list, SDL_Renderer *ren);
