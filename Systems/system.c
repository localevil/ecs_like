#include "system.h"

component_type type;

bool find_comp(void *data) {
	component *comp = (component*)data;
	return comp && comp->type == type;
}
