#pragma once
#include <stdint.h>

#include <Entitys/entity.h>

void collision_system();
void collision_sys_add_item(entity *en);
uint32_t init_collision_sustem(uint32_t max);
void destroy_collison_system();
