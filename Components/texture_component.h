#pragma once
#include <stdint.h>
#include "Systems/drawing_system.h"

typedef struct texture_comp {
	uint32_t width;
	uint32_t height;
	void *texture;
}texture_comp_t;
