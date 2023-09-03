#include "Mat4.h"
#include <iostream>

Mat4::Mat4()
{
	A.makeEmpty(4, 4);
	A.makeIdentity();
}

Mat4::Mat4(Matrix A)
{
	if (A.n == 4 && A.m == 4)
		this->A = A;
	else
	{
		this->A.makeEmpty(4, 4);
		this->A.makeIdentity();
	}
}

Vec3 Mat4::operator*(Vec3 v)
{
	return A * v;
}

Mat4 Mat4::operator*(Mat4 &B)
{
	return Mat4(A * B.A);
}

float& Mat4::element(int i, int j)
{
	return A.a[i][j];
}

Vec3 Mat4::rotateDirVector(Vec3 v)
{
	Vec3 u;
	for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
		u.n[i] += A.a[i][j] * v.n[j];
	return u;
}

Mat4 Mat4::inverse()
{
	Matrix B = A;
	B.invert();
	return B;
}

void Mat4::debug_print()
{
	std::cout << "matrix: " << std::endl;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			std::cout << A.a[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}
