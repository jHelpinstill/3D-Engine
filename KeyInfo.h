#ifndef KEY_INFO_
#define KEY_INFO_
#include <string>

class KeyInfo
{
private:
	std::string buffer;

public:
	struct Key
	{
		bool pressed{}, down{}, prev_down{};
	};
	Key keys[100]{};
	
	KeyInfo(){}
	
	void keyDownEvent(int key_code);
	void keyUpEvent(int key_code);
	void update();
	
	bool keyPressed(int c);
	bool keyHeld(int c);

	bool available();
	char readBuffer();
	std::string getBuffer();
	
	static const int CTRL = 17;
	static const int SHIFT = 16;
};

#endif
