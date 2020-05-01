#include "ai_system.h"
#include <stdlib.h>
#include "Components/position_component.h"
#include <stdint.h>
#include <time.h>

static void ai_func(void *elm)
{
	position_comp_t *p = (position_comp_t*)elm;
	srand(time(NULL));
	uint32_t duration_x = rand() % 3 - 1;
	uint32_t duration_y = rand() % 3 - 1;
	//todo drawing compoment with width and height
	if (p->x + duration_x > 0 && p->x + 10 + duration_x < 640)
		p->x += duration_x;
	if (p->y + duration_y > 0 && p->y + 10 + duration_y < 480)
		p->y += duration_y;
}

void ai_system(list_t *ai_list)
{
	l_for_each(ai_list, ai_func);
}

//bool ai_compare(void *data1, void *data2) {
//	SDL_Rect *ob1 = (SDL_Rect *)data1;
//	SDL_Rect *ob2 = (SDL_Rect *)data2;
//	if (ob1->id == ob2->id)
//		return true;
//	return false;
//}
