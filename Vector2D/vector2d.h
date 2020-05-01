#pragma once

typedef struct vector2d {
	float x;
	float y;
}vector2d_t;

vector2d_t vector2d_add(vector2d_t, vector2d_t);
vector2d_t vector2d_subtract(vector2d_t, vector2d_t);
vector2d_t vector2d_multiply(vector2d_t, vector2d_t);
vector2d_t vector2d_divide(vector2d_t, vector2d_t);
vector2d_t vector2d_normalize(vector2d_t v);
