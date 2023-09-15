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
		GRAYER_ALL
	};

private:
	Rect body;

	Point relative_pos;
	int offset_x{}, offset_y{};
	bool pos_is_relative = false;
	ClickEffect click_effect = ClickEffect::NONE;
	Color pressed_fill_color;
	Color pressed_border_color;
	
	Textbox* text_box = nullptr;
	void setTextPos();
	void findPressedColors();
	
public:

	std::string name;

	bool hover_over = false;
	bool pressed = false;
	bool clicked = false;
	bool grabbed = false;
	bool released = false;

	
	Button() { body.x = body.y = body.width = body.height = 0; body.fill_color = Color(0xd0d0d0), body.border_color = Color(0x2f2f2f); }
	Button(Rect body, Textbox* text_box, std::string name, ClickEffect click_effect = ClickEffect::NONE);
	Button(Rect body, std::string text, std::string name, ClickEffect click_effect = ClickEffect::NONE);
	Button(Point relative_pos, int offset_x, int offset_y, int width, int height, std::string text, ClickEffect click_effect = ClickEffect::NONE);

	Button(const Button& other);
	void operator=(const Button& other);

	void setPos(int x, int y);
	void setRelativePos(float x, float y);
	void setOffset(int x, int y);
	void setSize(int width, int height);
	void setColor(Color color);
	void setFillColor(Color color);
	void setBorderColor(Color color);
	void setTextBox(Textbox* text_box);
	void setText(std::string text);
	Textbox* getTextBox();
	void snapBottom(int x, int frame_height);
	void snapRight(int y, int frame_width);

	void draw(Canvas& canvas);
	void checkMouse(MouseInfo& mouse);
	void checkMouse(MouseInfo& mouse, int x, int y);
	void draw(Canvas& canvas, MouseInfo& mouse);
	
	void debug_print();

	~Button();
};

#endif
