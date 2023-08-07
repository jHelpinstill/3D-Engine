#include "Button.h"
#include <iostream>

Button::Button(int x, int y, int width, int height)
{
	setPos(x, y);
	setSize(width, height);
}
Button::Button(int x, int y, int width, int height, std::string text)
{
	setPos(x, y);
	setSize(width, height);
	setText(text);
}
Button::Button(int x, int y, int width, int height, Color color)
{
	setPos(x, y);
	setSize(width, height);
	setColor(color);
}
Button::Button(int x, int y, int width, int height, Color fill_color, Color border_color)
{
	setPos(x, y);
	setSize(width, height);
	setFillColor(fill_color);
	setBorderColor(border_color);
}

Button::Button(Point relative_pos, int offset_x, int offset_y, int width, int height, std::string text)
{
	setRelativePos(relative_pos.x, relative_pos.y);
	setOffset(offset_x, offset_y);
	setSize(width, height);
	setText(text);

	pos_is_relative = true;
}

void Button::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
	setTextPos();
}
void Button::setRelativePos(float x, float y)
{
	this->relative_pos = Point(x, y);
	if (!pos_is_relative)
		setPos(0, 0);
	pos_is_relative = true;
}
void Button::setOffset(int x, int y)
{
	this->offset_x = x;
	this->offset_y = y;
}
void Button::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}
void Button::setColor(Color color)
{
	this->fill_color = color;
	this->border_color = (~color.val & 0x00ffffff) + (color.val & 0xff000000);
}

void Button::setFillColor(Color color)
{
	this->fill_color = color;
}

void Button::setBorderColor(Color color)
{
	this->border_color = color;
}

void Button::setText(std::string text)
{
	this->text.print(text);
	setTextPos();
}

void Button::setTextPos()
{
	text.setPos(x + width / 2 - text.getLength() * 6 * text.getScale() / 2 + text.getScale(), y + height / 2 - 4 * text.getScale());
}

void Button::snapBottom(int x, int frame_height)
{
	setPos(x, (frame_height - 1) - height);
}

void Button::snapRight(int y, int frame_width)
{
	setPos((frame_width - 1) - height, y);
}

void Button::draw(Canvas &canvas, MouseInfo &mouse)
{
	if (pos_is_relative)
	{
		x = canvas.getWidth() * relative_pos.x + offset_x;
		y = canvas.getHeight() * relative_pos.y + offset_y;
		setTextPos();
	}

	checkMouse(mouse);
	if(!pressed)
	{
		canvas.fillRect(x, y, width, height, fill_color);
		canvas.drawRect(x, y, width, height, border_color);
	}
	else
	{
		canvas.fillRect(x, y, width, height, border_color);
		canvas.drawRect(x, y, width, height, fill_color);
	}
	text.draw(canvas);
}
void Button::checkMouse(MouseInfo &mouse)
{
	clicked = false;
	pressed = false;
	
	if(mouse.x < (x + width) && mouse.x >= x && mouse.y < (y + height) && mouse.y >= y)
	{
		clicked = mouse.leftClick();
		pressed = mouse.leftIsDown();
	}
}

void Button::debug_print()
{
	std::cout << "pos: " << x << ", " << y << std::endl;
	std::cout << "size: " << width << ", " << height << std::endl;
	std::cout << "color: " << std::hex << fill_color.val << ", " << border_color.val << std::dec << std::endl;
	std::cout << std::endl;
}
