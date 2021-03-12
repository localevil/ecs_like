#pragma once

typedef struct {
	float x;
	float y;
}vector2f;

vector2f vector2f_add(vector2f, vector2f);
vector2f vector2f_subtract(vector2f, vector2f);
vector2f vector2f_multiply(vector2f, vector2f);
vector2f vector2f_divide(vector2f, vector2f);
vector2f vector2f_divide_scalar(vector2f, float);
vector2f vector2f_normalize(vector2f v);
