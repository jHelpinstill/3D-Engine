#include "Button.h"
#include <iostream>

Button::Button(Rect body, std::string text, std::string name, ClickEffect click_effect)
{
	setPos(body.x, body.y);
	setSize(body.width, body.height);
	setFillColor(body.fill_color);
	setBorderColor(body.border_color);
	setText(text);
	this->name = name;
	this->click_effect = click_effect;
	findPressedColors();
}
Button::Button(Rect body, Textbox* text_box, std::string name, ClickEffect click_effect)
{
	setPos(body.x, body.y);
	setSize(body.width, body.height);
	setFillColor(body.fill_color);
	setBorderColor(body.border_color);
	setTextBox(text_box);
	this->name = name;
	this->click_effect = click_effect;
	findPressedColors();
}
Button::Button(Point relative_pos, int offset_x, int offset_y, int width, int height, std::string text, ClickEffect click_effect)
{
	setRelativePos(relative_pos.x, relative_pos.y);
	setOffset(offset_x, offset_y);
	setSize(width, height);
	setText(text);

	pos_is_relative = true;
	this->click_effect = click_effect;
	findPressedColors();
}

Button::Button(const Button& other)
{
	*this = other;
}
void Button::operator=(const Button& other)
{
	this->body = other.body;

	this->relative_pos = other.relative_pos;
	this->offset_x = other.offset_x;
	this->offset_y = other.offset_y;
	this->pos_is_relative = other.pos_is_relative;

	this->name = other.name;

	this->pressed = other.pressed;
	this->clicked = other.clicked;
	this->text_box = new Textbox(*(other.text_box));
}

void Button::setPos(int x, int y)
{
	this->body.x = x;
	this->body.y = y;
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
	this->body.width = width;
	this->body.height = height;
}
void Button::setColor(Color color)
{
	this->body.fill_color = color;
	this->body.border_color = (~color.val & 0x00ffffff) + (color.val & 0xff000000);
	findPressedColors();
}

void Button::setFillColor(Color color)
{
	this->body.fill_color = color;
	findPressedColors();
}

void Button::setBorderColor(Color color)
{
	this->body.border_color = color;
	findPressedColors();
}

void Button::setText(std::string text)
{
	delete text_box;
	text_box = new Textbox();
	text_box->print(text);
	setTextPos();
}
void Button::setTextBox(Textbox* text_box)
{
	if (this->text_box != nullptr)
		delete this->text_box;
	this->text_box = text_box;
	setTextPos();
}
Textbox* Button::getTextBox()
{
	return text_box;
}
void Button::setTextPos()
{
	if (text_box == nullptr)
		text_box = new Textbox();
	text_box->setPos(body.x + body.width / 2 - text_box->getLength() * 6 * text_box->getScale() / 2 + text_box->getScale(), body.y + body.height / 2 - 4 * text_box->getScale());
}

void Button::snapBottom(int x, int frame_height)
{
	setPos(x, (frame_height - 1) - body.height);
}

void Button::snapRight(int y, int frame_width)
{
	setPos((frame_width - 1) - body.height, y);
}

void Button::draw(Canvas& canvas)
{
	if (pos_is_relative)
	{
		body.x = canvas.getWidth() * relative_pos.x + offset_x;
		body.y = canvas.getHeight() * relative_pos.y + offset_y;
		setTextPos();
	}
	if (!pressed)
	{
		canvas.drawRect(body);
	}
	else
	{
		Rect pressed = body;
		
		pressed.fill_color = pressed_fill_color;
		pressed.border_color = pressed_border_color;

		canvas.drawRect(pressed);
	}
	text_box->draw(canvas);
}

void Button::findPressedColors()
{
	pressed_fill_color = body.fill_color;
	pressed_border_color = body.border_color;

	switch (click_effect)
	{
	case ClickEffect::NONE:
		break;

	case ClickEffect::GRAYER_FILL:
		pressed_fill_color.setR((body.fill_color.getR() + 0x80) / 2);
		pressed_fill_color.setG((body.fill_color.getG() + 0x80) / 2);
		pressed_fill_color.setB((body.fill_color.getB() + 0x80) / 2);
		break;

	case ClickEffect::GRAYER_BORDER:
		pressed_border_color.setR((body.border_color.getR() + 0x80) / 2);
		pressed_border_color.setG((body.border_color.getG() + 0x80) / 2);
		pressed_border_color.setB((body.border_color.getB() + 0x80) / 2);
		break;

	case ClickEffect::GRAYER_ALL:
		pressed_fill_color.setR((body.fill_color.getR() + 0x80) / 2);
		pressed_fill_color.setG((body.fill_color.getG() + 0x80) / 2);
		pressed_fill_color.setB((body.fill_color.getB() + 0x80) / 2);
			   
		pressed_border_color.setR((body.border_color.getR() + 0x80) / 2);
		pressed_border_color.setG((body.border_color.getG() + 0x80) / 2);
		pressed_border_color.setB((body.border_color.getB() + 0x80) / 2);
		break;

	default:
		break;
	}
}

void Button::draw(Canvas& canvas, MouseInfo& mouse)
{
	checkMouse(mouse);
	draw(canvas);
}
void Button::checkMouse(MouseInfo &mouse)
{
	checkMouse(mouse, 0, 0);
}
void Button::checkMouse(MouseInfo& mouse, int x, int y)
{
	clicked = false;
	pressed = false;
	hover_over = false;
	int pos_x = mouse.x - x;
	int pos_y = mouse.y - y;
	if (pos_x < (body.x + body.width) && pos_x >= body.x && pos_y < (body.y + body.height) && pos_y >= body.y)
	{
		hover_over = true;
		clicked = mouse.leftClick();
		pressed = mouse.leftHeld();
		released = mouse.leftRelease();
		if (clicked) grabbed = true;
		if (!pressed) grabbed = false;
	}
}
void Button::debug_print()
{
	std::cout << "pos: " << body.x << ", " << body.y << std::endl;
	std::cout << "size: " << body.width << ", " << body.height << std::endl;
	std::cout << "color: " << std::hex << body.fill_color.val << ", " << body.border_color.val << std::dec << std::endl;
	std::cout << std::endl;
}

Button::~Button()
{
	delete text_box;
}
