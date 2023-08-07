#ifndef TRANSFORM_
#define TRANSFORM_

#include "Vec3.h"
#include "Mat4.h"
#include "Quat.h"

class Transform
{
private:
	Mat4 mat;
	Mat4 inverse_mat;
	
public:
	Transform(){}
	Transform(Vec3 pos);
	
	Mat4& getMat();
	Mat4& getInverse();
	
	void setPos(Vec3 v);
	void translate(Vec3 v);
	
	void setRot(Quat q);
	void rotate(Quat q);
	
	Vec3 getPos();
};

#endif
