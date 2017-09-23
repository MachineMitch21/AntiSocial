#include "vector4.h"

#include <math.h>

using as_math::Vector4;

Vector4::Vector4(float _x, float _y, float _z, float _w)
	: x(_x), y(_y), z(_z), w(_w)
{

}

Vector4::~Vector4() {

}

float Vector4::magnitude() {
	return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

float Vector4::dot_product(Vector4& v) {
	return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
}

float Vector4::operator*(Vector4& v) {
	return dot_product(v);
}

Vector4 Vector4::operator+(const Vector4& v) {
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4 Vector4::operator-(const Vector4& v) {
	return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}
