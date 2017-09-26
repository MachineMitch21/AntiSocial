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

		friend Matrix4 ortho(float left, float right, float bottom, float top, float near, float far);
		friend Matrix4 perspective(float fov, float apectRatio, float near, float far);

		friend Matrix4 lookAt(Vector3& viewPos, Vector3& objPos, Vector3& up);

		friend Matrix4 translate(Vector3& translation);
		friend Matrix4 rotate(float angle, const Vector3& axis);
		friend Matrix4 scale(const Vector3& scale);

		friend Matrix4 operator*(Matrix4 left, const Matrix4& right);
		Matrix4& operator*=(const Matrix4& other);
		
	private:
		float _elements[16];
	};
	
	Matrix4 ortho(float left, float right, float bottom, float top, float near, float far);
	Matrix4 perspective(float fov, float apectRatio, float near, float far);

	Matrix4 lookAt(Vector3& viewPos, Vector3& objPos, Vector3& up);

	Matrix4 translate(Vector3& translation);
	Matrix4 rotate(float angle, const Vector3& axis);
	Matrix4 scale(const Vector3& scale);
	Matrix4 operator*(Matrix4 left, Matrix4& right);

}



#endif //__MATRIX4_H__
