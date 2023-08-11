#include <iostream>
#include "Render.h"
#include "PointLight.h"
#include "Color.h"
#include "PlayerController.h"

void doButtons(Canvas &canvas, PlayerController &player, MouseInfo &mouse, float dt)
{
	static Button fwdButton(50, 100, 50, 50, new TextBox(0, 0, "FWD", 1.5));
	static Button bkwdButton(50, 150, 50, 50, new TextBox(0, 0, "BKWD", 1.5));
	static Button leftButton(0, 150, 50, 50, new TextBox(0, 0, "LEFT", 1.5));
	static Button rightButton(100, 150, 50, 50, new TextBox(0, 0, "RIGHT", 1.5));
	static Button upButton(0, 100, 50, 50, new TextBox(0, 0, "UP", 1.5));
	static Button downButton(100, 100, 50, 50, new TextBox(0, 0, "DOWN", 1.5));
	static Button rotLeftButton(0, 200, 50, 50, new TextBox(0, 0, "turnL", 1.5));
	static Button rotRightButton(100, 200, 50, 50, new TextBox(0, 0, "turnR", 1.5));
	static Button captureMouseBut(0, 300, 200, 30, new TextBox(0, 0, "capture mouse", 1.5));

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

void textScalingTest(Canvas& canvas, MouseInfo& mouse, KeyInfo& keyboard)
{
	static Button decrease(Point(0.5, 0.8), -100, 0, 50, 50, "-");
	static Button increase(Point(0.5, 0.8), 100, 0, 50, 50, "+");

	static TextBox text(395, 390, "Test ABC abc", 2);
	static TextBox scale_text(300, 200);
	static float scale = 2;

	static Color square[16] =
	{
		0x0, 0x0, 0x0, 0x0,
		0x0, 0xff000000, 0xff000000, 0x0,
		0x0, 0xff000000, 0xff000000, 0x0,
		0x0, 0x0, 0x0, 0x0
	};
	static Color smiley[144] =
	{
		Color::ALPHA, Color::ALPHA, Color::ALPHA, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::ALPHA, Color::ALPHA, Color::ALPHA,
		Color::ALPHA, Color::ALPHA, Color::BLACK, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::BLACK, Color::ALPHA, Color::ALPHA,
		Color::ALPHA, Color::BLACK, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::BLACK, Color::ALPHA,
		Color(0x00ff0000), Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK,
		Color(0x0000ff00), Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::YELLOW, Color::YELLOW,  Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK,
		Color(0x000000ff), Color::YELLOW, Color::BLACK, Color::BLACK, Color::BLACK, Color::YELLOW, Color::YELLOW, Color::BLACK, Color::BLACK, Color::BLACK, Color::YELLOW, Color::BLACK,
		Color(0x00ffff00), Color::YELLOW,  Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::BLACK,
		Color(0x0000ffff), Color::YELLOW,  Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::BLACK, Color::YELLOW, Color::YELLOW, Color::BLACK,
		Color(0x00ff00ff), Color::YELLOW,  Color::YELLOW, Color::YELLOW, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::BLACK,
		Color::ALPHA, Color::BLACK, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::BLACK, Color::ALPHA,
		Color::ALPHA, Color::ALPHA, Color::BLACK, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::YELLOW, Color::BLACK, Color::ALPHA, Color::ALPHA,
		Color::ALPHA, Color::ALPHA, Color::ALPHA, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, Color::ALPHA, Color::ALPHA, Color::ALPHA,
	};

	mouse.release();
	canvas.fill(Color::WHITE);
	text.setScale(scale);
	Point mouse_c(300, 300);
	canvas.drawCircle(mouse_c, 10);
	text.setPos(Point(400 + (mouse.x - mouse_c.x) / 20.0, 400 + (mouse.y - mouse_c.y) / 20.0));
	//canvas.lerpDrawMatrix(Point(380 + (mouse.x - mouse_c.x) / 20.0, 400 + (mouse.y - mouse_c.y) / 20.0), 4, 4, scale, square);
	canvas.lerpDrawMatrix(Point(380 + (mouse.x - mouse_c.x) / 20.0, 400 + (mouse.y - mouse_c.y) / 20.0), 12, 12, scale, smiley);
	text.draw(canvas);
	
	//canvas.lerpDrawPoint(Point(400 + (mouse.x - mouse_c.x) / 50.0, 400 + (mouse.y - mouse_c.y) / 50.0), scale);
	//canvas.fillRect(Point(410 + (mouse.x - mouse_c.x) / 50.0, 400 + (mouse.y - mouse_c.y) / 50.0), scale, scale);
	decrease.draw(canvas, mouse);
	increase.draw(canvas, mouse);

	// draw fat pixels
	int buffer[400];
	canvas.getFrameRegion(390, 390, 20, 20, buffer);
	for (int i = 0; i < 20; i++) for (int j = 0; j < 20; j++)
		canvas.fillRect(i * 10, j * 10, 10, 10, buffer[j * 20 + i]);
	canvas.drawRect(0, 0, 200, 200);

	if (decrease.clicked)
		scale -= 0.1;
	if (increase.clicked)
		scale += 0.1;
	scale_text.clear();
	scale_text.print(scale);
	scale_text.draw(canvas);
}

void render(Frame &frame, Camera &camera, MouseInfo &mouse, KeyInfo &keyboard, std::vector<Mesh*> &mesh_list)
{	
	static PointLight light(Vec3(2, 2, 2), Color::WHITE);
	static PlayerController player(&camera, &keyboard, &mouse);
	
	Canvas canvas(&frame);
	player.update(frame.dt);

	///// PLACE RENDER CODE HERE (PAINT TO CANVAS) /////

	//camera.drawHorizon(canvas, Color(0x50ff50), Color(0x8080ff));
	//camera.draw(canvas, mesh_list[0], &light);
	//
	//doButtons(canvas, player, mouse, frame.dt);
	//doText(canvas, frame.dt);

	textScalingTest(canvas, mouse, keyboard);

	if(keyboard.keyPressed(27))
		mouse.release();

}
