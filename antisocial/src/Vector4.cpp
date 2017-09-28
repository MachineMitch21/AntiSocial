#include <Vector4.h>

#include <math.h>

using as_math::Vector4;

Vector4::Vector4(float x, float y, float z, float w)
	: _x(x), _y(y), _z(z), _w(w)
{

}

Vector4::~Vector4() {

}

float Vector4::magnitude() {
	return sqrt((_x * _x) + (_y * _y) + (_z * _z) + (_w * _w));
}

float Vector4::dot_product(const Vector4& v) {
	return (_x * v._x) + (_y * v._y) + (_z * v._z) + (_w * v._w);
}

float Vector4::operator*(const Vector4& v) {
	return dot_product(v);
}

Vector4 Vector4::add(const Vector4& v) {
	return Vector4(_x + v._x, _y + v._y, _z + v._z, _w + v._w);
}

Vector4 Vector4::subtract(const Vector4& v) {
	return Vector4(_x - v._x, _y - v._y, _z - v._z, _w - v._w);
}

Vector4 Vector4::operator+(const Vector4& v) {
	return add(v);
}

Vector4 Vector4::operator-(const Vector4& v) {
	return subtract(v);
}
