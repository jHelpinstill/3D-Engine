#ifndef KEY_INFO_
#define KEY_INFO_

class KeyInfo
{
public:
	struct Key {bool pressed, down, prev_down;};
	Key keys[100];
	
	KeyInfo(){}
	
	void keyDownEvent(int key_code);
	void keyUpEvent(int key_code);
	void update();
	
	bool keyPressed(int c);
	bool keyHeld(int c);
	
	static const int CTRL = 17;
	static const int SHIFT = 16;
};

#endif
