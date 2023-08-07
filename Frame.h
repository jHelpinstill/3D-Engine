#ifndef FRAME_
#define FRAME_

#include <cstdint>

struct Frame
{
	int width;
	int height;
	uint32_t *pixels;
	
	float dt;
};

#endif
