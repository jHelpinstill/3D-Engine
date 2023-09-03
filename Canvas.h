#ifndef CANVAS_
#define CANVAS_

#include "Frame.h"
#include "Color.h"
class Camera;

struct Point
{
	float x, y;
	Point() {}
	Point(float x, float y) { this->x = x; this->y = y; }
};

struct DepthBuffer
{
	float* buffer = nullptr;
	int width, height;
	DepthBuffer() {}
	DepthBuffer(int width, int height)
	{
		buffer = new float[width * height];
		for (int i = 0; i < (width * height); i++)
			buffer[i] = -1;
		this->width = width;
		this->height = height;
	}

	bool check(int x, int y, float depth)
	{
		int i = x + width * y;
		if (buffer[i] < 0)
		{
			buffer[i] = depth;
			return true;
		}
		if (buffer[i] > depth)
		{
			buffer[i] = depth;
			return true;
		}
		return false;
	}
	~DepthBuffer() { delete buffer; }
};

class Canvas
{
private:
	Frame* frame = nullptr;
	DepthBuffer depth_buffer;

	int cursor = 0;
	
	void swap(int &a, int &b);
	void swap(float &a, float &b);
	int signOf(float a);
	
	void fillUpperTri(int x0, int x1, int x2, int y0, int y1, Color (*colorFunc)(int, int));
	void fillLowerTri(int x0, int x1, int x2, int y0, int y1, Color (*colorFunc)(int, int));
	
	bool updated = false;

	void drawNextPoint(Color color);
	void setCursor(int x, int y);
	Color averageOfRegion(float x, float y, float region_width, float region_height, Color* buffer, int width, int height, Color background = Color::ALPHA);
	Color bilinearInterp(Point p, int width, int height, Color* buffer);

	static Color defaultColorFunc(int x, int y);
	static Color default_color;
	
public:
	Canvas(){}
	Canvas(Frame* frame);
	
	int getWidth();
	int getHeight();
	void getFrameRegion(int x, int y, int width, int height, int* buffer);

	void drawMatrix(int x, int y, int image_width, int image_height, Color* buffer);
	void lerpDrawMatrix(Point pos, int image_width, int image_height, float scale, Color* buffer);
	
	void drawPoint(int x, int y, Color color = Color(0));
	void drawPoint(int x, int y, Color (*colorFunc)(int, int, DepthBuffer&));
	void drawLine(int x0, int y0, int x1, int y1, Color color = Color(0));
	void drawRect(int x, int y, int width, int height, Color color = Color(0));
	void fillRect(int x, int y, int width, int height, Color color = Color(0));
	void fill(Color color);
	void drawCircle(int x, int y, int radius, Color color = Color(0));
	void fillCircle(int x, int y, int radius, Color color = Color(0));
	void fillCircle(int x, int y, int radius, Color (*colorFunc)(int, int, DepthBuffer&));
	void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color);
	void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color (*colorFunc)(int, int));
	void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color);
	
	void drawPoint(Point p, Color color = Color(0));
	void lerpDrawPoint(Point p, float size, Color color = Color::BLACK);
	void drawLine(Point p0, Point p1, Color color = Color(0));
	void drawRect(Point p, int width, int height, Color color = Color(0));
	void fillRect(Point p, int width, int height, Color color = Color(0));
	void drawCircle(Point c, int radius, Color color = Color(0));
	void fillCircle(Point c, int radius, Color color = Color(0));
	void drawTriangle(Point p0, Point p1, Point p2, Color color);
	void fillTriangle(Point p0, Point p1, Point p2, Color (*colorFunc)(int, int));
	void fillTriangle(Point p0, Point p1, Point p2, Color color);

	~Canvas();
};

#endif
