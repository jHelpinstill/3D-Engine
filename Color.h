#ifndef COLOR_
#define COLOR_

#include <string>
#include <string.h>
#include <stdio.h>
#include <sstream>


class Color
{
private:
	static void expandNextColor(Color* img_buffer, int& buffer_index, std::string f, Color c);

public:
	int val;


	Color(){}
	Color(int color);
	
	void operator=(int color);
	Color operator+(Color color);
	Color operator-(Color color);
	void operator+=(Color color);
	void operator-=(Color color);
	Color operator*(float a);
	Color operator/(float a);
	void operator*=(float a);
	void operator/=(float a);
	
	Color operator*(Color color);
	static int occludeFast(int color1, int color2);
	Color occlude(Color color);

	static Color average(Color* colors, int num_colors, float* weights = nullptr);
	static Color* createTexture(int width, int height, std::string format);
	
	int getAlpha();
	int getR();
	int getG();
	int getB();
	
	void setAlpha(int a);
	void setR(int r);
	void setG(int g);
	void setB(int b);
	bool hasAlpha();
	
	static Color R; static Color RED;
	static Color G; static Color GREEN;
	static Color B; static Color BLUE;
	static Color Y; static Color YELLOW;
	static Color BLACK;
	static Color WHITE;
	static Color ALPHA;
};

#endif
