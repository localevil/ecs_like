#include "collision_system.h"

static void check_collision(position_comp_t *go1, position_comp_t *go2)
{
	//todo drawing component
	if (go1->x < go2->x + 10 &&
		go1->x + 10 > go2->x)
		go1->x = -1;
	if (go1->y < go2->y + 10 &&
		go1->y + 10 > go2->y)
		go1->y = -1;
}

void collision_system(position_comp_t **arr)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (arr[i] && arr[j])
			{
				position_comp_t *go1 = (position_comp_t*)arr[i];
				position_comp_t *go2 = (position_comp_t*)arr[j];
				check_collision(go1, go2);
			}
		}
	}
}
