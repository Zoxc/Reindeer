#pragma once
#include <stdint.h>

namespace Reindeer
{
	typedef uint32_t color_t;
	typedef uint8_t alpha_t;

	const color_t color_black = 0x000000FF;
	const color_t color_white = 0xFFFFFFFF;
	
	const alpha_t alpha_transparent = 0x00;
	const alpha_t alpha_opaque = 0xFF;
};
