#include "Widget.h"

Widget::Widget(int x, int y, int width, int height)
{
	setPos(x, y);
	setSize(width, height);

	regions.push_back(Region(Rect(0, 0, width, height, Color::LIGHT_GRAY, Color::DARK_GRAY), "default"));
}

Widget::Widget(
	int x, int y, int width, int height,
	std::initializer_list<Button> buttons,
	std::initializer_list<Textbox> textboxes,
	std::initializer_list<Region> regions)
{
	setPos(x, y);
	setSize(width, height);

	for (Button b : buttons)
		this->buttons.push_back(b);

	for (Textbox t : textboxes)
		this->textboxes.push_back(t);

	for (Region r : regions)
		this->regions.push_back(r);
}

Widget::Widget(const Widget& other)
{
	*this = other;
}
Widget& Widget::operator=(const Widget& other)
{
	if (this == &other)
		return *this;

	setPos(other.getX(), other.getY());

	setSize(other.getWidth(), other.getHeight());

	this->buttons = other.copyButtons();
	this->textboxes = other.copyTextboxes();
	this->regions = other.copyRegions();

	return *this;
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

int Widget::getX() const
{
	return x;
}

int Widget::getY() const
{
	return y;
}

int Widget::getWidth() const
{
	return frame.width;
}

int Widget::getHeight() const
{
	return frame.height;
}

void Widget::setSize(int width, int height)
{
	delete[] frame.pixels;
	frame.pixels = new uint32_t[width * height];
	frame.width = width;
	frame.height = height;
	body = Canvas(&frame);
}

void Widget::checkMouse(MouseInfo& mouse)
{
	for (int i = 0; i < buttons.size(); i++)
		buttons[i].checkMouse(mouse, x, y);
	//for (Button& button : buttons)
	//	button.checkMouse(mouse, x, y);
}

void Widget::draw(Canvas& canvas)
{
	drawSelf();

	canvas.drawMatrix(x, y, frame.width, frame.height, (Color*)frame.pixels);
}

void Widget::drawSelf()
{
	for (Region& region : regions)
		body.drawRect(region.body);

	for (Button& button : buttons)
		button.draw(body);

	for (Textbox& text : textboxes)
		text.draw(body);
}

bool Widget::isAlive()
{
	return alive;
}

Button* Widget::button(std::string name)
{
	for (Button& button : buttons)
	{
		if (button.name.compare(name) == 0)
		{
			return &button;
		}
	}
	return nullptr;
}
Textbox* Widget::textbox(std::string name)
{
	for (Textbox& text : textboxes)
	{
		if (text.name.compare(name) == 0)
		{
			return &text;
		}
	}
	return nullptr;
}
Region* Widget::region(std::string name)
{
	for (Region& region : regions)
	{
		if (region.name.compare(name) == 0)
		{
			return &region;
		}
	}
	return nullptr;
}

std::vector<Button> Widget::copyButtons() const
{
	return buttons;
}
std::vector<Textbox> Widget::copyTextboxes() const
{
	return textboxes;
}
std::vector<Region> Widget::copyRegions() const
{
	return regions;
}

Widget::~Widget()
{
	delete[] frame.pixels;

	regions.clear();
	buttons.clear();
	textboxes.clear();
}