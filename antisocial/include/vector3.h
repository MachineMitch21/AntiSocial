#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

using std::ostream;

namespace as_math {

	class Vector3
	{
	public:
		Vector3(float x, float y, float z);
		~Vector3();

		float magnitude();
		Vector3 cross_product(const Vector3& v);
		float dot_product(const Vector3& v);
		Vector3 add(const Vector3& v);
		Vector3 subtract(const Vector3& v);

		float operator*(const Vector3& v);
		Vector3 operator*(const float& scalar);
		Vector3 operator+(const Vector3& v);
		Vector3 operator-(const Vector3& v);
		
		friend ostream& operator<<(ostream& os, const Vector3& v) {
			return os << "(" << v._x << ", " << v._y << ", " << v._z << ")";
		}

	private:
		float _x = 0, _y = 0, _z = 0;
	protected:

	};
}

#endif
