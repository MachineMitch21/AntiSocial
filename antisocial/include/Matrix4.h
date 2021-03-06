#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include <AntisocialDLL.h>

#include <Vector3.h>
#include <vector>
#include <cmath>

using antisocial::Vector3;

#define PI  3.14159265358979323846

namespace antisocial {

	float radians(float degrees)
	{
		return degrees * (PI / 180.0f);
	}

	class ANTISOCIAL_API Matrix4 {

	public:
		Matrix4();
		Matrix4(float diagonal);

		~Matrix4();

		inline const float* getElements() const { return _elements; }

		static Matrix4 identity();

		Matrix4& multiply(const Matrix4& other);
		void toString();

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
