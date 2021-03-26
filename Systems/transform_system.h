#pragma once
#include <stdint.h>

#include <Entitys/entity.h>

void transform_system();
void transform_sys_add_item(entity *parent_en, entity *trans_en);
uint32_t init_transform_system();
void destroy_transform_system();
