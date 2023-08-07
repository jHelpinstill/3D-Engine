#include "Color.h"

Color::Color(int color)
{
	val = color;
}
void Color::operator=(int color)
{
	val = color;
}
Color Color::operator+(Color color)
{
	Color color_out;
	color_out.setAlpha(this->getAlpha() + color.getAlpha());
	color_out.setR(this->getR() + color.getR());
	color_out.setG(this->getG() + color.getG());
	color_out.setB(this->getB() + color.getB());
	return color_out;
}
Color Color::operator-(Color color)
{
	Color color_out;
	color_out.setAlpha(this->getAlpha() - color.getAlpha());
	color_out.setR(this->getR() - color.getR());
	color_out.setG(this->getG() - color.getG());
	color_out.setB(this->getB() - color.getB());
	return color_out;
}
void Color::operator+=(Color color)
{
	this->setAlpha(this->getAlpha() + color.getAlpha());
	this->setR(this->getR() + color.getR());
	this->setG(this->getG() + color.getG());
	this->setB(this->getB() + color.getB());
}
void Color::operator-=(Color color)
{
	this->setAlpha(this->getAlpha() - color.getAlpha());
	this->setR(this->getR() - color.getR());
	this->setG(this->getG() - color.getG());
	this->setB(this->getB() - color.getB());
}
Color Color::operator*(float a)
{
	Color color_out;
	color_out.setR(this->getR() * a);
	color_out.setG(this->getG() * a);
	color_out.setB(this->getB() * a);
	return color_out;
}
Color Color::operator/(float a)
{
	Color color_out;
	color_out.setR(this->getR() / a);
	color_out.setG(this->getG() / a);
	color_out.setB(this->getB() / a);
	return color_out;
}
void Color::operator*=(float a)
{
	this->setR(this->getR() * a);
	this->setG(this->getG() * a);
	this->setB(this->getB() * a);
}
void Color::operator/=(float a)
{
	this->setR(this->getR() / a);
	this->setG(this->getG() / a);
	this->setB(this->getB() / a);
}
Color Color::operator*(Color color)
{
	Color out;
	out.setAlpha((getAlpha() * color.getAlpha()) / 255);
	out.setR((getR() * color.getR()) / 255);
	out.setG((getG() * color.getG()) / 255);
	out.setB((getB() * color.getB()) / 255);
	return color;
}

int Color::occludeFast(int color1, int color2)
{
//	return this->val;
	
	int transmittance = (color1 & 0xff000000) >> 24;
	if(transmittance == 0) return color1;
	if(transmittance == 255) return color2;
	
//	float transmittancef = transmittance / 255.0;
	int rgbs[2][3];
	rgbs[0][0] = color1 & 0xff0000;
	rgbs[0][1] = color1 & 0xff00;
	rgbs[0][2] = color1 & 0xff;
	
	rgbs[1][0] = color2 & 0xff0000;
	rgbs[1][1] = color2 & 0xff00;
	rgbs[1][2] = color2 & 0xff;
	
	int r, g, b;
	r = (transmittance * (rgbs[1][0] - rgbs[0][0])) / 255 + rgbs[0][0];
	g = (transmittance * (rgbs[1][1] - rgbs[0][1])) / 255 + rgbs[0][1];
	b = (transmittance * (rgbs[1][2] - rgbs[0][2])) / 255 + rgbs[0][2];
	
	return (r & 0xff0000) | (g & 0xff00) | b;
//	return ((Color(color2) * transmittancef) + (Color(color1) * (1 - transmittancef))).val;
}
Color Color::occlude(Color color)
{
	float transmittance = getAlpha();
	if(transmittance == 0) return *this;
	if(transmittance == 255) return color;
	
	
	return (color * transmittance) + (*this * (1 - transmittance));
}

void Color::setAlpha(int a)
{
	if(a < 0)
		val &= 0x00ffffff;
	else if(a > 255)
		val |= 0xff000000;
	else
	{
		val &= 0x00ffffff;
		val |= a << 24;
	}
}
void Color::setR(int r)
{
	if(r < 0)
		val &= 0xff00ffff;
	else if(r > 255)
		val |= 0x00ff0000;
	else
	{
		val &= 0xff00ffff;
		val |= r << 16;
	}
}

void Color::setG(int g)
{
	if(g < 0)
		val &= 0xffff00ff;
	else if(g > 255)
		val |= 0x0000ff00;
	else
	{
		val &= 0xffff00ff;
		val |= g << 8;
	}
}

void Color::setB(int b)
{
	if(b < 0)
		val &= 0xffffff00;
	else if(b > 255)
		val |= 0x000000ff;
	else
	{
		val &= 0xffffff00;
		val |= b;
	}
}


int Color::getAlpha()
{
	return (val & 0xff000000) >> 24;
}
int Color::getR()
{
	return (val & 0x00ff0000) >> 16;
}
int Color::getG()
{
	return (val & 0x0000ff00) >> 8;
}
int Color::getB()
{
	return (val & 0x000000ff);
}

Color Color::R = Color(0x00ff0000);
Color Color::G = Color(0x0000ff00);
Color Color::B = Color(0x000000ff);
Color Color::BLACK = Color(0x00000000);
Color Color::WHITE = Color(0x00ffffff);
