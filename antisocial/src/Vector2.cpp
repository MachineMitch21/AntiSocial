#include <Vector2.h>

#include <math.h>

using antisocial::Vector2;

Vector2::Vector2(float x, float y)
	: _x(x), _y(y)
{

}

Vector2::~Vector2() {

}

float Vector2::magnitude() {
	return sqrt((_x * _x) + (_y * _y));
}

float Vector2::dot_product(const Vector2& v) {
	return (_x * v._x) + (_y * v._y);
}

Vector2 Vector2::add(const Vector2& v) {
	return Vector2(_x + v._x, _y + v._y);
}

Vector2 Vector2::subtract(const Vector2& v) {
	return Vector2(_x - v._x, _y - v._y);
}

float Vector2::operator*(const Vector2& v) {
	return dot_product(v);
}

Vector2 Vector2::operator+(const Vector2& v) {
	return add(v);
}

Vector2 Vector2::operator-(const Vector2& v) {
	return subtract(v);
}
