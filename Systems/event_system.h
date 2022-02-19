#pragma once
#include <stdint.h>

#include <Entitys/entity.h>

uint32_t init_event_sustem();
int8_t event_system(uint32_t *current_time);
void event_sys_add_item(entity *en);
void destroy_event_system();
