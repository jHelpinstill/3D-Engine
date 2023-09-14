#include "PlayerController.h"
#include <chrono>
#include <iomanip>
#include <cmath>

PlayerController::PlayerController(Camera* camera, KeyInfo* keyboard, MouseInfo* mouse)
{
	attachCamera(camera);
	attachKeyboard(keyboard);
	attachMouse(mouse);
}

void PlayerController::attachCamera(Camera* camera)
{
	this->camera = camera;
}

void PlayerController::attachKeyboard(KeyInfo* keyboard)
{
	this->keyboard = keyboard;
}

void PlayerController::attachMouse(MouseInfo* mouse)
{
	this->mouse = mouse;
}

void PlayerController::update(float dt)
{
	if(mouse->isCaptured())
	{
		yaw(-mouse->delta_x_raw / 5.0);
		pitch(-mouse->delta_y_raw / 5.0);
	}
	
	if(keyboard->keyHeld('W'))
		translate(Vec3::X * 2 * dt);
	if(keyboard->keyHeld('S'))
		translate(Vec3::X * -2 * dt);
	if(keyboard->keyHeld('A'))
		translate(Vec3::Y * 2 * dt);
	if(keyboard->keyHeld('D'))
		translate(Vec3::Y * -2 * dt);
	if(keyboard->keyHeld(KeyInfo::SHIFT))
		translate(Vec3::Z * 2 * dt);
	if(keyboard->keyHeld(KeyInfo::CTRL))
		translate(Vec3::Z * -2 * dt);
}
void PlayerController::translate(Vec3 v)
{
	Vec3 forward = camera->transform.getMat().rotateDirVector(Vec3::X);
	forward.z = 0;
	Vec3 left = Vec3::cross(Vec3::Z, forward);
	
	left = left.unit() * v.y;
	forward = forward.unit() * v.x;
	v = left + forward + Vec3::Z * v.z;
	camera->transform.translate(v);
}

void PlayerController::pitch(float deg)
{
	Vec3 forward = camera->transform.getMat().rotateDirVector(Vec3::X);
	float angle = asin(forward.unit().z) * Vec3::rad2deg;
//	std::cout << "angle: " << angle << " initial deg: " << deg;
	if(angle + deg > 90)
		deg = 90 - angle;
	else if(angle + deg < -90)
		deg = -90 - angle;
		
//	std::cout << "final deg: " << deg << std::endl;
	camera->transform.rotate(Quat(Vec3::Y, -deg));
	
//	Vec3 forward = camera->transform.getMat().rotateDirVector(Vec3::X);
////	forward.debug_print();
//	std::cout << angle << std::endl;
}
void PlayerController::yaw(float deg)
{
	Vec3 axis = camera->transform.getInverse().rotateDirVector(Vec3::Z);
	camera->transform.rotate(Quat(axis, deg));
}
void PlayerController::roll(float deg)
{
	camera->transform.rotate(Quat(Vec3::X, deg));
}
