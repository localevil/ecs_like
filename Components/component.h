#pragma once

#include "Components/position_component.h"
#include "Components/texture_component.h"

typedef enum {
	COMP_TYPE_POS,
	COMP_TYPE_TEXTURE
} component_type;

typedef struct {
	component_type type;
	union {
		position_comp_t pos_comp;
		texture_comp_t texture_comp;
	};
} component;
