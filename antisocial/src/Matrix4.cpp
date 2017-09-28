
#include <Matrix4.h>

#include <iostream>

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
				sum += _elements[i + x * 4] * other._elements[y + i * 4];
			}

			_elements[x + y * 4] = sum;
		}
	}

	return *this;
}

void Matrix4::toString()
{
	std::cout << _elements[0] << ", " << _elements[1] << ", " << _elements[2] << ", " << _elements[3] << std::endl;
	std::cout << _elements[4] << ", " << _elements[5] << ", " << _elements[6] << ", " << _elements[7] << std::endl;
	std::cout << _elements[8] << ", " << _elements[9] << ", " << _elements[10] << ", " << _elements[11] << std::endl;
	std::cout << _elements[12] << ", " << _elements[13] << ", " << _elements[14] << ", " << _elements[15] << std::endl;
}

Matrix4 antisocial::operator*(Matrix4 left, const Matrix4& right)
{
	return left.multiply(right);
}

Matrix4& Matrix4::operator*=(const Matrix4& other)
{
	return multiply(other);
}

Matrix4 Matrix4::ortho(float left, float right, float bottom, float top, float near, float far)
{
	Matrix4 result(1.0f);

	result._elements[0 + 0 * 4] = 2.0f / (right - left);
	result._elements[1 + 1 * 4] = 2.0f / (top - bottom);
	result._elements[2 + 2 * 4] = 2.0f / (near - far);

	result._elements[3 + 0 * 4] = 2.0f / (left + right) / (left - right);
	result._elements[3 + 1 * 4] = 2.0f / (bottom + top) / (bottom - top);
	result._elements[3 + 2 * 4] = 2.0f / (far + near) / (far - near);

	result._elements[15] = 0.0f;

	return result;
}

Matrix4 Matrix4::perspective(float fov, float aspectRatio, float near, float far)
{
	Matrix4 result(1.0f);

	float f_n = 1.0f / (far - near);
  	float theta = antisocial::radians(fov) * 0.5f;
	float divisor = tan(theta);
	float factor = 1.0f / divisor;

	result._elements[0] = 1.0f / (aspectRatio * factor);
	result._elements[5] = factor;
	result._elements[10] = (-(far + near)) * f_n;
	result._elements[11] = -2.0f * far * near * f_n;
	result._elements[14] = -1.0f;
	result._elements[15] = 0.0f;

//	float q = 1.0f / tan(antisocial::radians(fov / 2.0f));
//	float a = 1.0f / (aspectRatio * tan(antisocial::radians(fov / 2.0f)));
//	float b = -((near + far) / (near - far));
//	float c = -((2.0f * near * far) / (near - far));

//	result._elements[0 + 0 * 4] = a;
//	result._elements[1 + 1 * 4] = q;
//	result._elements[2 + 2 * 4] = b;
//	result._elements[2 + 3 * 4] = -1.0f;
//	result._elements[3 + 2 * 4] = c;

	return result;
}

Matrix4 Matrix4::lookAt(Vector3 camPos, Vector3 objPos, Vector3 up)
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

	result *= translate(result, translationVec);

	return result;
}

Matrix4 Matrix4::translate(Matrix4& mat, Vector3 translation)
{
	mat._elements[3 + 0 * 4] = translation._x;
	mat._elements[3 + 1 * 4] = translation._y;
	mat._elements[3 + 2 * 4] = translation._z;

	return mat;
}

Matrix4 Matrix4::rotate(Matrix4& mat, float angle, Vector3 axis)
{
	float r = radians(angle);
	float c = cos(r);
	float s = sin(r);
	float omc = 1.0f - c;

	mat._elements[0 + 0 * 4] = axis._x * axis._x * omc + c;
	mat._elements[0 + 1 * 4] = axis._y * axis._x * omc + axis._z * s;
	mat._elements[0 + 2 * 4] = axis._x * axis._z * omc - axis._y * s;

	mat._elements[1 + 0 * 4] = axis._x * axis._y * omc - axis._z * s;
	mat._elements[1 + 1 * 4] = axis._y * axis._y * omc + c;
	mat._elements[1 + 2 * 4] = axis._y * axis._z * omc + axis._x * s;

	mat._elements[2 + 0 * 4] = axis._x * axis._z * omc + axis._y * s;
	mat._elements[2 + 1 * 4] = axis._y * axis._z * omc - axis._x * s;
	mat._elements[2 + 2 * 4] = axis._x * axis._z * omc + c;

	return mat;
}

Matrix4 Matrix4::scale(Matrix4& mat, Vector3 scale)
{
	mat._elements[0 + 0 * 4] = scale._x;
	mat._elements[1 + 1 * 4] = scale._y;
	mat._elements[2 + 2 * 4] = scale._z;

	return mat;
}

Matrix4::~Matrix4()
{

}
