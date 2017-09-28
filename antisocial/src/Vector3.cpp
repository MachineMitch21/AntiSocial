#include <Vector3.h>
#include <math.h>

using antisocial::Vector3;

Vector3::Vector3(float x, float y, float z)
	: _x(x), _y(y), _z(z)
{

}

Vector3::~Vector3() {

}

float Vector3::magnitude() {
	return sqrt((_x * _x) + (_y * _y) + (_z * _z));
}

Vector3 Vector3::cross_product(const Vector3& v) {
	return Vector3(	(_y * v._z) - (_z * v._y),
					(_z * v._x) - (_x * v._z),
					(_x * v._y) - (_y * v._x)	);
}

float Vector3::dot_product(const Vector3& v) {
	return (_x * v._x) + (_y * v._y) + (_z * v._z);
}

Vector3 Vector3::normalize()
{
	float length = magnitude();
	return Vector3(_x / length, _y / length, _z / length);
}

Vector3 Vector3::add(const Vector3& v) {
	return Vector3(_x + v._x, _y + v._y, _z + v._z);
}
		
Vector3 Vector3::subtract(const Vector3& v) {
	return Vector3(_x - v._x, _y - v._y, _z - v._z);
}


float Vector3::operator*(const Vector3& v) {
	return dot_product(v);
}

Vector3 Vector3::operator*(const float& scalar) {
	return Vector3(_x * scalar, _y * scalar, _z * scalar);
}

Vector3 Vector3::operator+(const Vector3& v) {
	return add(v);
}

Vector3 Vector3::operator-(const Vector3& v) {
	return subtract(v);
}
