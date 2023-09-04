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
	Matrix V(4, 1);
	for (int i = 0; i < 3; i++)
	{
		V.a[i][0] = v.n[i];
	}
	V.a[3][0] = 1;
	V = A * V;
	Vec3 u(V.a[0][0], V.a[1][0], V.a[2][0]);
	return u;
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
	return Mat4(B);
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
