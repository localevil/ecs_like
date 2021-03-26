#pragma once

#include <stdint.h>

#include <Entitys/entity.h>

void ai_system(float delta);
void ai_sys_add_item(entity *en);
uint32_t init_ai_system();
void destroy_ai_system();
