#ifndef BUTTON_
#define BUTTON_

#include "Canvas.h"
#include "MouseInfo.h"
#include "Textbox.h"
#include "Color.h"
#include "Rect.h"
#include <string>
#include "ScreenElement.h"

class Button : public ScreenElement
{
public:
	enum class ClickEffect
	{
		NONE,
		GRAYER_FILL,
		GRAYER_BORDER,
		GRAYER_ALL,
		LIGHTER_ALL
	};

protected:
	ClickEffect click_effect = ClickEffect::NONE;

	Buffer pressed_body;
	void findPressedBody();
	void addText(std::string text);

	struct ButtonStates
	{
		bool hovered = false;
		bool pressed = false;
		bool clicked = false;
		bool grabbed = false;
		bool released = false;
	} states;
	
public:
	Button() {}
	Button(int x, int y, int width, int height, ClickEffect click_effect = ClickEffect::NONE, std::string name = "");
	Button(int x, int y, const Buffer& body, ClickEffect click_effect = ClickEffect::NONE, std::string name = "");
	Button(int x, int y, const Buffer& body, std::string text, ClickEffect click_effect = ClickEffect::NONE, std::string name = "");

	bool hovered();
	bool pressed();
	bool clicked();
	bool grabbed();
	bool released();

	void draw(Canvas& canvas);
	void checkMouse(MouseInfo& mouse);
	void checkMouse(MouseInfo& mouse, int x, int y);

	static Buffer standardBody(int width, int height, Color fill_color = Color::LIGHT_GRAY, Color border_color = Color::GRAY);

	void debug_print();
	std::string debug_string();
};

#endif