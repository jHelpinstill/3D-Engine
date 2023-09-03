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
	
	
	void attachToStaticVariables(Mesh* mesh, LightSource* light);
	
	static LightSource* current_light;
	static Mesh* current_mesh;
	static Color lightingColorFunc(int x, int y);
	static int* current_ambient;
	static float** current_db;

	struct
	{
		Vec3 pos = Vec3::zero; // transformed into camera view
		float radius = 0;
		Color color = Color::BLACK;
		float fov = 1;
		void set(Vec3 pos, float radius, Color color, float fov) { this->pos = pos; this->radius = radius; this->color = color; this->fov = fov; }
	} static ball_depth_info;
	static Color checkDepthBall(int x, int y, DepthBuffer& depth_buffer);
	
	Canvas* canvas = nullptr;

public:
	Transform transform;
	
	Camera(){}
	Camera(Vec3 pos);

	void beginDraw(Canvas& canvas);
	void endDraw();
	
	void drawMesh(Canvas &canvas, Mesh* mesh, LightSource* light);
	void drawBall(Canvas& canvas, Vec3 pos, float radius, Color color);
	void drawLine(Canvas& canvas, Vec3 start, Vec3 end, Color color);
	void drawHorizon(Canvas &canvas, Color ground_color, Color sky_color);

	static Vec3 getRay(int x, int y, int width, int height, float fov_val);
	Vec3 getRay(int x, int y);
	
	float getFOVVal();		
};

#endif
