#include "ScreenElement.h"

ScreenElement::ScreenElement(std::string name)
{
	setName(name);
}

ScreenElement::ScreenElement(Coord pos, Buffer& body, std::string name)
{
	setPos(pos);
	setBody(body);
	setName(name);
}

void ScreenElement::draw(Canvas& canvas)
{
	canvas.drawMatrix(pos.x, pos.y, body);
}

std::string ScreenElement::getName() const
{
	return name;
}

void ScreenElement::setName(std::string name)
{
	this->name = name;
}

void ScreenElement::setBody(const Buffer& body)
{
	this->body = body;
}

void ScreenElement::setPos(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}

void ScreenElement::setPos(Coord pos)
{
	this->pos = pos;
}

void ScreenElement::setSize(int width, int height)
{
	this->body.setSize(width, height);
}

Buffer& ScreenElement::getBody()
{
	return body;
}

Coord ScreenElement::getPos() const
{
	return pos;
}

Coord ScreenElement::getSize() const
{
	return Coord(body.getWidth(), body.getHeight());
}