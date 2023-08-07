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

void Button::setPos(int x, int y)
{
	right_aligned = false;
	bottom_aligned = false;
	center_aligned_width = false;
	center_aligned_height = false;

	switch (x)
	{
	case LEFT:
		this->x = 0;
		break;
	case RIGHT:
		right_aligned = true;
		break;
	case CENTER:
		this->center_aligned_width = true;
		break;
	default:
		this->x = x;
		break;
	}
	switch (y)
	{
	case TOP:
		this->y = 0;
		break;
	case BOTTOM:
		this->bottom_aligned = true;
		break;
	case CENTER:
		this->center_aligned_height = true;
		break;
	default:
		this->y = y;
		break;
	}
	setTextPos();
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

const int Button::LEFT = -1;
const int Button::RIGHT = -2;
const int Button::TOP = -1;
const int Button::BOTTOM = -2;
const int Button::CENTER = -3;
