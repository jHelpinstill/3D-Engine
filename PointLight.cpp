#include "PointLight.h"
#include <iostream>

PointLight::PointLight()
{
	this->color = Color::WHITE;
}

PointLight::PointLight(Vec3 pos, Color color)
{
	this->pos = pos;
	this->color = color;
}

void PointLight::beginLighting(int width, int height, Camera* camera, Vec3 dest_normal, Vec3 point_on_plane)
{
	transformed_pos = camera->transform.getInverse() * pos;
	pos_sq_mag = transformed_pos.sqMag();
	current_tri_is_lit = true;
	if(Vec3::dot(transformed_pos - point_on_plane, dest_normal) < 0)
		current_tri_is_lit = false;
//	else
//		std::cout << "tri lit. dot prod: ";
//	std::cout << Vec3::dot(transformed_pos - point_on_plane, dest_normal) << std::endl;
	info.width = width;
	info.height = height;
	info.d = Vec3::dot(dest_normal, point_on_plane);
	info.pixel_inc = 2 * camera->getFOVVal() / width;
	info.prev_x = info.prev_y = -1;
	info.dest_normal = dest_normal;
	info.FOV_value = camera->getFOVVal();
}

int PointLight::incrementX()
{
	return 0;
}
int PointLight::incrementY(int x)
{
	return 0;
}
Color PointLight::findColor(int x, int y, Color base_color)
{
	if(!current_tri_is_lit)
		return base_color;
	float a, b;
	a = ((2 * x / (float)info.width) - 1) * info.FOV_value;
	b = (info.height / (float)info.width - 2 * y / (float)info.width) * info.FOV_value;
	
	Vec3 v(1, a, b);
	float v_sq_mag = v.sqMag();
	float n_dot_v = Vec3::dot(info.dest_normal, v);
	float denom = (v_sq_mag * info.d) / (n_dot_v * n_dot_v) - 2 * Vec3::dot(v, pos) / n_dot_v + pos_sq_mag;
	Color color_out = color / denom;
	
//	std::cout << denom << std::endl;
//	std::cout << std::hex << color_out.val << std::dec << std::endl;
	return color_out * base_color;//(color_out + base_color).val;
}
