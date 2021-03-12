#pragma once
#include "Vector2D/vector2f.h"
#include "stdbool.h"

typedef struct {
	vector2f pos;
	vector2f size;
	bool on_floor;
}position_comp_t;
