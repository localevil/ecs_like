#include "drawing_system.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "system.h"
#include <List/list.h>

typedef struct {
	texture_comp_t *texture_comp;
	position_comp_t *pos_comp;
}drawing_node;

typedef struct {
	const char *path;
	SDL_Texture *texture;
} texture_node;

typedef struct {
   SDL_Renderer *ren;
   SDL_Window *win;
   list_t *items;
   list_t *textures;
} drawing_system_t;

static drawing_system_t draw_sys;

static void drawing_func(void *elm) {
	drawing_node *node = (drawing_node *)elm;
	if (node == NULL) 
		return;

	SDL_Rect draw_rect;
	vec2f left_top =
			vec2f_subtract(node->pos_comp->center,
							vec2f_divide_scalar(node->texture_comp->draw_size, 2));
	draw_rect.x = left_top.x;
	draw_rect.y = left_top.y;
	//todo drawing component
	draw_rect.w = node->texture_comp->draw_size.x;
	draw_rect.h = node->texture_comp->draw_size.y;
	if (node->texture_comp->texture == NULL) {
		SDL_RenderFillRect(draw_sys.ren, &draw_rect);
		return;
	}
	SDL_Rect texture_rect;
	texture_rect.x = node->texture_comp->pos.x;
	texture_rect.y = node->texture_comp->pos.y;
	texture_rect.w = node->texture_comp->texture_size.x;
	texture_rect.h = node->texture_comp->texture_size.y;

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if(node->pos_comp->flip) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	SDL_RenderCopyEx(draw_sys.ren,
						(SDL_Texture*)node->texture_comp->texture,
						&texture_rect, &draw_rect, 0., NULL, flip);
}

void drawing_system() {
	SDL_RenderClear(draw_sys.ren);
	SDL_SetRenderDrawColor(draw_sys.ren, 255,255,255, 0);
	l_for_each(draw_sys.items, drawing_func);
	SDL_SetRenderDrawColor(draw_sys.ren, 0, 0, 0, 0);
	SDL_RenderPresent(draw_sys.ren);
}

static const char* _path;

static bool find_texture(void *data) {
	texture_node *text_node = (texture_node*)data;
	return text_node && !strcmp(text_node->path, _path);
}

void* drawing_sys_add_texture(const char *path) {
	_path = path;
	texture_node* node = (texture_node*) l_find(draw_sys.textures, find_texture);
	if (!node) {
		SDL_Texture *texture = IMG_LoadTexture(draw_sys.ren, path);
		if (!texture) {
			printf("Texture: %s not loaded\n", path);
			return NULL;
		}
		node = (texture_node*)malloc(sizeof(texture_node));
		node->path = path;
		node->texture = texture;
		l_push(draw_sys.textures, (void*)node);
	}
	return (void*) node->texture;
}

uint32_t init_drawing_system(uint32_t w, uint32_t h) {
	int32_t res = SDL_Init(SDL_INIT_VIDEO);
	if (res) {
		return 2;
	}
	draw_sys.win = SDL_CreateWindow("Game", 0, 0, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);
	if (draw_sys.win == NULL) {
		return 3;
	}
	draw_sys.ren = SDL_CreateRenderer(draw_sys.win, 0,  SDL_RENDERER_ACCELERATED);
	if (draw_sys.ren == NULL) {
		return 4;
	}

	draw_sys.items = l_create();
	draw_sys.textures = l_create();
	return 0;
}

void drawing_sys_add_item(entity *en) {
	type = COMP_TYPE_POS;
	component *pos = (component*)l_find(en->components, find_comp);
	if(!pos) {
		printf("Entity %s not have position component", en->name);
		return;
	}
	type = COMP_TYPE_TEXTURE;
	component *texture = (component*)l_find(en->components, find_comp);
	if(!texture) {
		printf("Entity %s not have texture component", en->name);
		return;
	}
	drawing_node *node = (drawing_node*)malloc(sizeof (drawing_node));
	node->texture_comp = &texture->texture_comp;
	node->pos_comp = &pos->pos_comp;
	l_push(draw_sys.items,(void *)node);
}

static void delete_items(void *elm) {
	if(elm) {
		texture_node* node = (texture_node*)elm;
		SDL_DestroyTexture(node->texture);
		free(node);
	}
}

static void delete_textures(void *elm) {
	if(elm) SDL_DestroyTexture(elm);
}

void destroy_drawing_system() {
	l_for_each(draw_sys.items, delete_items);
	l_for_each(draw_sys.textures, delete_textures);
	free(draw_sys.items);
	SDL_DestroyRenderer(draw_sys.ren);
	SDL_DestroyWindow(draw_sys.win);
	SDL_Quit();
}
