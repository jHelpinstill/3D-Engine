#pragma once
#ifndef WIDGET_
#define WIDGET_

#include "Canvas.h"
#include "MouseInfo.h"
#include "Textbox.h"
#include "Color.h"
#include "Button.h"
#include "Rect.h"

#include <vector>
#include <string>
#include <initializer_list>

struct Region
{
	Rect body;
	std::string name;
	Region() {}
	Region(Rect body, std::string name)
	{
		this->body = body;
		this->name = name;
	}
};

class Widget
{
private:

	int x;
	int y;

	Frame frame;
	Canvas body;

	std::vector<Button*> buttons;
	std::vector<Textbox*> textboxes;
	std::vector<Region*> regions;

	void drawSelf();

public:

	Widget() {}
	Widget(int x, int y, int width, int height);
	Widget(
		int x, int y, int width, int height,
		std::initializer_list<Button*> buttons,
		std::initializer_list<Textbox*> textboxes,
		std::initializer_list<Region*> regions);

	void setPos(int x, int y);
	void shiftPos(int x, int y);
	int getX();
	int getY();
	void setSize(int width, int height);
	void draw(Canvas& canvas, MouseInfo& mouse);

	Button& button(std::string name);
	Textbox& textbox(std::string name);
	Region& region(std::string name);

	~Widget();
};

#endif