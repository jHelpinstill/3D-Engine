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
