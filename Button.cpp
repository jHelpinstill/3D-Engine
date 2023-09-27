#include "Button.h"
#include <iostream>

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

Button::Button(const Button& other)
{
	*this = other;
}
Button& Button::operator=(const Button& other)
{
	if (this == &other)
		return *this;

	setPos(other.body.x, other.body.y);
	setSize(other.body.width, other.body.height);
	setFillColor(other.body.fill_color);
	setBorderColor(other.body.border_color);
	setTextBox(new Textbox(*(other.text_box)));

	this->name = other.name;
	this->click_effect = other.click_effect;
	this->hover_over = other.hover_over;
	this->pressed = other.pressed;
	this->clicked = other.clicked;
	this->grabbed = other.grabbed;
	this->released = other.released;
	findPressedColors();
	
	return *this;
}

void Button::setPos(int x, int y)
{
	this->body.x = x;
	this->body.y = y;
	setTextPos();
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
void Button::setTextBox(Textbox* text_box)
{
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
		return;
	text_box->setPos(body.x + body.width / 2 - text_box->getLength() * 6 * text_box->getScale() / 2 + text_box->getScale(), body.y + body.height / 2 - 4 * text_box->getScale());
}

void Button::draw(Canvas& canvas)
{
	if (pressed)
	{
		Rect pressed_rect = body;
		
		pressed_rect.fill_color = pressed_fill_color;
		pressed_rect.border_color = pressed_border_color;
		
		canvas.drawRect(pressed_rect);
	}
	else
		canvas.drawRect(body);

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
	
	case ClickEffect::LIGHTER_ALL:
		pressed_fill_color.setR((body.fill_color.getR() + 0xFF) / 2);
		pressed_fill_color.setG((body.fill_color.getG() + 0xFF) / 2);
		pressed_fill_color.setB((body.fill_color.getB() + 0xFF) / 2);

		pressed_border_color.setR((body.border_color.getR() + 0xFF) / 2);
		pressed_border_color.setG((body.border_color.getG() + 0xFF) / 2);
		pressed_border_color.setB((body.border_color.getB() + 0xFF) / 2);
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
	}
	if (clicked) grabbed = true;
	if (!pressed) grabbed = false;
}

Rect Button::getRect()
{
	return body;
}

void Button::debug_print()
{
	Canvas::debug.print(debug_string());
}
std::string Button::debug_string()
{
	std::stringstream ss;
	ss << this->name;
	ss << "\nclicked: " << (clicked ? 1 : 0);
	ss << "\npressed: " << (pressed ? 1 : 0);
	ss << "\ngrabbed: " << (grabbed ? 1 : 0);
	ss << "\nreleased: " << (released ? 1 : 0);
	ss << "\nhover: " << (hover_over ? 1 : 0);
	std::string out = ss.str();
	return out;
}

Button::~Button()
{
	delete text_box;
}
