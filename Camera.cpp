#include "Camera.h"
#include "Textbox.h"
#include <cmath>

Camera::Camera(Vec3 pos)
{
	transform.setPos(pos);
}

void Camera::beginDraw(Canvas &canvas)
{	
	this->canvas = &canvas;

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
}

void Camera::drawMesh(Canvas &canvas, Mesh* mesh, LightSource* light)
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

}

void Camera::drawBall(Canvas& canvas, Vec3 pos, float radius, Color color)
{
	//if (depth_buffer == nullptr) beginDraw(canvas);

	if (pointInView(pos))
	{
		float region_left = mapVecToDisplay(canvas, pos + this->transform.getMat().rotateDirVector(Vec3::Y) * radius  * 1.5 * FOV_value).x;
		float region_right = mapVecToDisplay(canvas, pos + this->transform.getMat().rotateDirVector(Vec3::Y * -1) * radius * 1.5 * FOV_value).x;
		float region_top = mapVecToDisplay(canvas, pos + this->transform.getMat().rotateDirVector(Vec3::Z) * radius * 1.5 * FOV_value).y;
		float region_bottom = mapVecToDisplay(canvas, pos + this->transform.getMat().rotateDirVector(Vec3::Z * -1) * radius * 1.5 * FOV_value).y;

		ball_depth_info.set(transform.getInverse() * pos, radius, color, FOV_value);
		canvas.fillRect(region_left, region_top, region_right - region_left, region_bottom - region_top, checkDepthBall);
	}
}

void Camera::drawLine(Canvas& canvas, Vec3 start, Vec3 end, Color color)
{
	//if (depth_buffer == nullptr) beginDraw(canvas);
	
	if (pointInView(start) && pointInView(end))
	{
		canvas.drawLine(mapVecToDisplay(canvas, start), mapVecToDisplay(canvas, end), color);
	}
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

}

float Camera::getFOV()
{
	return atan(FOV_value) * Vec3::rad2deg * 2;
}

void Camera::setFOV(float deg)
{
	FOV_value = tan(deg / (2 * Vec3::rad2deg));
}

Vec3 Camera::getRay(int x, int y, int width, int height, float fov_val)
{
	float a = -((2 * x / (float)width) - 1) * fov_val;
	float b = ((height - 2 * y) / (float)width) * fov_val;
	return Vec3(1, a, b).unit();
}

Vec3 Camera::getRay(int x, int y)
{
	return getRay(x, y, this->canvas->getWidth(), this->canvas->getHeight(), this->FOV_value);
}

Color Camera::checkDepthBall(int x, int y, DepthBuffer& depth_buffer)
{
	//float a = -((2 * x / (float)depth_buffer.width) - 1) * ball_depth_info.fov;
	//float b = ((depth_buffer.height - 2 * y) / (float)depth_buffer.width) * ball_depth_info.fov;
	//Vec3 ray = Vec3(1, a, b).unit();

	Vec3 ray = getRay(x, y, depth_buffer.width, depth_buffer.height, ball_depth_info.fov);

	float t_ca = Vec3::dot(ball_depth_info.pos, ray);
	if (t_ca < 0) return Color::ALPHA;

	float d_sq = ball_depth_info.pos.sqMag() - (t_ca * t_ca);
	float r_sq = ball_depth_info.radius * ball_depth_info.radius;
	if (d_sq > r_sq) return Color::ALPHA;

	float t_hc = sqrt(r_sq - d_sq);
	float depth = t_ca - t_hc;

	if (depth_buffer.check(x, y, depth))
		return ball_depth_info.color;
	return Color::ALPHA;
}

LightSource* Camera::current_light = NULL;
Mesh* Camera::current_mesh = NULL;
int* Camera::current_ambient = NULL;
float** Camera::current_db = NULL;

decltype(Camera::ball_depth_info) Camera::ball_depth_info;