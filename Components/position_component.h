#pragma once
#include <stdbool.h>
#include <Vector2D/vector2f.h>

typedef struct {
	vec2f center;
	vec2f duration;
	bool flip;
}position_comp_t;
