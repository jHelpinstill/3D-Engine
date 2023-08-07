#ifndef COLOR_
#define COLOR_

class Color
{
public:
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

	static Color average(Color* colors, int num_colors);
	
	int val;
	
	int getAlpha();
	int getR();
	int getG();
	int getB();
	
	void setAlpha(int a);
	void setR(int r);
	void setG(int g);
	void setB(int b);
	bool hasAlpha();
	
	static Color R;
	static Color G;
	static Color B;
	static Color BLACK;
	static Color WHITE;
	static Color ALPHA;
};

#endif
