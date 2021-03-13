#pragma once

#include "Vector2D/vector2f.h"

typedef enum {
	PHYSIC_TYPE_STATIC,
	PHYSIC_TYPE_DYNAMIC
}physic_type;

typedef struct {
	physic_type type;
	vec2f halfSize;
	vec2f speed;
}physics_comp_t;
