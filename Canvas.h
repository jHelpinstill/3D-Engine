#ifndef CANVAS_
#define CANVAS_

#include "Frame.h"
#include "Color.h"

struct Point
{
	float x, y;
	Point() {}
	Point(float x, float y) { this->x = x; this->y = y; }
};

class Canvas
{
private:
	Frame* frame = nullptr;

	int cursor = 0;
	
	void swap(int &a, int &b);
	void swap(float &a, float &b);
	int signOf(float a);
	
	void fillUpperTri(int x0, int x1, int x2, int y0, int y1, Color (*colorFunc)(int, int));
	void fillLowerTri(int x0, int x1, int x2, int y0, int y1, Color (*colorFunc)(int, int));
	
	bool updated = false;

	void drawNextPoint(Color color);
	void setCursor(int x, int y);
	
	static Color defaultColorFunc(int x, int y);
	static Color default_color;
	
public:
	Canvas(){}
	Canvas(Frame* frame);
	
	int getWidth();
	int getHeight();
	
	void drawPoint(int x, int y, Color color = Color(0));
	void drawLine(int x0, int y0, int x1, int y1, Color color = Color(0));
	void drawRect(int x, int y, int width, int height, Color color = Color(0));
	void fillRect(int x, int y, int width, int height, Color color = Color(0));
	void fill(Color color);
	void drawCircle(int x, int y, int radius, Color color = Color(0));
	void fillCircle(int x, int y, int radius, Color color = Color(0));
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
};

#endif
