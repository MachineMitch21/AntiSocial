
#include "matrix4.h"

using antisocial::Matrix4;


Matrix4::Matrix4()
{
	for (int i = 0; i < 4 * 4; i++)
	{
		_elements[i] = 0.0f;
	}
}

Matrix4::Matrix4(float diagonal)
{
	for (int i = 0; i < 4 * 4; i++)
	{
		_elements[i] = 0.0f;
	}

	_elements[0 + 0 * 4] = diagonal;
	_elements[1 + 1 * 4] = diagonal;
	_elements[2 + 2 * 4] = diagonal;
	_elements[3 + 3 * 4] = diagonal;
}

Matrix4 Matrix4::identity()
{
	return Matrix4(1.0f);
}

Matrix4& Matrix4::multiply(const Matrix4& other)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			float sum = 0.0f;

			for (int i = 0; i < 4; i++)
			{
				sum += _elements[x + i * 4] * other._elements[i + y * 4];
			}

			_elements[x + y * 4] = sum;
		}
	}

	return *this;
}

Matrix4 antisocial::operator*(Matrix4 left, const Matrix4& right)
{
	return left.multiply(right);
}

Matrix4& Matrix4::operator*=(const Matrix4& other)
{
	return multiply(other);
}

Matrix4 antisocial::ortho(float left, float right, float bottom, float top, float near, float far)
{
	Matrix4 result(1.0f);

	result._elements[0 + 0 * 4] = 2.0f / (right - left);
	result._elements[1 + 1 * 4] = 2.0f / (top - bottom);
	result._elements[2 + 2 * 4] = 2.0f / (near - far);

	result._elements[0 + 3 * 4] = 2.0f / (left + right) / (left - right);
	result._elements[1 + 3 * 4] = 2.0f / (bottom + top) / (bottom - top);
	result._elements[2 + 3 * 4] = 2.0f / (far + near) / (far - near);

	return result;
}

Matrix4 antisocial::perspective(float fov, float aspectRatio, float near, float far)
{
	Matrix4 result(1.0f);

	float q = 1.0f / tan(radians(0.5f * fov));
	float a = q / aspectRatio;
	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	result._elements[0 + 0 * 4] = a;
	result._elements[1 + 1 * 4] = q;
	result._elements[2 + 2 * 4] = b;
	result._elements[3 + 2 * 4] = -1.0f;
	result._elements[2 + 3 * 4] = c;

	return result;
}

Matrix4 antisocial::lookAt(Vector3& camPos, Vector3& objPos, Vector3& up)
{
	Matrix4 result(1.0f);

	Vector3 f = (objPos - camPos).normalize();
	Vector3 s = f.cross_product(up.normalize());
	Vector3 u = s.cross_product(f);

	result._elements[0 + 0 * 4] = s._x;
	result._elements[0 + 1 * 4] = s._y;
	result._elements[0 + 2 * 4] = s._z;

	result._elements[1 + 0 * 4] = u._x;
	result._elements[1 + 1 * 4] = u._y;
	result._elements[1 + 2 * 4] = u._z;

	result._elements[2 + 0 * 4] = -f._x;
	result._elements[2 + 1 * 4] = -f._y;
	result._elements[2 + 2 * 4] = -f._z;

	Vector3 translationVec(-camPos._x, -camPos._y, -camPos._z);

	result *= translate(translationVec);

	return result;
}

Matrix4 antisocial::translate(Vector3& translation)
{
	Matrix4 result(1.0f);

	result._elements[0 + 3 * 4] = translation._x;
	result._elements[1 + 3 * 4] = translation._y;
	result._elements[2 + 3 * 4] = translation._z;

	return result;
}

Matrix4 antisocial::rotate(float angle, const Vector3& axis)
{
	Matrix4 result(1.0f);

	float r = radians(angle);
	float c = cos(r);
	float s = sin(r);
	float omc = 1.0f - c;

	result._elements[0 + 0 * 4] = axis._x * omc + c;
	result._elements[1 + 0 * 4] = axis._y * axis._x * omc + axis._z * s;
	result._elements[2 + 0 * 4] = axis._x * axis._z * omc - axis._y * s;

	result._elements[0 + 1 * 4] = axis._x * axis._y * omc - axis._z * s;
	result._elements[1 + 1 * 4] = axis._y * omc + c;
	result._elements[2 + 1 * 4] = axis._y * axis._z * omc + axis._x * s;

	result._elements[0 + 0 * 4] = axis._x * axis._z * omc + axis._y * s;
	result._elements[1 + 0 * 4] = axis._y * axis._z * omc - axis._x * s;
	result._elements[2 + 0 * 4] = axis._x * axis._z * omc + axis._x * s;

	return result;
}

Matrix4 antisocial::scale(const Vector3& scale)
{
	Matrix4 result(1.0f);

	result._elements[0 + 0 * 4] = scale._x;
	result._elements[1 + 1 * 4] = scale._y;
	result._elements[2 + 2 * 4] = scale._z;

	return result;
}

Matrix4::~Matrix4()
{

}
