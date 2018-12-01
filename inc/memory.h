
//$Header$
//---------------------------------------------------------------------------------------------------------
//												Memory
//---------------------------------------------------------------------------------------------------------
//	Chip8 Interpreter
//
// Author: Thomas Finch
// Created: 22/11/2018
//
/**
*	Manages all memory interactions within the system as well reading from external files.
*
*	@note: 
*
*/
//---------------------------------------------------------------------------------------------------------


#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <array>
#include <fstream>
#include <cstring>
#include "constants.h"
#include <iostream>

// Memory Map
// ------------------------------------------------------------------
// (0x0000 - 0x01FF)	holds char sprites			(512 bytes)
// (0x0200 - 0x0FFF)	holds program work memory		(3584 bytes)
//							TOTAL:	(4096 bytes)


class Memory
{

private:
	char m_mem[MEMORY_SIZE] = { 0 };

public:
	Memory(const uint16_t offset);		// constructor reads ROM file into mem starting from a given offset		
	~Memory();

	char& operator[](const uint16_t addr);

};

#endif
