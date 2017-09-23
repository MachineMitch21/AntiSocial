#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

using std::ostream;

namespace as_math {
	class Vector2
	{
	public:
		Vector2(float _x, float _y);
		~Vector2();

		float magnitude();
		float dot_product(Vector2& v);

		float operator*(Vector2& v);
		Vector2 operator+(const Vector2& v);
		Vector2 operator-(const Vector2& v);

		friend ostream& operator<<(ostream& os, const Vector2& v) {
			return os << "(" << v.x << ", " << v.y << ")";
		}

	private:
		float x = 0, y = 0;

	protected:

	};
}


#endif
