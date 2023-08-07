#include "Canvas.h"
#include <iostream>
#include <cmath>

Canvas::Canvas(Frame* frame)
{
	this->frame = frame;
}

int Canvas::getWidth()
{
	return frame->width;
}

int Canvas::getHeight()
{
	return frame->height;
}

void Canvas::getFrameRegion(int x, int y, int width, int height, int* buffer)
{
	// add safety features!

	for (int j = 0; j < height; j++)
	{
		int p = x + ((frame->height - 1) - (y + j)) * frame->width;
		for (int i = 0; i < width; i++)
			buffer[j * width + i] = frame->pixels[p + i];
	}
}
	
void Canvas::drawPoint(int x, int y, Color color)
{
	if(x >= frame->width || y >= frame->height || x < 0 || y < 0)
		return;
	int p = x + ((frame->height - 1) - y) * frame->width;
	frame->pixels[p] = Color::occludeFast(color.val, frame->pixels[p]); //color.occludeFast(frame->pixels[p]);
}

void Canvas::drawNextPoint(Color color)
{
	frame->pixels[cursor] = Color::occludeFast(color.val, frame->pixels[cursor]);
	cursor++;
}

void Canvas::setCursor(int x, int y)
{
	cursor = x + ((frame->height - 1) - y) * frame->width;
}

void Canvas::lerpDrawPoint(Point p, float size, Color color)
{
	int x0, x1, y0, y1;
	float radius = size / 2;

	x0 = floor(p.x - radius);
	x1 = ceil(p.x + radius);

	y0 = floor(p.y - radius);
	y1 = floor(p.y + radius);

	if (x0 < 0) return;
	if (x1 > frame->width) return;
	if (y0 < 0) return;
	if (y1 > frame->height) return;

	float t0, t1, s0, s1;
	t0 = (p.x - radius) - x0;
	t1 = x1 - (p.x + radius);
	s0 = (p.y - radius) - y0;
	s1 = y1 - (p.y + radius);

	int opacity = 255 - color.getAlpha();

	if (size > 1)
	{
		// body
		fillRect(x0 + 1, y0 + 1, x1 - x0 - 2, y1 - y0 - 2, color);

		// top edge
		color.setAlpha(opacity * s0);
		setCursor(x0 + 1, y0);
		for (int i = x0 + 1; i < x1 - 1; i++)
			drawNextPoint(color);

		// bottom edge
		color.setAlpha(opacity * s1);
		setCursor(x0 + 1, y1 - 1);
		for (int i = x0 + 1; i < x1 - 1; i++)
			drawNextPoint(color);

		// left edge
		color.setAlpha(opacity * t0);
		for (int i = y0 + 1; i < y1 - 1; i++)
		{
			setCursor(x0, i);
			drawNextPoint(color);
		}

		// right edge
		color.setAlpha(opacity * t1);
		for (int i = y0 + 1; i < y1 - 1; i++)
		{
			setCursor(x1 - 1, i);
			drawNextPoint(color);
		}
	}

	// top left corner
	color.setAlpha(opacity * (1 - (t0 * s0)));
	setCursor(x0, y0);
	drawNextPoint(color);

	// top right corner
	color.setAlpha(opacity * (1 - (t1 * s0)));
	setCursor(x1 - 1, y0);
	drawNextPoint(color);
	
	// bottom left corner
	color.setAlpha(opacity * (1 - (t0 * s1)));
	setCursor(x0, y1 - 1);
	drawNextPoint(color);
	
	// bottom right corner
	color.setAlpha(opacity * (1 - (t1 * s1)));
	setCursor(x1 - 1, y1 - 1);
	drawNextPoint(color);
}

void Canvas::drawLine(int x0, int y0, int x1, int y1, Color color)
{
	float rise = (y1 - y0);
	float run = (x1 - x0);
	float m = rise / run;
	float m_mag = (m < 0) ? -m : m;
	
	int code = 0;
	if(rise < 0) code += 1;
	if(run < 0) code += 2;
	if(m_mag > 1) code += 4;
	
	int dir = 1;
	bool steep = false;
	
	switch(code)
	{
		case 4: steep = true;
		case 0:
			break;
		case 6: steep = true;
		case 1:
			dir = -1;
			break;
		case 5: steep = true;
		case 2:
			swap(x0, x1);
			swap(y0, y1);
			dir = -1;
			break;
		case 7: steep = true;
		case 3:
			swap(x0, x1);
			swap(y0, y1);
			break;
	}
	float accumulator = 0.5;
	m *= dir;
	if(!steep)
	{
		int y = y0;
		for(int x = x0; x < x1; x++)
		{
			drawPoint(x, y, color);
			accumulator += m;
			if(accumulator > 1)
			{
				y += dir;
				accumulator -= 1;
			}
		}
	}
	else
	{
		m = 1 / m;
		int x = x0;
		for(int y = y0; y < y1; y++)
		{
			drawPoint(x, y, color);
			accumulator += m;
			if(accumulator > 1)
			{
				x += dir;
				accumulator -= 1;
			}
		}
	}
}

void Canvas::drawRect(int x, int y, int width, int height, Color color)
{
	for(int i = 0; i < width; i++)
	{
		drawPoint(x + i, y, color);
		drawPoint(x + i, y + height, color);
	}
	for(int i = 0; i < height; i++)
	{
		drawPoint(x, y + i, color);
		drawPoint(x + width, y + i, color);
	}
}

void Canvas::fillRect(int x, int y, int width, int height, Color color)
{
	if (x >= frame->width) return;
	if (y >= frame->height) return;

	int x1 = x + width + 1;
	int y1 = y + height + 1;
	if (x1 < 0) return;
	if (y1 < 0) return;

	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x1 > frame->width) x1 = frame->width;
	if (y1 > frame->height) y1 = frame->height;

	for (int i = y; i < y1; i++)
	{
		setCursor(x, i);
		for (int j = x; j < x1; j++)
			drawNextPoint(color);
	}


	//for(int i = x; i < x + width; i++)
	//{
	//	for(int j = y; j < y + height; j++)
	//	{
	//		drawPoint(i, j, color);
	//	}
	//}
}

void Canvas::fill(Color color)
{
	for(int x = 0; x < frame->width; x++)
	{
		for(int y = 0; y < frame->height; y++)
		{
			frame->pixels[x + y * frame->width] = color.val;
		}
	}
}

void Canvas::drawCircle(int x, int y, int radius, Color color)
{
//	std::cout << "drawCircle..." << std::endl;
	int point_x = radius;
	int point_y = 0;
	float accumulator = 0.5;
	
	while(point_y <= point_x)
	{
		drawPoint(x + point_x, y + point_y, color);
		drawPoint(x + point_x, y - point_y, color);
		drawPoint(x - point_x, y + point_y, color);
		drawPoint(x - point_x, y - point_y, color);
		
		drawPoint(x + point_y, y + point_x, color);
		drawPoint(x + point_y, y - point_x, color);
		drawPoint(x - point_y, y + point_x, color);
		drawPoint(x - point_y, y - point_x, color);
		
		accumulator += point_x - sqrt(point_x * point_x - 2 * point_y - 1);
		if(accumulator > 1)
		{
			accumulator -= 1;
			point_x--;
		}
		point_y++;
	}
}

void Canvas::fillCircle(int x, int y, int radius, Color color)
{
	int point_x = radius;
	int point_y = 0;
	float accumulator = 0.5;
	
	while(point_y <= point_x)
	{
		for(int i = 0; i < point_y * 2; i++)
		{
			drawPoint(x + point_x, y + point_y - i, color);
			drawPoint(x - point_x, y + point_y - i, color);
		}
		for(int i = 0; i < point_x * 2; i++)
		{
			drawPoint(x + point_y, y + point_x - i, color);
			drawPoint(x - point_y, y + point_x - i, color);
		}
		accumulator += point_x - sqrt(point_x * point_x - 2 * point_y - 1);
		if(accumulator > 1)
		{
			accumulator -= 1;
			point_x--;
		}
		point_y++;
	}
}

void Canvas::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color)
{
	drawLine(x0, y0, x1, y1, color);
	drawLine(x1, y1, x2, y2, color);
	drawLine(x2, y2, x0, y0, color);
}

void Canvas::fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color)
{
	default_color = color;
	fillTriangle(x0, y0, x1, y1, x2, y2, defaultColorFunc);
}

void Canvas::fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color (*colorFunc)(int, int))
{
	int points[3][2];
	points[0][0] = x0;
	points[0][1] = y0;
	points[1][0] = x1;
	points[1][1] = y1;
	points[2][0] = x2;
	points[2][1] = y2;
	
	//	Sort points by lowest y value
	if(points[0][1] > points[1][1])
	{
		swap(points[0][1], points[1][1]);
		swap(points[0][0], points[1][0]);
	}
	if(points[1][1] > points[2][1])
	{
		swap(points[1][1], points[2][1]);
		swap(points[1][0], points[2][0]);
	}
	if(points[0][1] > points[1][1])
	{
		swap(points[0][1], points[1][1]);
		swap(points[0][0], points[1][0]);
	}
	
	if(points[0][1] == points[1][1])
	{
		fillLowerTri(points[2][0], points[0][0], points[1][0], points[1][1], points[2][1], colorFunc);
		return;
	}
	
	if(points[1][1] == points[2][1])
	{
		fillUpperTri(points[0][0], points[1][0], points[2][0], points[0][1], points[1][1], colorFunc);
		return;
	}
	
	int mid_x = points[0][0] + ((points[2][0] - points[0][0]) * (points[1][1] - points[0][1])) / (points[2][1] - points[0][1]);
	
	fillUpperTri(points[0][0], points[1][0], mid_x, points[0][1], points[1][1], colorFunc);
	fillLowerTri(points[2][0], points[1][0], mid_x, points[1][1], points[2][1], colorFunc);
}

void Canvas::fillUpperTri(int x0, int x1, int x2, int y0, int y1, Color (*colorFunc)(int, int))
{
//	color = 0x0000ff;
	
	if(y1 == y0) for(int i = x1; i < x2; i++)
	{
		drawPoint(i, y0, colorFunc(i, y0));
		return;
	}
	
	int y = y0;
	int x = x0;
	int xf = x0;
	
	if(x2 < x1)
		swap(x1, x2);
	
	float m1 = (x1 - x0) / (float)(y1 - y0);
	float m2 = (x2 - x0) / (float)(y1 - y0);
	
	int dir1 = signOf(m1);
	int dir2 = signOf(m2);
	
	float m1_mag = m1 / dir1;
	float m2_mag = m2 / dir2;
	
	float accum1 = 0.5;
	float accum2 = 0.5;
	
	while(y < y1)
	{
		for(int i = x; i <= xf; i++)
			drawPoint(i, y, colorFunc(i, y));
			
		accum1 += m1_mag;
		while(accum1 > 1)
		{
			accum1 -= 1;
			x += dir1;
		}
		
		accum2 += m2_mag;
		while(accum2 > 1)
		{
			accum2 -= 1;
			xf += dir2;
		}
		y++;
	}
}

void Canvas::fillLowerTri(int x0, int x1, int x2, int y0, int y1, Color (*colorFunc)(int, int))
{
//	color = 0x00ff00;
	
	if(y1 == y0) for(int i = x1; i < x2; i++)
	{
		drawPoint(i, y0, colorFunc(i, y0));
		return;
	}
	
	if(x2 < x1)
		swap(x1, x2);
	
	int y = y0;
	int x = x1;
	int xf = x2;
	
	float m1 = (x0 - x1) / (float)(y1 - y0);
	float m2 = (x0 - x2) / (float)(y1 - y0);
	
	int dir1 = signOf(m1);
	int dir2 = signOf(m2);
	
	float m1_mag = m1 / dir1;
	float m2_mag = m2 / dir2;
	
	float accum1 = 0.5;
	float accum2 = 0.5;
	
	while(y < y1)
	{	
		for(int i = x; i <= xf; i++)
			drawPoint(i, y, colorFunc(i, y));
		
		accum1 += m1_mag;
		while(accum1 > 1)
		{
			accum1 -= 1;
			x += dir1;
		}
		
		accum2 += m2_mag;
		while(accum2 > 1)
		{
			accum2 -= 1;
			xf += dir2;
		}
		
		y++;
	}
}

void Canvas::drawPoint(Point p, Color color)
{
	drawPoint(p.x, p.y, color);
}
void Canvas::drawLine(Point p0, Point p1, Color color)
{
	drawLine(p0.x, p0.y, p1.x, p1.y, color);
}
void Canvas::drawRect(Point p, int width, int height, Color color)
{
	drawRect(p.x, p.y, width, height, color);
}
void Canvas::fillRect(Point p, int width, int height, Color color)
{
	fillRect(p.x, p.y, width, height, color);
}
void Canvas::drawCircle(Point c, int radius, Color color)
{
	drawCircle(c.x, c.y, radius, color);
}
void Canvas::fillCircle(Point c, int radius, Color color)
{
	fillCircle(c.x, c.y, radius, color);
}
void Canvas::drawTriangle(Point p0, Point p1, Point p2, Color color)
{
	drawTriangle(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, color);
}
void Canvas::fillTriangle(Point p0, Point p1, Point p2, Color (*colorFunc)(int, int))
{
	fillTriangle(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, colorFunc);
}
void Canvas::fillTriangle(Point p0, Point p1, Point p2, Color color)
{
	fillTriangle(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, color);
}

Color Canvas::defaultColorFunc(int x, int y)
{
	return default_color;
}

void Canvas::swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void Canvas::swap(float &a, float &b)
{
	float temp = a;
	a = b;
	b = temp;
}

int Canvas::signOf(float a)
{
	if(a >= 0)
		return 1;
	return -1;
}

Color Canvas::default_color = Color(0x0);
