#include "vector2d.h"
#include <math.h>

vector2d_t vector2d_add(vector2d_t v1, vector2d_t v2)
{
	vector2d_t v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return v;
}
vector2d_t vector2d_subtract(vector2d_t v1, vector2d_t v2)
{
	vector2d_t v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	return v;
}
vector2d_t vector2d_multiply(vector2d_t v1, vector2d_t v2)
{
	vector2d_t v;
	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	return v;
}
vector2d_t vector2d_divide(vector2d_t v1, vector2d_t v2)
{
	vector2d_t v;
	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	return v;
}

vector2d_t vector2d_normalize(vector2d_t v)
{
	if (v.x == 0 && v.y == 0)
		return v;
	float inv_length = 1.f / sqrt(pow(v.x,2) + pow(v.y,2));
	vector2d_t newV = {v.x * inv_length, v.y * inv_length};
	return newV;
}
