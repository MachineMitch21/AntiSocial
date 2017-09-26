#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "vector3.h"

namespace antisocial {

	class Matrix4 {

	public:
		Matrix4();
		Matrix4(float diagonal);		

		~Matrix4();

		static Matrix4 identity();
		Matrix4& multiply(const Matrix4& other);

		static Matrix4 ortho(float left, float right, float bottom, float top, float near, float far);
		static Matrix4 perspective(float fov, float apectRatio, float near, float far);

		static Matrix4 translation(const antisocial::Vector3& translation);
		static Matrix4 rotation(float angle, const antisocial::Vector3& axis);
		static Matrix4 scale(const antisocial::Vector3& scale);

		friend Matrix4 operator*(Matrix4 left, const Matrix4& right);
		Matrix4& operator*=(const Matrix4& other);
		
	private:
		float _elements[16];
	};

}



#endif //__MATRIX4_H__
