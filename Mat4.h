#ifndef MAT_4_
#define MAT_4_

#include "Vec3.h"

class Mat4
{
public:
	float m[4][4];
	
	Mat4();
	
	Vec3 operator*(Vec3 v);
	Mat4 operator*(Mat4 &A);
	
	Mat4 inverse();
	Vec3 rotateDirVector(Vec3 v);
	void debug_print();
};

#endif
