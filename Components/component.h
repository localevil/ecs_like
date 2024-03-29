#pragma once

#include "position_component.h"
#include "texture_component.h"
#include "physics_component.h"
#include "transform_component.h"

typedef enum {
	COMP_TYPE_POS = 1,
	COMP_TYPE_TEXTURE,
	COMP_TYPE_PHYSICS,
	COMP_TYPE_TRANSFORM
} component_type;

typedef struct {
	component_type type;
	union {
		position_comp_t pos_comp;
		texture_comp_t texture_comp;
		physics_comp_t physics_comp;
		transform_comp_t transform_comp;
	};
} component;
