#include "event_system.h"
#include <SDL2/SDL.h>
#include <string.h>

#include "system.h"

typedef struct {
	const char* name;
	position_comp_t* pos_comp;
} event_node;

typedef struct  {
	const uint8_t *keys;
	list_t *items;
} event_system_t;

static event_system_t event_sys;

static char* name = NULL;

static bool f_find(void *data) {
	event_node *node = (event_node*)data;
	return !strcmp(node->name, name);
}

int8_t event_system(uint32_t *current_time) {
	static SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return 1;
		}
	}

	vec2f duration = {0,0};
	if (event_sys.keys[SDL_SCANCODE_LEFT] || event_sys.keys[SDL_SCANCODE_A])
	{
		duration.x -= 1;
	}
	if (event_sys.keys[SDL_SCANCODE_RIGHT] || event_sys.keys[SDL_SCANCODE_D])
	{
		duration.x += 1;
	}
	if (event_sys.keys[SDL_SCANCODE_UP] || event_sys.keys[SDL_SCANCODE_W])
	{
		duration.y -= 1;
	}
	if (event_sys.keys[SDL_SCANCODE_DOWN] || event_sys.keys[SDL_SCANCODE_S])
	{
		duration.y += 1;
	}

	if(duration.x != 0 || duration.y != 0)  {
		name = "Player";
		event_node *node = (event_node*)l_find(event_sys.items, f_find);
		if(node)
			node->pos_comp->duration = vec2f_normalize(duration);
	}

	*current_time = SDL_GetTicks();
	return 0;
}

uint32_t init_event_sustem() {
	event_sys.keys = SDL_GetKeyboardState(NULL);
	event_sys.items = l_create();
	return 0;
}

void event_sys_add_item(entity *en) {
	type = COMP_TYPE_POS;
	component *pos = (component*)l_find(en->components, find_comp);
	if(!pos) {
		printf("Entity %s not have position component", en->name);
		return;
	}
	event_node *node = (event_node*)malloc(sizeof (event_node));
	node->name = en->name;
	node->pos_comp = &pos->pos_comp;
	l_push(event_sys.items,(void *)node);
}

static void delete_items(void *elm) {
	if(elm) free(elm);
}

void destroy_event_system() {
	l_for_each(event_sys.items, delete_items);
	l_delete(event_sys.items);
}
