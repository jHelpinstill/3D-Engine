#ifndef CAMERA_
#define CAMERA_

#include "Transform.h"
#include "Canvas.h"
#include "Mesh.h"
#include "LightSource.h"
#include "PointLight.h"
#include "Color.h"

class LightSource;

class Camera
{
private:
	float* depth_buffer;
	Vec3 frustum_normals[4];
	float clipping_distance = 0.01;
	int ambient_light = 25;
	
	float FOV_value = 1;
	bool checkTriNormal(Triangle &triangle);
	void mapToDisplay(Canvas &canvas, Triangle &tri);
	bool clipTriangle(Canvas &canvas, Triangle &tri);
	Point mapVecToDisplay(Canvas &canvas, Vec3 p);
	void drawNormals(Canvas &canvas, Mesh* mesh);
	bool pointInView(Vec3 p);
	bool transformedPointInView(Vec3 p, int* which_plane = NULL);
	
	void beginDraw(Canvas &canvas);
	void endDraw();
	void attachToStaticVariables(Mesh* mesh, LightSource* light);
	
	static LightSource* current_light;
	static Mesh* current_mesh;
	static Color lightingColorFunc(int x, int y);
	static int* current_ambient;
	static float** current_db;
	
public:
	Transform transform;
	
	Camera(){}
	Camera(Vec3 pos);
	
	void draw(Canvas &canvas, Mesh* mesh, LightSource* light);
	void drawHorizon(Canvas &canvas, Color ground_color, Color sky_color);
	
	float getFOVVal();		
};

#endif
