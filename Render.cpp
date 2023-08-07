#include <iostream>
#include "Render.h"
#include "PointLight.h"
#include "Color.h"
#include "PlayerController.h"

void doButtons(Canvas &canvas, PlayerController &player, MouseInfo &mouse, float dt)
{
	static Button fwdButton(50, 100, 50, 50, "FWD");
	static Button bkwdButton(50, 150, 50, 50, "BKWD");
	static Button leftButton(0, 150, 50, 50, "LEFT");
	static Button rightButton(100, 150, 50, 50, "RIGHT");
	static Button upButton(0, 100, 50, 50, "UP");
	static Button downButton(100, 100, 50, 50, "DOWN");
	static Button rotLeftButton(0, 200, 50, 50, "turnL");
	static Button rotRightButton(100, 200, 50, 50, "turnR");
	static Button captureMouseBut(0, 300, 200, 30, "capture mouse");

	static Button transparentButton(500, 500, 200, 200, Color(0x80808080));
	transparentButton.setPos(mouse.x - 100, mouse.y - 100);

	fwdButton.draw(canvas, mouse);
	bkwdButton.draw(canvas, mouse);
	leftButton.draw(canvas, mouse);
	rightButton.draw(canvas, mouse);
	upButton.draw(canvas, mouse);
	downButton.draw(canvas, mouse);
	rotLeftButton.draw(canvas, mouse);
	rotRightButton.draw(canvas, mouse);
	captureMouseBut.draw(canvas, mouse);

	//	transparentButton.draw(canvas, mouse);

	if (fwdButton.pressed)
		player.translate(Vec3::X * 2 * dt);
	if (bkwdButton.pressed)
		player.translate(Vec3::X * -2 * dt);
	if (leftButton.pressed)
		player.translate(Vec3::Y * 2 * dt);
	if (rightButton.pressed)
		player.translate(Vec3::Y * -2 * dt);
	if (upButton.pressed)
		player.translate(Vec3::Z * 2 * dt);
	if (downButton.pressed)
		player.translate(Vec3::Z * -2 * dt);
	if (rotLeftButton.pressed)
		player.yaw(90 * dt);
	if (rotRightButton.pressed)
		player.yaw(-90 * dt);
	if (captureMouseBut.pressed)
		mouse.capture();
}

void doText(Canvas& canvas, float dt)
{
	static TextBox info(0, 0, "Press 'esc' to release mouse", 2);
	static TextBox fps(0, 20);

	fps.setColor(Color::WHITE);
	fps.clear();
	fps.print(1.0 / dt); fps.print(" fps\n"); fps.print(dt * 1000); fps.print(" millis");
	fps.draw(canvas);

	info.draw(canvas);
}

void render(Frame &frame, Camera &camera, MouseInfo &mouse, KeyInfo &keyboard, std::vector<Mesh*> &mesh_list)
{	
	static PointLight light(Vec3(2, 2, 2), Color::WHITE);
	static PlayerController player(&camera, &keyboard, &mouse);
	
	
	
	Canvas canvas(&frame);
	player.update(frame.dt);

	///// PLACE RENDER CODE HERE (PAINT TO CANVAS) /////

	camera.drawHorizon(canvas, Color(0x50ff50), Color(0x8080ff));
	camera.draw(canvas, mesh_list[0], &light);

	doButtons(canvas, player, mouse, frame.dt);
	doText(canvas, frame.dt);
	
	if(keyboard.keyPressed(27))
		mouse.release();

}
