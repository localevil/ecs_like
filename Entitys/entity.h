#pragma once

#include "Components/component.h"
#include "List/list.h"

typedef struct {
	const char *name;
	list_t *components;
} entity;
