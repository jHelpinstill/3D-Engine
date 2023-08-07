#ifndef PLAYER_CONTROLLER
#define PLAYER_CONTROLLER

#include "Camera.h"
#include "KeyInfo.h"
#include "MouseInfo.h"

class PlayerController
{
private:
	Camera* camera;
	KeyInfo* keyboard;
	MouseInfo* mouse;
	
	float roll_val = 0;
	float yaw_val = 0;
	float pitch_val = 0;
	
public:
	PlayerController(){}
	PlayerController(Camera* camera, KeyInfo* keyboard, MouseInfo* mouse);
	
	void attachCamera(Camera* camera);
	void attachKeyboard(KeyInfo* keyboard);
	void attachMouse(MouseInfo* mouse);
	
	
	void update(float dt);
	void translate(Vec3 v);
	
	void pitch(float deg);
	void yaw(float deg);
	void roll(float deg);
};

#endif
