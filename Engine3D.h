#pragma once

#ifndef ENGINE_3D
#define ENGINE_3D

#include <windows.h>

#include "MouseInfo.h"
#include "KeyInfo.h"
#include "Canvas.h"
#include "Frame.h"

#include "Mesh.h"
#include "Camera.h"
#include "Vec3.h"

namespace Engine3D
{
	extern int millis_per_frame;

	extern Frame frame;

	extern MouseInfo mouse;
	extern KeyInfo keyboard;

	extern BITMAPINFO frame_bitmap_info;
	extern HBITMAP frame_bitmap;
	extern HDC frame_device_context;

	extern bool init_box;

	void frameLoop(HWND hwnd);
}

#endif