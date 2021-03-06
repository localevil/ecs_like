#pragma once
#include "List/list.h"
#include <stdint.h>
#include "Components/position_component.h"

typedef struct moving_struct {
	const uint8_t *keys;
	position_comp_t *elm;
}moving_struct_t;

void moving_system(list_t *moving_list);

bool moving_compare(void *data1, void *data2);
