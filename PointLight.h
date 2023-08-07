#ifndef POINT_LIGHT
#define POINT_LIGHT

#include "LightSource.h"

class PointLight : public LightSource
{
private:
	float pos_sq_mag;
	
	Vec3 transformed_pos;
	int incrementX();
	int incrementY(int x);
	
	
public:
	
	PointLight();
	PointLight(Vec3 pos, Color color);
	
	void beginLighting(int, int, Camera*, Vec3, Vec3);
	Color findColor(int x, int y, Color base_color);
};

#endif
