#pragma once

#include <stdint.h>

#include "Entitys/entity.h"


void drawing_system();
void* drawing_sys_add_texture(const char *path);
uint32_t init_drawing_system(uint32_t w, uint32_t h);
void drawing_sys_add_item(entity *);
void destroy_drawing_system();
