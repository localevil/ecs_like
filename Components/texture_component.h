#pragma once
#include <stdint.h>
#include "Systems/drawing_system.h"

typedef struct texture_comp {
	uint32_t width;
	uint32_t height;
	void *texture;
}texture_comp_t;


texture_comp_t texture_comp_create(const char* path,
									uint32_t width, uint32_t height) {
	texture_comp_t tmp;
	tmp.width = width;
	tmp.height = height;
	tmp.texture = drawing_sys_add_texture(path);
	return tmp;
}
