#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

	// CHIP8 CONSTANTS

	const uint8_t NUM_REGS = 16;
	const uint8_t MEM_OFFSET = 5;



	// MEMORY MAPPING

	const uint16_t SPRT_STRT_ADDR = 0x0000;
	const uint16_t SPRT_MEM_SIZE = 512;

	const uint16_t RAM_STRT_ADDR = 0x0200;
	const uint16_t RAM_MEM_SIZE = 3584;

	const uint16_t GRAPH_STRT_ADDR = 0x1000;
	const uint16_t GRAPH_MEM_SIZE = 256;


	const uint16_t MEMORY_SIZE = 4352;

	// GRAPHICS CONSTANTS

	const uint8_t screen_width = 64;
	const uint8_t screen_height = 32;


	const uint8_t sprite_width = 8;



	class Vec2
	{
	public:
		Vec2(uint16_t x, uint16_t y) : m_x(x), m_y(y) {};
		uint8_t m_x;
		uint8_t m_y;
	};

#endif
