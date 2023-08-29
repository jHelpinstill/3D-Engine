#ifndef TEXT_BOX_
#define TEXT_BOX_

#include "Canvas.h"
#include "Color.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <sstream>

struct LetterBits
{
	unsigned int bytes[2];
};

class TextBox
{
private:
	int x = 0;
	int y = 0;
	int width = -1;
	float scale = 2;
	std::string text;
	Color color = 0x0;
	
	static LetterBits letters[128];
	int cursor_x = 0;
	int cursor_y = 0;

	void drawChar(Canvas& canvas, char c);
	
public:
	TextBox(){}
	TextBox(int x, int y);
	TextBox(int x, int y, std::string text);
	TextBox(int x, int y, std::string text, float scale);
	TextBox(int x, int y, std::string text, float scale, Color color);
	
	void setPos(int x, int y);
	void setScale(float scale);
	void setColor(Color color);
	
	void print(const std::string str);
	void print(double val);
	void print(int val);
	
	void clear();
	void draw(Canvas &canvas);
	int getLength();
	float getScale();
};

#endif
