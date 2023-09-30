#include "Button.h"

Button::Button(int x, int y, int width, int height, ClickEffect click_effect, std::string name)
{
	setPos(x, y);
	setBody(standardBody(width, height));
	this->click_effect = click_effect;
	setName(name);
}
Button::Button(int x, int y, const Buffer& body, ClickEffect click_effect, std::string name)
{
	setPos(x, y);
	setBody(body);
	this->click_effect = click_effect;
	setName(name);
}
Button::Button(int x, int y, const Buffer& body, std::string text, ClickEffect click_effect, std::string name)
{
	setPos(x, y);
	setBody(body);
	this->click_effect = click_effect;
	findPressedBody();
	addText(text);
	
	setName(name);
}

void Button::addText(std::string text)
{
	Canvas canvas_body(body);
	Canvas canvas_pressed(pressed_body);

	Textbox textbox(0, 0, body.getWidth(), body.getHeight(), text, 1.0, Color::BLACK, Textbox::Adjustment::CENTER, "");
	
	textbox.draw(canvas_body);
	textbox.draw(canvas_pressed);
}

void Button::draw(Canvas& canvas)
{
	if (states.pressed)
		canvas.drawMatrix(pos.x, pos.y, pressed_body);
	else
		ScreenElement::draw(canvas);
}

void Button::findPressedBody()
{
	pressed_body = body;
	Color* pressed_pixels = pressed_body.getPixels();
	Color* body_pixels = body.getPixels();

	switch (click_effect)
	{
	case ClickEffect::NONE:
		break;

	case ClickEffect::GRAYER_FILL:
		break;

	case ClickEffect::GRAYER_BORDER:
		break;

	case ClickEffect::GRAYER_ALL:
		for (int i = 0; i < body.getWidth() * body.getHeight(); i++)
		{
			pressed_pixels[i].setR((body_pixels[i].getR() + 0x80) / 2);
			pressed_pixels[i].setG((body_pixels[i].getG() + 0x80) / 2);
			pressed_pixels[i].setB((body_pixels[i].getB() + 0x80) / 2);
		}
		break;
	
	case ClickEffect::LIGHTER_ALL:
		for (int i = 0; i < body.getWidth() * body.getHeight(); i++)
		{
			pressed_pixels[i].setR((body_pixels[i].getR() + 0xff) / 2);
			pressed_pixels[i].setG((body_pixels[i].getG() + 0xff) / 2);
			pressed_pixels[i].setB((body_pixels[i].getB() + 0xff) / 2);
		}
		break;

	default:
		break;
	}
}

void Button::checkMouse(MouseInfo &mouse)
{
	checkMouse(mouse, 0, 0);
}
void Button::checkMouse(MouseInfo& mouse, int x, int y)
{
	states.clicked = false;
	states.pressed = false;
	states.hovered = false;
	int pos_x = mouse.x - x;
	int pos_y = mouse.y - y;
	if (pos_x < (getPos().x + getSize().width) && pos_x >= getPos().x && pos_y < (getPos().y + getSize().height) && pos_y >= getPos().y)
	{
		states.hovered = true;
		states.clicked = mouse.leftClick();
		states.pressed = mouse.leftHeld();
		states.released = mouse.leftRelease();
	}
	if (states.clicked) states.grabbed = true;
	if (!states.pressed) states.grabbed = false;
}

bool Button::hovered()
{
	return states.hovered;
}
bool Button::pressed()
{
	return states.pressed;
}
bool Button::clicked()
{
	return states.clicked;
}
bool Button::grabbed()
{
	return states.grabbed;
}
bool Button::released()
{
	return states.released;
}

void Button::debug_print()
{
	Canvas::debug.print(debug_string());
}
std::string Button::debug_string()
{
	std::stringstream ss;
	ss << this->name;
	ss << "\nclicked: " << (states.clicked ? 1 : 0);
	ss << "\npressed: " << (states.pressed ? 1 : 0);
	ss << "\ngrabbed: " << (states.grabbed ? 1 : 0);
	ss << "\nreleased: " << (states.released ? 1 : 0);
	ss << "\nhover: " << (states.hovered ? 1 : 0);
	std::string out = ss.str();
	return out;
}

Buffer Button::standardBody(int width, int height, Color fill_color, Color border_color)
{
	Buffer body(width, height);
	Canvas canvas(body);
	canvas.fill(fill_color);
	canvas.drawRect(0, 0, width, height, border_color);
	return body;
}
