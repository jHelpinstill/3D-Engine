#include "Widget.h"

Widget::Widget(int x, int y, int width, int height)
{
	setPos(x, y);
	setSize(width, height);

	regions.push_back(new Region(Rect(0, 0, width, height, Color::LIGHT_GRAY, Color::DARK_GRAY), "default"));
}

Widget::Widget(
	int x, int y, int width, int height,
	std::initializer_list<Button*> buttons,
	std::initializer_list<Textbox*> textboxes,
	std::initializer_list<Region*> regions)
{
	setPos(x, y);
	setSize(width, height);

	for (Button* b : buttons)
		this->buttons.push_back(b);

	for (Textbox* t : textboxes)
		this->textboxes.push_back(t);

	for (Region* r : regions)
		this->regions.push_back(r);
}

void Widget::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Widget::shiftPos(int x, int y)
{
	setPos(this->x + x, this->y + y);
}

int Widget::getX()
{
	return x;
}

int Widget::getY()
{
	return y;
}

void Widget::setSize(int width, int height)
{
	delete frame.pixels;
	frame.pixels = new uint32_t[width * height];
	frame.width = width;
	frame.height = height;
	body = Canvas(&frame);
}

void Widget::draw(Canvas& canvas, MouseInfo& mouse)
{
	for (Button* button : buttons)
		button->checkMouse(mouse, x, y);

	drawSelf();

	canvas.drawMatrix(x, y, frame.width, frame.height, (Color*)frame.pixels);
}

void Widget::drawSelf()
{
	for (Region* region : regions)
		body.drawRect(region->body);

	for (Button* button : buttons)
		button->draw(body);

	for (Textbox* text : textboxes)
		text->draw(body);
}

Button& Widget::button(std::string name)
{
	static Button dummy;
	for (Button* button : buttons)
	{
		if (button->name.compare(name) == 0)
		{
			return *button;
		}
	}
	return dummy;
}
Textbox& Widget::textbox(std::string name)
{
	static Textbox dummy;
	for (Textbox* text : textboxes)
	{
		if (text->name.compare(name) == 0)
		{
			return *text;
		}
	}
	return dummy;
}
Region& Widget::region(std::string name)
{
	static Region dummy;
	for (Region* region : regions)
	{
		if (region->name.compare(name) == 0)
		{
			return *region;
		}
	}
	return dummy;
}

Widget::~Widget()
{
	delete frame.pixels;
	for (Region* region : regions)
		delete region;

	for (Button* button : buttons)
		delete button;

	for (Textbox* text : textboxes)
		delete text;
}