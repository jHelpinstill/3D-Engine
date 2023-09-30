#ifndef FRAME_
#define FRAME_

#include <cstdint>

struct Frame
{
	int width = 0;
	int height = 0;
	uint32_t *pixels = nullptr;
	
	float dt = 0;
};

#endif
