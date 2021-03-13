#pragma once
#include <Vector2D/vector2f.h>

typedef struct {
	vec2f pos;
	vec2f texture_size;
	vec2f draw_size;
	void *texture;
}texture_comp_t;
