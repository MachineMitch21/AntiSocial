#include "vector2.h"

#include <math.h>

using as_math::Vector2;

Vector2::Vector2(float _x, float _y)
	: x(_x), y(_y)
{

}

Vector2::~Vector2() {

}

float Vector2::magnitude() {
	return sqrt((x * x) + (y * y));
}

float Vector2::dot_product(Vector2& v) {
	return (x * v.x) + (y * v.y);
}

float Vector2::operator*(Vector2& v) {
	return dot_product(v);
}

Vector2 Vector2::operator+(const Vector2& v) {
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) {
	return Vector2(x - v.x, y - v.y);
}
