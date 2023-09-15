#include "MouseInfo.h"
#include <iostream>

void MouseInfo::update(HWND hwnd)
{
	window_handle = hwnd;
	setLeftClick();
	setRightClick();
	left_held = left_down;
	right_held = right_down;
	if (captured)
		whenCaptured();

	delta_x = x - prev_x;
	delta_y = y - prev_y;

	prev_x = x;
	prev_y = y;
}

void MouseInfo::movedEvent(HWND hwnd, LPARAM lParam)
{
	x = lParam & (long)0xffff;
	y = (lParam & (long)0xffff0000) >> 16;

	enteredWindowEvent(hwnd);
}

void MouseInfo::leftDownEvent()
{
	left_down = true;
}
void MouseInfo::leftUpEvent()
{
	left_down = false;
}
void MouseInfo::setLeftClick()
{
	if(left_down && !left_held)
		left_click = true;
	else
		left_click = false;
}
bool MouseInfo::leftIsDown()
{
	return left_down;
}
bool MouseInfo::leftClick()
{
	return left_click;
}
bool MouseInfo::leftHeld()
{
	return left_held;
}
void MouseInfo::rightDownEvent()
{
	right_down = true;
}
void MouseInfo::rightUpEvent()
{
	right_down = false;
}
void MouseInfo::setRightClick()
{
	if(right_down && !right_held)
		right_click = true;
	else
		right_click = false;
}
bool MouseInfo::rightIsDown()
{
	return right_down;
}
bool MouseInfo::rightClick()
{
	return right_click;
}
bool MouseInfo::rightHeld()
{
	return right_held;
}
void MouseInfo::collectRawData(LPARAM lParam)
{
	UINT dwSize = sizeof(RAWINPUT);
	static BYTE lpb[sizeof(RAWINPUT)];

	UINT result = GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		raw_x += raw->data.mouse.lLastX;
		raw_y += raw->data.mouse.lLastY;
	}
}
void MouseInfo::whenCaptured()
{
	delta_x_raw = raw_x * sensitivity / 100;
	delta_y_raw = raw_y * sensitivity / 100;

	raw_x = raw_y = 0;

	centerCursor();
}
void MouseInfo::centerCursor()
{
	RECT rc;
	GetClientRect(window_handle, &rc);
	POINT pt = { (rc.left + rc.right) / 2 - 1, (rc.top + rc.bottom) / 2 - 1};
	x = pt.x;
	y = pt.y;
	ClientToScreen(window_handle, &pt);
	SetCursorPos(pt.x, pt.y);
}
void MouseInfo::bindToWindow()
{
	if(window_handle == NULL) return;
	
	RECT rc;
	GetClientRect(window_handle, &rc);
	
	POINT pt = { rc.left, rc.top };
	POINT pt2 = { rc.right, rc.bottom };
	ClientToScreen(window_handle, &pt);
	ClientToScreen(window_handle, &pt2);
	SetRect(&rc, pt.x, pt.y, pt2.x - 1, pt2.y - 1);
	
	ClipCursor(&rc);
}
void MouseInfo::capture()
{
	captured = true;
	bindToWindow();
	whenCaptured();
}
void MouseInfo::release()
{
	ClipCursor(NULL);
	captured = false;
}
bool MouseInfo::isCaptured()
{
	return captured;
}
void MouseInfo::leftWindowEvent()
{
	release();
	tracking_movement = false;
	delta_x_raw = delta_y_raw = 0;
}
void MouseInfo::enteredWindowEvent(HWND hwnd)
{
	if(tracking_movement == false)
	{
		window_handle = hwnd;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = hwnd;
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.dwHoverTime = 0;
		TrackMouseEvent(&tme);
		
		if(captured)
			centerCursor();
		
		prev_x = x;
		prev_y = y;
		tracking_movement = true;
	}
}
