
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
// (0x0000 - 0x01FF)	holds char sprites				(512 bytes)
// (0x0200 - 0x0FFF)	holds program mem and Work RAM	(3584 bytes)
// (0x1000 - 0x10FF)	holds graphics memory			(256 bytes)
//												TOTAL:	(4352 bytes)

// *Note: Each bit of graphics memory represents a pixel on screen





class Memory
{

private:
	char m_mem[MEMORY_SIZE] = { 0 };

public:
	Memory();
	Memory(const std::string filename, uint16_t offset);			// constructor reads ROM file into mem starting from a given offset
	~Memory();

	char& operator[](const uint16_t addr);

};

#endif
