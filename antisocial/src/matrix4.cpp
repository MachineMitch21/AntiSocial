
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

	_elements[0 + 0 + 4] = diagonal;
	_elements[1 + 1 + 4] = diagonal;
	_elements[2 + 2 + 4] = diagonal;
	_elements[3 + 3 + 4] = diagonal;
}

Matrix4 Matrix4::identity()
{
	return Matrix4(1.0f);
}

Matrix4& Matrix4::multiply(const Matrix4& other)
{
	
}

Matrix4::~Matrix4()
{

}
