#ifndef MOUSE_INFO
#define MOUSE_INFO
#include <windows.h>

class MouseInfo
{
private:
	bool left_down = false;
	bool left_held = false;
	bool left_click = false;
	
	bool right_down = false;
	bool right_held = false;
	bool right_click = false;
	
	void setLeftClick();
	void setRightClick();
	
	void whenCaptured();
	void centerCursor();
	void bindToWindow();
	
	int prev_x = 0;
	int prev_y = 0;
	long raw_x, raw_y;
	bool tracking_movement = false;
	bool captured = false;
	
	HWND window_handle;
	
	
public:
	int x, y;
	int delta_x, delta_y;
	float delta_x_raw, delta_y_raw;

	float sensitivity = 10;
	
	MouseInfo(){}
	
	void update(HWND hwnd);
	
	void leftDownEvent();
	void leftUpEvent();
	bool leftIsDown();
	bool leftClick();
	bool leftHeld();
	
	void rightDownEvent();
	void rightUpEvent();
	bool rightIsDown();
	bool rightClick();
	bool rightHeld();
	
	void capture();
	void release();
	bool isCaptured();
	
	void movedEvent(HWND hwnd, LPARAM lParam);
	void collectRawData(LPARAM lParam);
	void leftWindowEvent();
	void enteredWindowEvent(HWND hwnd);
};

#endif
