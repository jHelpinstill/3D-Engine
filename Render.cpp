#include <iostream>
#include "Render.h"
#include "PointLight.h"
#include "Color.h"
#include "PlayerController.h"

void render(Frame &frame, Camera &camera, MouseInfo &mouse, KeyInfo &keyboard, std::vector<Mesh*> &mesh_list)
{
//	Transform t1(Vec3(1, 1, 1));
//	Transform t2(Vec3(1, 1, 1));
//	
//	std::cout << "before: " << std::endl;
//	std::cout << "t1: " << std::endl;
//	t1.getMat().debug_print();
//	t1.getInverse().debug_print();
//	std::cout << "t2: " << std::endl;
//	t2.getMat().debug_print();
//	t2.getInverse().debug_print();
//	
//	t1.rotate(Quat(Vec3::Z, -45));
//	t1.rotate(Quat(Vec3::Z, 90));
//	t2.rotate(Quat(Vec3::X, 123));
//	t2.setRot(Quat(Vec3::Z, 45));
//	
//	std::cout << "after: " << std::endl;
//	std::cout << "t1: " << std::endl;
//	t1.getMat().debug_print();
//	t1.getInverse().debug_print();
//	std::cout << "t2: " << std::endl;
//	t2.getMat().debug_print();
//	t2.getInverse().debug_print();
	
	
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
	
	static PointLight light(Vec3(2, 2, 2), Color::WHITE);
	static PlayerController player(&camera, &keyboard, &mouse);
	
	static TextBox info(0, 0, "Press 'esc' to release mouse", 2);
	static TextBox fps(0, 20);
	fps.setColor(Color::WHITE);
	
	Canvas canvas(&frame);
	player.update(frame.dt);
	// Place render code here, paint to canvas.
//	canvas.fill(Color::BLACK);

	camera.drawHorizon(canvas, Color(0x50ff50), Color(0x8080ff));
	camera.draw(canvas, mesh_list[0], &light);
	
	if(keyboard.keyPressed(27))
		mouse.release();
	
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
	
	if(fwdButton.pressed)
		player.translate(Vec3::X * 2 * frame.dt);
	if(bkwdButton.pressed)
		player.translate(Vec3::X * -2 * frame.dt);
	if(leftButton.pressed)
		player.translate(Vec3::Y * 2 * frame.dt);
	if(rightButton.pressed)
		player.translate(Vec3::Y * -2 * frame.dt);
	if(upButton.pressed)
		player.translate(Vec3::Z * 2 * frame.dt);
	if(downButton.pressed)
		player.translate(Vec3::Z * -2 * frame.dt);
	if(rotLeftButton.pressed)
		player.yaw(90 * frame.dt);
	if(rotRightButton.pressed)
		player.yaw(-90 * frame.dt);
	if(captureMouseBut.pressed)
		mouse.capture();
	
	fps.clear();
	fps.print(1.0 / frame.dt); fps.print(" fps\n"); fps.print(frame.dt * 1000); fps.print(" millis");
	fps.draw(canvas);
	info.draw(canvas);
//	camera.transform.getMat().debug_print();
//	std::cout << "inverse "; camera.transform.getInverse().debug_print();
}
