#include "Quat.h"
#include <iostream>
#include <cmath>

Quat::Quat()
{
	a = 1;
	b = 0;
	c = 0;
	d = 0;
}
  
Quat::Quat(float a, float b, float c, float d){
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

Quat::Quat(Vec3 eulers)
{
    Quat heading_rot(Vec3::Z, eulers.z);
    Vec3 roll_vec = heading_rot * Vec3::X;
    Vec3 pitch_vec = Vec3::cross(roll_vec, Vec3::Z);//roll_vec.cross(Vec3::Z);

    *this = Quat(pitch_vec, -eulers.y) * Quat(roll_vec, eulers.x) * heading_rot;
}

Quat::Quat(Vec3 v, float deg){
	convertAxisAngle(v, deg);
}

Quat Quat::operator*(Quat q){
	Quat r;
	r.a = a * q.a - b * q.b - c * q.c - d * q.d;
	r.b = a * q.b + b * q.a + c * q.d - d * q.c;
	r.c = a * q.c - b * q.d + c * q.a + d * q.b;
	r.d = a * q.d + b * q.c - c * q.b + d * q.a;
	return r;
}

Quat Quat::inverse(){
	Quat q(a, -b, -c, -d);
	return q;
}

Vec3 Quat::operator*(Vec3 v){
	Quat qin( a, -b, -c, -d );
	Quat qVec( 0, v.x, v.y, v.z );
	Quat temp = (*this * qVec) * qin;
	Vec3 r(temp.b, temp.c, temp.d);
	return r;
}

void Quat::convertAxisAngle(Vec3 v, float angle){
	float halfrad = 0.5 * angle * 3.141592653589793 / 180;
	v = v.unit();
	a = cos(halfrad);
	b = sin(halfrad) * v.x;
	c = sin(halfrad) * v.y;
	d = sin(halfrad) * v.z;
}

Quat Quat::slerp(float t){
	Quat q;
	float theta = 2 * acos(a);
	
	if(theta == 0)
		return *this;
	
	float scalar = sin(t * theta) / sin(theta);
	
	q.a = (sin((1 - t) * theta) / sin(theta)) + a * scalar;
	q.b = b * scalar;
	q.c = c * scalar;
	q.d = d * scalar;
	return q;
}

void Quat::normalize(){
	float length = sqrt(a * a + b * b + c * c + d * d);
	a /= length;
	b /= length;
	c /= length;
	d /= length;
}

Mat4 Quat::mat(){
	Mat4 A;
	float a2, b2, c2, d2;
	a2 = a * a; b2 = b * b; c2 = c * c; d2 = d * d;
	A.element(0,0) = a2 + b2 - c2 - d2;
	A.element(1,1) = a2 - b2 + c2 - d2;
	A.element(2,2) = a2 - b2 - c2 + d2;

	A.element(0,1) = 2 * b * c - 2 * a * d;
	A.element(0,2) = 2 * b * d + 2 * a * c;
	A.element(1,0) = 2 * b * c + 2 * a * d;
	A.element(1,2) = 2 * c * d - 2 * a * b;
	A.element(2,0) = 2 * b * d - 2 * a * c;
	A.element(2,1) = 2 * c * d + 2 * a * b;
	
	return A;
}

Vec3 Quat::getAxis()
{
    if (w > 1)
        normalize();
    Vec3 axis;
    float factor = sin(acos(a));
    if (factor == 0) return Vec3::zero;
    axis.x = b / factor;
    axis.y = c / factor;
    axis.z = d / factor;
    return axis.unit();
}

float Quat::getAngle()
{
    if (w > 1)
        normalize();
    float halfrad = acos(a);
    return 2 * halfrad * Vec3::rad2deg;
}


Vec3 Quat::eulerAngles()
{
    Vec3 angles;
    angles.x = atan(2 * (w * x + y * z) / (1 - 2 * (x * x + y * y))) * Vec3::rad2deg;
    angles.y = (2 * atan(sqrt(1 + 2 * (w * y - x * z)) / sqrt(1 - 2 * (w * y - x * z)))) * Vec3::rad2deg - 90;
    angles.z = atan2(2 * (w * z + x * y), (1 - 2 * (y * y + z * z))) * Vec3::rad2deg;
    for (int i = 0; i < 3; i++)
    {
        if (std::isnan(angles.n[i]))
            angles.n[i] = 0;
    }
    return angles;
}

void Quat::debug_print(){
	std::cout << "Quat: ";
	for(int i = 0; i < 4; i++)
		std::cout << n[i] << ", ";
	std::cout << std::endl;
}
