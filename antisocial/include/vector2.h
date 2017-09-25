#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

using std::ostream;

namespace antisocial {

	class Vector2
	{
	public:
		Vector2(float x, float y);
		~Vector2();

		float magnitude();
		float dot_product(const Vector2& v);
		Vector2 add(const Vector2& v);
		Vector2 subtract(const Vector2& v);

		float operator*(const Vector2& v);
		Vector2 operator+(const Vector2& v);
		Vector2 operator-(const Vector2& v);

		friend ostream& operator<<(ostream& os, const Vector2& v) {
			return os << "(" << v._x << ", " << v._y << ")";
		}

	private:
		float _x = 0, _y = 0;

	protected:

	};
}


#endif
