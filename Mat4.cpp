#include "Mat4.h"
#include <iostream>

Mat4::Mat4()
{
	for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++)
		m[i][j] = 0;
	for(int i = 0; i < 4; i++)
		m[i][i] = 1;
}

Vec3 Mat4::operator*(Vec3 v)
{
	Vec3 u;
	for(int i = 0; i < 3; i++)
	{
		u.n[i] = v.x * m[i][0] + v.y * m[i][1] + v.z * m[i][2] + m[i][3];
	}
	return u;
}

Mat4 Mat4::operator*(Mat4 &A)
{
	Mat4 B;
	for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++)
		B.m[i][j] = m[i][0] * A.m[0][j] + m[i][1] * A.m[1][j] + m[i][2] * A.m[2][j] + m[i][3] * A.m[3][j];
		
	return B;
}

Vec3 Mat4::rotateDirVector(Vec3 v)
{
	Vec3 u;
	for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
		u.n[i] += m[i][j] * v.n[j];
	return u;
}

void Mat4::debug_print()
{
	std::cout << "matrix: " << std::endl;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			std::cout << m[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}
