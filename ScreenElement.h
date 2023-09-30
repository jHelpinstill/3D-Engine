#pragma once
#ifndef SCREEN_ELEMENT
#define SCREEN_ELEMENT

#include <string>
#include "Rect.h"
#include "Canvas.h"

struct Coord
{
	union
	{
		struct { int x, y; };
		struct { int width, height; };
	};
	Coord() { x = 0; y = 0; }
	Coord(int x, int y) { this->x = x; this->y = y; }
};

class ScreenElement
{
protected:
	std::string name = "";
	Coord pos;
	Buffer body;

public:
	ScreenElement() : pos(Coord(0, 0)) {}
	ScreenElement(std::string name);
	ScreenElement(Coord pos, Buffer& body, std::string name = "");

	void draw(Canvas& canvas);

	std::string getName() const;
	void setName(std::string name);

	void setBody(const Buffer& body);
	
	void setPos(int x, int y);
	void setPos(Coord pos);
	void setSize(int width, int height);

	Buffer& getBody();
	Coord getPos() const;
	Coord getSize() const;
};

#endif