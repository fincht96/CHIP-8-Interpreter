#ifndef CONSTANTS_H
#define CONSTANTS_H


//$Header$
// 
//	Chip8 Interpreter
//
// Author: Thomas Finch
// Created: 22/11/2018
//
/**
*	Contains the various constants for all the classes.
*
*	@note: n/a
*
*/
//---------------------------------------------------------------------------------------------------------


#include <stdint.h>


// CHIP8 CONSTANTS

const uint8_t NUM_REGS = 16;
const uint8_t MEM_OFFSET = 5;



// MEMORY MAPPING

const uint16_t PROG_MEM_OFFSET = 0x200;

const uint16_t SPRT_STRT_ADDR = 0x0000;
const uint16_t SPRT_MEM_SIZE = 512;

const uint16_t RAM_STRT_ADDR = 0x0200;
const uint16_t RAM_MEM_SIZE = 3584;

const uint16_t GRAPH_STRT_ADDR = 0x1000;
const uint16_t GRAPH_MEM_SIZE = 256;


const uint16_t MEMORY_SIZE = 4096;

// GRAPHICS CONSTANTS

const uint8_t SCREEN_WIDTH = 64;
const uint8_t SCREEN_HEIGHT = 32;


const uint8_t SPRITE_WIDTH = 8;



class Vec2
{
public:
	Vec2(uint8_t x, uint8_t y) : m_x(x), m_y(y) {};
	uint8_t m_x;
	uint8_t m_y;
};

#endif
