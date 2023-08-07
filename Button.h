#ifndef BUTTON_
#define BUTTON_

#include "Canvas.h"
#include "MouseInfo.h"
#include "TextBox.h"
#include "Color.h"

class Button
{
private:
	int x;
	int y;
	int width;
	int height;
	
	Color fill_color = Color(0xd0d0d0);
	Color border_color = Color(0x2f2f2f);
	void checkMouse(MouseInfo &mouse);
	
	TextBox text;
	void setTextPos();
	
public:
	bool pressed = false;
	bool clicked = false;
	
	Button(){}
	Button(int x, int y, int width, int height);
	Button(int x, int y, int width, int height, const char* text);
	Button(int x, int y, int width, int height, Color fill_color);
	Button(int x, int y, int width, int height, Color fill_color, Color border_color);
	
	void setPos(int x, int y);
	void setSize(int width, int height);
	void setColor(Color color);
	void setFillColor(Color color);
	void setBorderColor(Color color);
	void setText(const char* text);
	void snapBottom(int x, int frame_height);
	void snapRight(int y, int frame_width);
	
	void draw(Canvas &canvas, MouseInfo &mouse);
	void debug_print();
};

#endif
