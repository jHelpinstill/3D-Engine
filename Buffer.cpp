#include "Buffer.h"

Buffer::Buffer(int width, int height)
{
	setSize(width, height);
}
Buffer::Buffer(const Buffer& other)
{
	*this = other;
}

Buffer& Buffer::operator=(const Buffer& other)
{
	if (this == &other)
		return *this;

	this->width = other.width;
	this->height = other.height;

	int num_pixels = width * height;
	delete[] pixels;
	pixels = new Color[num_pixels];
	for (int i = 0; i < num_pixels; i++)
		pixels[i] = other.pixels[i];

	return *this;
}

void Buffer::setSize(int width, int height)
{
	Color* prev_pixels = pixels;
	int prev_width = this->width;
	int prev_height = this->height;

	this->width = width;
	this->height = height;
	int num_pixels = width * height;
	pixels = new Color[num_pixels];

	int fill_width = (prev_width > width) ? width : prev_width;
	int fill_height = (prev_height > height) ? height : prev_height;

	for (int j = 0; j < fill_height; j++)
	{
		int row_offset = j * fill_width;
		for (int i = 0; i < fill_width; i++)
			pixels[row_offset + i] = prev_pixels[row_offset + i];
	}
	int next_pixel = fill_height * fill_width;
	for (int i = next_pixel; i < num_pixels; i++)
		pixels[i] = Color::ALPHA;

	delete[] prev_pixels;
}
int Buffer::getWidth() const
{
	return width;
}
int Buffer::getHeight() const
{
	return height;
}
Frame* Buffer::getFrame()
{
	return &frame;
}
Color* Buffer::getPixels()
{
	return pixels;
}
Buffer::~Buffer()
{
	delete[] pixels;
}