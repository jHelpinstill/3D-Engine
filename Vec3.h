#ifndef VEC_3
#define VEC_3

class Vec3
{
public:
	union
	{
		struct
		{
			float
				x,
				y,
				z;
		};
		float n[3];
	};
	
	static Vec3 zero;
	static Vec3 X;
	static Vec3 Y;
	static Vec3 Z;
	
	Vec3();
	Vec3(float x, float y, float z);
	
	Vec3 operator+(Vec3 v);
	Vec3 operator-(Vec3 v);
	Vec3 operator*(float a);
	Vec3 operator/(float a);
	
	void operator+=(Vec3 v);
	void operator-=(Vec3 v);
	void operator*=(float a);
	void operator/=(float a);
	
	float mag();
	float sqMag();
	Vec3 unit();
	
	static float dot(Vec3 v, Vec3 u);
	static Vec3 cross(Vec3 v, Vec3 u);
	static Vec3 project(Vec3 v, Vec3 u);
	static float angleBetween(Vec3 v, Vec3 u);
	
	void debug_print();
	
	static float rad2deg;
};

#endif
