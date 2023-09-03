#include <windows.h>
#include <chrono>
#include <iostream>
#include <vector>

#include "Engine3D.h"

namespace Engine3D
{
	int millis_per_frame = 10;

	Frame frame = { 0 };

	MouseInfo mouse;
	KeyInfo keyboard;

	BITMAPINFO frame_bitmap_info;
	HBITMAP frame_bitmap = 0;
	HDC frame_device_context = 0;

	bool init_box = false;
}

//void frameLoop(HWND hwnd)
//{
//	static std::vector<Mesh*> mesh_list;
//	static Camera camera(Vec3(-4, 2, 0.5));
//	
//	if(!Engine3D::init_box)
//	{
//		mesh_list.push_back(new Mesh("mesh_files/box_mesh.txt"));
//		Engine3D::init_box = true;
//		std::cout << "box added to mesh list." << std::endl;
//	}
//	
//	render(Engine3D::frame, camera, Engine3D::mouse, Engine3D::keyboard, mesh_list);
//	
//	Engine3D::mouse.update(hwnd);
//	Engine3D::keyboard.update();
//	
//	InvalidateRect(hwnd, NULL, false);
//	UpdateWindow(hwnd);
//}

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		//case WM_KEYDOWN: // same as pressing the X button:
    case WM_CLOSE:
		{
			DestroyWindow(hwnd);
			return 0;
		}
		case WM_PAINT:
		{
			static PAINTSTRUCT paint;
			static HDC device_context;
			device_context = BeginPaint(hwnd, &paint);
			BitBlt(	device_context,
							paint.rcPaint.left, paint.rcPaint.top,
							paint.rcPaint.right - paint.rcPaint.left,
							paint.rcPaint.bottom - paint.rcPaint.top,
							Engine3D::frame_device_context,
							paint.rcPaint.left, paint.rcPaint.top,
							SRCCOPY);
			EndPaint(hwnd, &paint);
			return 0;
		}
	  case WM_MOUSEMOVE:	
		{
			Engine3D::mouse.x = lParam & (long)0xffff;
			Engine3D::mouse.y = (lParam & (long)0xffff0000) >> 16;
			Engine3D::mouse.movedEvent(hwnd);
			return 0;
		}
		case WM_MOUSELEAVE:
		{
			Engine3D::mouse.leftWindowEvent();
			Engine3D::mouse.release();
//			std::cout << "mouse left window" << std::endl;
			return 0;
		}
		case WM_MOUSEHOVER:
		{
			Engine3D::mouse.enteredWindowEvent(hwnd);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			Engine3D::mouse.leftDownEvent();
			return 0;
		}
		case WM_LBUTTONUP:
		{
			Engine3D::mouse.leftUpEvent();
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			Engine3D::mouse.rightDownEvent();
			return 0;
		}
		case WM_RBUTTONUP:
		{
			Engine3D::mouse.rightUpEvent();
			return 0;
		}
		case WM_KEYDOWN:
		{		
//			std::cout << "key down: " << wParam << std::endl;
			Engine3D::keyboard.keyDownEvent(wParam);
	      return 0;
	   }

    	case WM_KEYUP:
      {		
//			std::cout << "key up: " << wParam << std::endl;
			Engine3D::keyboard.keyUpEvent(wParam);
	      return 0;
	   }
		case WM_SIZE:
		{			
			Engine3D::frame_bitmap_info.bmiHeader.biWidth = LOWORD(lParam);
			Engine3D::frame_bitmap_info.bmiHeader.biHeight = HIWORD(lParam);
			
			if(Engine3D::frame_bitmap) DeleteObject(Engine3D::frame_bitmap);
			Engine3D::frame_bitmap = CreateDIBSection(NULL, &Engine3D::frame_bitmap_info, DIB_RGB_COLORS, (void**)&Engine3D::frame.pixels, 0, 0);
			SelectObject(Engine3D::frame_device_context, Engine3D::frame_bitmap);
			
			Engine3D::frame.width = Engine3D::frame_bitmap_info.bmiHeader.biWidth;
			Engine3D::frame.height = Engine3D::frame_bitmap_info.bmiHeader.biHeight;
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = L"WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	Engine3D::frame_bitmap_info.bmiHeader.biSize = sizeof(Engine3D::frame_bitmap_info.bmiHeader);
	Engine3D::frame_bitmap_info.bmiHeader.biPlanes = 1;
	Engine3D::frame_bitmap_info.bmiHeader.biBitCount = 32;
	Engine3D::frame_bitmap_info.bmiHeader.biCompression = BI_RGB;
	Engine3D::frame_device_context = CreateCompatibleDC(0);

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"WindowClass", L"Jake's Renderererer",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		860, /* width */
		600, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(TRUE)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	 	{
	   	if (msg.message == WM_QUIT)
	     		break;
	   	TranslateMessage(&msg);
	   	DispatchMessage(&msg);
	 	}
	   else
	   {
	   		typedef std::chrono::high_resolution_clock hiresclock;
			static auto timer = hiresclock::now();
			double millisec = (hiresclock::now() - timer).count() / 1000000.0;
			if(millisec > Engine3D::millis_per_frame)
			{
	      		timer = hiresclock::now();
				Engine3D::frame.dt = millisec / 1000.0;

	        	Engine3D::frameLoop(hwnd);	// where library user implements their code

				Engine3D::mouse.update(hwnd);
				Engine3D::keyboard.update();

				InvalidateRect(hwnd, NULL, false);
				UpdateWindow(hwnd);
			}
		}
	}
	return msg.wParam;
}
