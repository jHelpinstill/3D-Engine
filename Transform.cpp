#include "Transform.h"
#include <iostream>

Transform::Transform(Vec3 pos)
{
	setPos(pos);
}

Mat4& Transform::getMat()
{
	return mat;
}

Mat4& Transform::getInverse()
{
	return inverse_mat;
}

void Transform::setPos(Vec3 v)
{
	for(int i = 0; i < 3; i++)
	{
		mat.m[i][3] = v.n[i];
		inverse_mat.m[i][3] = -v.n[i];
	}
}

void Transform::translate(Vec3 v)
{
	for(int i = 0; i < 3; i++)
	{
		mat.m[i][3] += v.n[i];
		inverse_mat.m[i][3] -= v.n[i];
	}
}

void Transform::setRot(Quat q)
{
	Mat4 B, Q;
	Q = q.mat();
	
	for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
		mat.m[i][j] = Q.m[i][j];
	
	
	for(int i = 0; i < 3; i++)
		B.m[i][3] = -mat.m[i][3];
	
	inverse_mat = q.inverse().mat() * B;
}
void Transform::rotate(Quat q)
{
	Mat4 Q = q.mat();
	mat = mat * Q;
	inverse_mat = q.inverse().mat() * inverse_mat;	
}

Vec3 Transform::getPos()
{
	Vec3 pos;
	for(int i = 0; i < 3; i++)
		pos.n[i] = mat.m[i][3];
	return pos;
}
