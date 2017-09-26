#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "vector3.h"
#include <vector>
#include <math.h>

using antisocial::Vector3;

#define _USE_MATH_DEFINES_


namespace antisocial {

	float radians(float degrees)
	{
		return degrees * (M_PI / 180.0f);
	}

	class Matrix4 {

	public:
		Matrix4();
		Matrix4(float diagonal);		

		~Matrix4();


		static Matrix4 identity();

		Matrix4& multiply(const Matrix4& other);

		static Matrix4 ortho(float left, float right, float bottom, float top, float near, float far);
		static Matrix4 perspective(float fov, float apectRatio, float near, float far);

		static Matrix4 lookAt(Vector3 viewPos, Vector3 objPos, Vector3 up);

		static Matrix4 translate(Matrix4& mat, Vector3 translation);
		static Matrix4 rotate(Matrix4& mat, float angle, Vector3 axis);
		static Matrix4 scale(Matrix4& mat, Vector3 scale);

		friend Matrix4 operator*(Matrix4 left, const Matrix4& right);
		Matrix4& operator*=(const Matrix4& other);
		
	public:
		float _elements[16];
	};

	Matrix4 operator*(Matrix4 left, const Matrix4& right);
}



#endif //__MATRIX4_H__
