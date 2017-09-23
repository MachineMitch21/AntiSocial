#include "vector3.h"
#include <math.h>

using as_math::Vector3;

Vector3::Vector3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{

}

Vector3::~Vector3() {

}

float Vector3::magnitude() {
	return sqrt((x * x) + (y * y) + (z * z));
}

Vector3 Vector3::cross_product(Vector3& v) {
	return Vector3(	(y * v.z) - (z * v.y),
					(z * v.x) - (x * v.z),
					(x * v.y) - (y * v.x)	);
}

float Vector3::dot_product(Vector3& v) {
	return (x * v.x) + (y * v.y) + (z * v.z);
}

float Vector3::operator*(Vector3& v) {
	return dot_product(v);
}

Vector3 Vector3::operator*(const float& scalar) {
	return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator+(const Vector3& v) {
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) {
	return Vector3(x - v.x, y - v.y, z - v.z);
}
