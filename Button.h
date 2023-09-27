#ifndef BUTTON_
#define BUTTON_

#include "Canvas.h"
#include "MouseInfo.h"
#include "Textbox.h"
#include "Color.h"
#include "Rect.h"
#include <string>

class Button
{
public:
	enum class ClickEffect
	{
		NONE,
		GRAYER_FILL,
		GRAYER_BORDER,
		GRAYER_ALL,
		LIGHTER_ALL
	};

private:
	Rect body;

	ClickEffect click_effect = ClickEffect::NONE;
	Color pressed_fill_color;
	Color pressed_border_color;
	
	Textbox* text_box = nullptr;
	void setTextPos();
	void findPressedColors();
	
public:

	std::string name = "";

	bool hover_over = false;
	bool pressed = false;
	bool clicked = false;
	bool grabbed = false;
	bool released = false;

	
	Button() { body.x = body.y = body.width = body.height = 0; body.fill_color = Color(0xd0d0d0), body.border_color = Color(0x2f2f2f); }
	Button(Rect body, Textbox* text_box, std::string name, ClickEffect click_effect = ClickEffect::NONE);
	Button(const Button& other);

	Button& operator=(const Button& other);

	void setPos(int x, int y);
	void setSize(int width, int height);
	void setColor(Color color);
	void setFillColor(Color color);
	void setBorderColor(Color color);
	void setTextBox(Textbox* text_box);
	Textbox* getTextBox();

	void draw(Canvas& canvas);
	void checkMouse(MouseInfo& mouse);
	void checkMouse(MouseInfo& mouse, int x, int y);
	void draw(Canvas& canvas, MouseInfo& mouse);

	Rect getRect();

	void debug_print();
	std::string debug_string();

	~Button();
};

#endif
