#include "memory.h"
#include "input.h"

Memory::Memory(const uint16_t offset)
{
	std::streampos size;
	std::ifstream file;

	while (!file.is_open())
	{
		std::cout << "\nPlease enter a valid filename (begin with ../ for relative paths):\n";
		file.open(Input::getCharStream(), std::ios::in | std::ios::binary | std::ios::ate);		// opens input file stream, input, points to end of file and in binary mode
	}
	
	size = file.tellg();
	file.seekg(0, std::ios::beg);
	file.read(m_mem, size);
	file.close();
	


	memmove(&m_mem[512], &m_mem[0], size);
}



Memory::~Memory()
{
}



char& Memory::operator[](const uint16_t addr)
{
	return m_mem[addr];
}
