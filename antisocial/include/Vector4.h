#ifndef VECTOR4_H
#define VECTOR4_H

#include <AntiSocialDLL.h>

#include <iostream>

using std::ostream;

namespace as_math {
	class ANTISOCIAL_API Vector4
	{
	public:
		Vector4(float x, float y, float z, float w);

		~Vector4();

		float magnitude();
		float dot_product(const Vector4& v);
		Vector4 add(const Vector4& v);
		Vector4 subtract(const Vector4& v);

		float operator*(const Vector4& v);
		Vector4 operator+(const Vector4& v);
		Vector4 operator-(const Vector4& v);

		friend ostream& operator<<(ostream& os, const Vector4& v) {
			return os << "(" << v._x << ", " << v._y << ", " << v._z << ", " << v._w << ")";
		}

	public:
		float _x = 0, _y = 0, _z = 0, _w = 0;

	protected:
	};
}

#endif
