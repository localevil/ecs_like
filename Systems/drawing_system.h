#pragma once
#include <stdint.h>

#include "List/list.h"


typedef struct drawing_system drawing_system_t;

void drawing_system_process(list_t *draw_list);
void* drawing_sys_add_texture( const char *path);
uint32_t init_drawing_system(uint32_t w, uint32_t h);
void destroy_drawing_system();
