#pragma once
#ifndef BUFFER_
#define BUFFER_
#include "Color.h"
#include "Frame.h"

class Buffer
{
private:
	union
	{
		struct { int width, height; Color* pixels; float dt; };
		Frame frame = Frame();
	};

public:
	Buffer() {}
	Buffer(int width, int height);
	Buffer(const Buffer& other);

	Buffer& operator=(const Buffer& other);

	void setSize(int width, int height);

	int getWidth() const;
	int getHeight() const;
	Frame* getFrame();
	Color* getPixels();

	~Buffer();
};

#endif