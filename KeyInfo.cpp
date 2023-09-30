#include "KeyInfo.h"

void KeyInfo::keyDownEvent(int key_code)
{
	if(key_code < 0 || key_code > 99)
		return;
	keys[key_code].down = true;
	keys[key_code].pressed = false;
	if(keys[key_code].prev_down == false)
		keys[key_code].pressed = true;
	keys[key_code].prev_down = true;

	buffer += (char)key_code;
	if (buffer.length() > 25)
		buffer = buffer.substr(1);
}

void KeyInfo::keyUpEvent(int key_code)
{
	if(key_code < 0 || key_code > 99)
		return;
	keys[key_code].down = false;
	keys[key_code].prev_down = false;
}

void KeyInfo::update()
{
	for(int i = 0; i < 100; i++)
		keys[i].pressed = false;
}

bool KeyInfo::keyPressed(int c)
{
	return keys[c].pressed;
}
bool KeyInfo::keyHeld(int c)
{
	return keys[c].down;
}

bool KeyInfo::available()
{
	return !buffer.empty();
}
char KeyInfo::readBuffer()
{
	if (buffer.empty())
		return 0;
	char c = buffer.at(0);
	buffer = buffer.substr(1);
	return c;
}
std::string KeyInfo::getBuffer()
{
	std::string line = buffer;
	buffer.clear();
	return line;
}