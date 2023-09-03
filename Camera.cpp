#include "Camera.h"
#include <cmath>

Camera::Camera(Vec3 pos)
{
	transform.setPos(pos);
}

void Camera::beginDraw(Canvas &canvas)
{	
	depth_buffer = new float[canvas.getWidth() * canvas.getHeight()];

	float aspect_ratio = canvas.getWidth() / (float)canvas.getHeight();
	frustum_normals[0] = (Vec3::X * FOV_value + Vec3::Y).unit();
	frustum_normals[1] = (Vec3::X * FOV_value - Vec3::Y).unit();
	frustum_normals[2] = (Vec3::X * FOV_value + Vec3::Z * aspect_ratio).unit();
	frustum_normals[3] = (Vec3::X * FOV_value - Vec3::Z * aspect_ratio).unit();
}

void Camera::attachToStaticVariables(Mesh* mesh, LightSource* light)
{
	current_light = light;
	current_mesh = mesh;
	current_ambient = &ambient_light;
	current_db = &depth_buffer;
}

void Camera::draw(Canvas &canvas, Mesh* mesh, LightSource* light)
{
	attachToStaticVariables(mesh, light);
	
	// allocate depth buffer, assign frustum normals
	beginDraw(canvas);
	
	// Draw the light
	if(pointInView(current_light->pos))
		canvas.fillCircle(mapVecToDisplay(canvas, current_light->pos), 10, Color::WHITE);
	
//	std::cout << "drawing box" << std::endl;
	for(int i = 0; i < mesh->num_tris; i++)
	{
		// Drawing triangles
		Triangle tri = mesh->tris[i];
		for(int vert = 0; vert < 3; vert++)
			tri.verts[vert] = transform.getInverse() * tri.verts[vert];
		Vec3 normal = tri.normal();
		if(!clipTriangle(canvas, tri))
			continue;
			
		current_light->beginLighting(canvas.getWidth(), canvas.getHeight(), this, normal, tri.verts[0]);
		mapToDisplay(canvas, tri);
		canvas.fillTriangle(tri.verts[0].x, tri.verts[0].y, tri.verts[1].x, tri.verts[1].y, tri.verts[2].x, tri.verts[2].y, lightingColorFunc);
	}
	
	//drawNormals(canvas, mesh);
	
	// delete depth buffer
	endDraw();
}

void Camera::drawBall(Canvas& canvas, Vec3 pos, float radius, Color color)
{
	beginDraw(canvas);

	if (pointInView(pos))
	{
		Vec3 point_on_ball = pos + this->transform.getMat().rotateDirVector(Vec3::Y) * radius;
		Point center_pixel = mapVecToDisplay(canvas, pos);
		float pixels_radius = center_pixel.x - mapVecToDisplay(canvas, point_on_ball).x;
		canvas.fillCircle(mapVecToDisplay(canvas, pos), pixels_radius, color);
	}


	endDraw();
}

void Camera::drawHorizon(Canvas &canvas, Color ground_color, Color sky_color)
{
	Vec3 forward = transform.getMat().rotateDirVector(Vec3::X);
	float angle = asin(forward.unit().z);
	float max_angle = (canvas.getWidth() > canvas.getHeight()) ? atan(FOV_value * 2) : atan(FOV_value * 2 * canvas.getHeight() / (float)canvas.getWidth());
	if(angle > max_angle)
		angle = max_angle;
	else if(angle < -max_angle)
		angle = -max_angle;
		
	float height = tan(angle);
	
	int boundary = (height * canvas.getWidth() / 2) + canvas.getHeight() / 2;
	
	canvas.fillRect(0, 0, canvas.getWidth(), boundary, sky_color);
	canvas.fillRect(0, boundary, canvas.getWidth(), canvas.getHeight() - boundary, ground_color);
}

void Camera::drawNormals(Canvas &canvas, Mesh* mesh)
{	
	for(int i = 0; i < mesh->num_tris; i++)
	{
		Vec3 n = mesh->tris[i].normal();
		Vec3 p = mesh->tris[i].verts[0];
		if(!pointInView(n)) continue;
		if(!pointInView(p)) continue;
		canvas.drawLine(mapVecToDisplay(canvas, p + n), mapVecToDisplay(canvas, p), 0xee0000);
	}
}

Color Camera::lightingColorFunc(int x, int y)
{
	//float a, b;
	//a = ((2 * x / (float)) - 1) * info.FOV_value;
	//b = (info.height / (float)info.width - 2 * y / (float)info.width) * info.FOV_value;
	//
	//Vec3 v(1, a, b);

	return current_mesh->color;// current_light->findColor(RayCast(this, x, y).distance, *current_ambient)* current_mesh->color;// + Color(Color::occludeFast(current_mesh->color.val, *current_ambient << 24));
}

void Camera::mapToDisplay(Canvas &canvas, Triangle &tri)
{
	for(int i = 0; i < 3; i++)
	{
		float x, y;
		x = -tri.verts[i].y / tri.verts[i].x;
		x /= FOV_value;
		x = (x + 1) * canvas.getWidth() / 2;
		
		y = -tri.verts[i].z / tri.verts[i].x;
		y /= FOV_value;
		y *= canvas.getWidth() / 2;
		y += canvas.getHeight() / 2;
		
		tri.verts[i].x = x;
		tri.verts[i].y = y;
		tri.verts[i].z = 0;
	}
}

Point Camera::mapVecToDisplay(Canvas &canvas, Vec3 p)
{
	p = transform.getInverse() * p;
	float x, y;
	x = -p.y / p.x;
	x /= FOV_value;
	x = (x + 1) * canvas.getWidth() / 2;
	
	y = -p.z / p.x;
	y /= FOV_value;
	y *= canvas.getWidth() / 2;
	y += canvas.getHeight() / 2;
	
	Point point;
	point.x = x;
	point.y = y;
	
	return point;
}

bool Camera::clipTriangle(Canvas &canvas, Triangle &tri)
{
	if(!(Vec3::dot(tri.verts[0], tri.normal()) < 0))
		return false;
//	std::cout << "clipping" << std::endl;
	int which_normals[4];
	int num_clipped = 0;
	int clipped_plane;
	for(int i = 0; i < 3; i++) if(!transformedPointInView(tri.verts[i], &clipped_plane))
	{
		which_normals[num_clipped] = clipped_plane;
		num_clipped++;
	}
	if(num_clipped == 0) return true;
	return false;
	
//	std::cout << "triangle clipped!" << std::endl;
}

bool Camera::pointInView(Vec3 p)
{
	p = transform.getInverse() * p;
	return transformedPointInView(p);
}

bool Camera::transformedPointInView(Vec3 p, int* which_plane)
{
	if(p.x < clipping_distance)
		return false;
	for(int i = 0; i < 4; i++) if(Vec3::dot(frustum_normals[i], p) < 0)
	{
		if(which_plane != NULL) *which_plane = i;
		return false;
	}
			
	return true;
}

float Camera::getFOVVal()
{
	return FOV_value;
}

void Camera::endDraw()
{
	delete depth_buffer;
}

LightSource* Camera::current_light = NULL;
Mesh* Camera::current_mesh = NULL;
int* Camera::current_ambient = NULL;
float** Camera::current_db = NULL;
