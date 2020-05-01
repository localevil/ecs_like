#pragma once
#include <SDL2/SDL.h>
#include "Components/position_component.h"

typedef struct game_object {
	position_comp_t position;
} game_object_t;
