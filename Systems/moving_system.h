#pragma once
#include <stdint.h>

#include <Entitys/entity.h>

uint32_t init_moving_sustem();
void moving_system(float delta);
void moving_sys_add_item(entity *en);
void destroy_moving_system();
