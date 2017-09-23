#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

using std::ostream;

namespace as_math {

	class Vector3
	{
	public:
		Vector3(float _x, float _y, float _z);
		~Vector3();

		float magnitude();
		Vector3 cross_product(Vector3& v);
		float dot_product(Vector3& v);

		float operator*(Vector3& v);
		Vector3 operator*(const float& scalar);
		Vector3 operator+(const Vector3& v);
		Vector3 operator-(const Vector3& v);
		
		friend ostream& operator<<(ostream& os, const Vector3& v) {
			return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		}

	private:
		float x = 0, y = 0, z = 0;
	protected:

	};
}

#endif
