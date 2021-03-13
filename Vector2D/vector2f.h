#pragma once

typedef struct {
	float x;
	float y;
}vec2f;

vec2f vec2f_add(vec2f, vec2f);
vec2f vec2f_subtract(vec2f, vec2f);
vec2f vec2f_multiply(vec2f, vec2f);
vec2f vec2f_multiply_scalar(vec2f, float);
vec2f vec2f_divide(vec2f, vec2f);
vec2f vec2f_divide_scalar(vec2f, float);
vec2f vec2f_normalize(vec2f v);
vec2f vec2f_abs(vec2f in_v);
float vec2f_module(vec2f in_v);
float vec2f_dot(vec2f v1, vec2f v2);
