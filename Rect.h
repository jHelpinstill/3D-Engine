#pragma once
#ifndef RECT_
#define RECT_

#include "Color.h"

struct Rect
{
	int x;
	int y;
	int width;
	int height;
	Color fill_color;
	Color border_color;
	Rect() {}
	Rect(int x, int y, int width, int height, Color color)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->fill_color = color;
		this->border_color = color;
	}
	Rect(int x, int y, int width, int height, Color fill_color, Color border_color)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->fill_color = fill_color;
		this->border_color = border_color;
	}
};

#endif