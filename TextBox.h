#ifndef TEXT_BOX_
#define TEXT_BOX_

#include "Canvas.h"
#include "Color.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include "ScreenElement.h"
#include "Buffer.h"

struct LetterBits
{
	unsigned int bytes[2];
};

class Textbox : public ScreenElement
{
public:
	enum class Adjustment
	{
		LEFT,
		RIGHT,
		CENTER
	};

protected:
	std::string text;
	float text_scale = 1;
	Color text_color = 0x0;
	Adjustment adjustment = Adjustment::LEFT;
	
	static LetterBits letters[128];
	int cursor_x = 0;
	int cursor_y = 0;

	void drawChar(Canvas& canvas, char c);
	
public:

	Textbox(){}
	Textbox(int x, int y, int width, int height);
	Textbox(int x, int y, int width, int height, std::string text, float scale = 1, Color color = Color::BLACK, Adjustment adjustment = Adjustment::LEFT, std::string name = "");
	
	void setTextScale(float scale);
	void setTextColor(Color color);
	void setAdjustment(Adjustment adjustment);
	
	void print(const std::string str);
	void print(double val);
	void print(int val, bool hex = false);

	void render();

	template <typename T>
	void println(T o)
	{
		print(o);
		print("\n");
	}
	
	void clear();
	int getLength();
	float getScale();
};

#endif