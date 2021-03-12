#include "collision_system.h"

#include <stdbool.h>
#include <math.h>
#include <stdio.h>

static bool check_collision(position_comp_t *go1, position_comp_t *go2)
{
	vector2f obj1_half_size = vector2f_divide_scalar(go1->size, 2);
	vector2f obj1_center = vector2f_subtract(go1->pos, obj1_half_size);
	vector2f obj2_half_size = vector2f_divide_scalar(go2->size, 2);
	vector2f obj2_center = vector2f_subtract(go2->pos, obj2_half_size);

	if ((fabs(obj1_center.x - obj2_center.x) > obj1_half_size.x + obj2_half_size.x) ||
		(fabs(obj1_center.y - obj2_center.y) > obj1_half_size.y + obj2_half_size.y))
		return false;
	return true;
}

void collision_system(component **arr)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (arr[i] != NULL && (arr[i]->type == COMP_TYPE_POS)
				&& arr[j] != NULL && (arr[j]->type == COMP_TYPE_POS))
			{
				if(check_collision(&arr[i]->pos_comp, &arr[j]->pos_comp)) {
					printf("collision detected\n");
				}
			}
		}
	}
}
