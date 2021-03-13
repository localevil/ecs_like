#include "vector2f.h"
#include <math.h>

vec2f vec2f_add(vec2f v1, vec2f v2) {
	vec2f v = {v1.x + v2.x, v1.y + v2.y};
	return v;
}

vec2f vec2f_subtract(vec2f v1, vec2f v2) {
	vec2f v = {v1.x - v2.x, v1.y - v2.y};
	return v;
}

vec2f vec2f_multiply(vec2f v1, vec2f v2) {
	vec2f v = {v1.x * v2.x, v1.y * v2.y};
	return v;
}

vec2f vec2f_multiply_scalar(vec2f in_v, float sc) {
	vec2f v = {in_v.x * sc, in_v.y * sc};
	return v;
}

vec2f vec2f_divide(vec2f v1, vec2f v2) {
	vec2f v = {v1.x / v2.x, v1.y / v2.y};
	return v;
}

vec2f vec2f_divide_scalar(vec2f in_v, float sc) {
	vec2f v = {in_v.x / sc, in_v.y / sc};
	return v;
}

vec2f vec2f_normalize(vec2f in_v) {
	if (in_v.x == 0 && in_v.y == 0)
		return in_v;
	float inv_length = 1.f / sqrt(pow(in_v.x,2) + pow(in_v.y,2));
	vec2f newV = {in_v.x * inv_length, in_v.y * inv_length};
	return newV;
}

vec2f vec2f_abs(vec2f in_v) {
	vec2f newV = {fabsf(in_v.x), fabsf(in_v.y)};
	return newV;
}

float vec2f_module(vec2f in_v) {
	return sqrt(pow(in_v.x,2) + pow(in_v.y,2));
}

float vec2f_dot(vec2f v1, vec2f v2) {
	return v1.x * v2.x + v1.y * v2.y;
}
