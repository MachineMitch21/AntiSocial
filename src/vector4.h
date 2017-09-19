#ifndef VECTOR4_H
#define VECTOR4_H

#include <iostream>

using std::ostream;

namespace as_math {
	class Vector4
	{
	public:
		Vector4(float _x, float _y, float _z, float _w);

		~Vector4();

		float magnitude();
		float dot_product(Vector4& v);

		float operator*(Vector4& v);
		Vector4 operator+(const Vector4& v);
		Vector4 operator-(const Vector4& v);

		friend ostream& operator<<(ostream& os, const Vector4& v) {
			return os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
		}

	private:
		float x = 0, y = 0, z = 0, w = 0;

	protected:
	};
}

#endif
