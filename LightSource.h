#ifndef LIGHT_SOURCE
#define LIGHT_SOURCE

#include "Vec3.h"
#include "Camera.h"
#include "Color.h"

class Camera;

struct LightInfo
{
	float d;
	float pixel_inc;
	float prev_a;
	float prev_b;
	float prev_sq_mag;
	float pos_sq_mag;
	float FOV_value;
	
	int prev_x;
	int prev_y;
	
	int width;
	int height;
	
	Vec3 dest_normal;
};

class LightSource
{
protected:
	
	LightInfo info;
	virtual int incrementX() { return 0; }
	virtual int incrementY(int x) { return 0; }
	bool current_tri_is_lit;
	
public:
	Vec3 pos;
	Color color;
	
	LightSource(){}
	
	virtual void beginLighting(int width, int height, Camera* camera, Vec3 dest_normal, Vec3 point_on_plane){}
	virtual Color findColor(int x, int y, Color base_color) { return base_color; }
	
};

#endif
