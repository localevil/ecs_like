#include "vector2f.h"
#include <math.h>

vector2f vector2f_add(vector2f v1, vector2f v2)
{
	vector2f v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return v;
}
vector2f vector2f_subtract(vector2f v1, vector2f v2)
{
	vector2f v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	return v;
}
vector2f vector2f_multiply(vector2f v1, vector2f v2)
{
	vector2f v;
	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	return v;
}
vector2f vector2f_divide(vector2f v1, vector2f v2)
{
	vector2f v;
	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	return v;
}

vector2f vector2f_divide_scalar(vector2f v1, float div) {
	vector2f v;
	v.x = v1.x / div;
	v.y = v1.y / div;
	return v;
}

vector2f vector2f_normalize(vector2f v)
{
	if (v.x == 0 && v.y == 0)
		return v;
	float inv_length = 1.f / sqrt(pow(v.x,2) + pow(v.y,2));
	vector2f newV = {v.x * inv_length, v.y * inv_length};
	return newV;
}
