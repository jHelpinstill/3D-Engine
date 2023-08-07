#include "Vec3.h"
#include <cmath>
#include <iostream>

Vec3::Vec3()
{
	x = y = z = 0;
}
Vec3::Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3 Vec3::operator+(Vec3 v)
{
	Vec3 u;
	for(int i = 0; i < 3; i++)
		u.n[i] = this->n[i] + v.n[i];
	return u;
}
Vec3 Vec3::operator-(Vec3 v)
{
	Vec3 u;
	for(int i = 0; i < 3; i++)
		u.n[i] = this->n[i] - v.n[i];
	return u;
}
Vec3 Vec3::operator*(float a)
{
	Vec3 u;
	for(int i = 0; i < 3; i++)
		u.n[i] = this->n[i] * a;
	return u;
}
Vec3 Vec3::operator/(float a)
{
	if(a == 0) return Vec3::zero;
	Vec3 u;
	
	for(int i = 0; i < 3; i++)
		u.n[i] = this->n[i] / a;
	return u;
}

void Vec3::operator+=(Vec3 v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}
void Vec3::operator-=(Vec3 v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}
void Vec3::operator*=(float a)
{
	this->x *= a;
	this->y *= a;
	this->z *= a;
}
void Vec3::operator/=(float a)
{
	if(a == 0) 
	{
		*this = Vec3::zero;
		return;
	}
	this->x /= a;
	this->y /= a;
	this->z /= a;
}

float Vec3::mag()
{
	return sqrt(x * x + y * y + z * z);
}
float Vec3::sqMag()
{
	return x * x + y * y + z * z;
}
Vec3 Vec3::unit()
{
	float mag = this->mag();
	if(mag == 0) return Vec3::zero;
	return *this / mag;
}

float Vec3::dot(Vec3 v, Vec3 u)
{
	return v.x * u.x + v.y * u.y + v.z * u.z;
}
Vec3 Vec3::cross(Vec3 v, Vec3 u)
{
	Vec3 w;
	w.x = v.y * u.z - v.z * u.y;
	w.y = v.z * u.x - v.x * u.z;
	w.z = v.x * u.y - v.y * u.x;
	return w;
}
Vec3 Vec3::project(Vec3 v, Vec3 u)
{
	float u_sq_mag = u.sqMag();
	if(u_sq_mag == 0)	return Vec3::zero;
	Vec3 w = u * (dot(v, u) / u_sq_mag);
	return w;
}
float Vec3::angleBetween(Vec3 v, Vec3 u)
{
//	float d = dot(v.unit(), u.unit());
//	if(d >= 1) return 0;
//	if(d <= -1) return 180;
	return acos(dot(v.unit(), u.unit())) * rad2deg;
}

void Vec3::debug_print()
{
	std::cout << "vector: " << x << ", " << y << ", " << z << std::endl;
}

Vec3 Vec3::zero = Vec3(0, 0, 0);
Vec3 Vec3::X = Vec3(1, 0, 0);
Vec3 Vec3::Y = Vec3(0, 1, 0);
Vec3 Vec3::Z = Vec3(0, 0, 1);

float Vec3::rad2deg = 180 / 3.14159265358979323846;
