#include "MouseInfo.h"
#include <iostream>

void MouseInfo::update(HWND hwnd)
{
	window_handle = hwnd;
	setLeftClick();
	setRightClick();
	prev_left_down = left_down;
	prev_right_down = right_down;
}

void MouseInfo::movedEvent(HWND hwnd)
{
	enteredWindowEvent(hwnd);
	if(captured)
	{
		whenCaptured();
		return;
	}
	
	delta_x = x - prev_x;
	delta_y = y - prev_y;
	
	prev_x = x;
	prev_y = y;
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
	if(left_down && !prev_left_down)
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
	if(right_down && !prev_right_down)
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
void MouseInfo::whenCaptured()
{
	delta_x = x - prev_x;
	delta_y = y - prev_y;
	
	centerCursor();
	bindToWindow();
	
	prev_x = x;
	prev_y = y;
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
	
	
//	RECT rc;
//	GetClientRect(window_handle, &rc);
//	
//	POINT pt = { (rc.left + rc.right) / 2 - 1, (rc.top + rc.bottom) / 2 - 1};
//	x = pt.x;
//	y = pt.y;
////	POINT pt2 = { (rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2};
//	ClientToScreen(window_handle, &pt);
////	ClientToScreen(window_handle, &pt2);
//	SetRect(&rc, pt.x, pt.y, pt.x, pt.y);
//	
//	ClipCursor(&rc);
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
	SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);
	
	ClipCursor(&rc);
}
void MouseInfo::capture()
{
	captured = true;
	whenCaptured();
	delta_x = delta_y = 0;
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
	tracking_movement = false;
	delta_x = delta_y = 0;
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
