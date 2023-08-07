#ifndef MOUSE_INFO
#define MOUSE_INFO
#include <windows.h>

class MouseInfo
{
private:
	bool left_down = false;
	bool prev_left_down = false;
	bool left_click = false;
	
	bool right_down = false;
	bool prev_right_down = false;
	bool right_click = false;
	
	void setLeftClick();
	void setRightClick();
	
	void whenCaptured();
	void centerCursor();
	void bindToWindow();
	
	int prev_x = 0;
	int prev_y = 0;
	bool tracking_movement = false;
	bool captured = true;
	
	HWND window_handle;
	
public:
	int x, y;
	int delta_x, delta_y;
	
	MouseInfo(){}
	
	void update(HWND hwnd);
	
	void leftDownEvent();
	void leftUpEvent();
	bool leftIsDown();
	bool leftClick();
	
	void rightDownEvent();
	void rightUpEvent();
	bool rightIsDown();
	bool rightClick();
	
	void capture();
	void release();
	bool isCaptured();
	
	void movedEvent(HWND hwnd);
	void leftWindowEvent();
	void enteredWindowEvent(HWND hwnd);
};

#endif
