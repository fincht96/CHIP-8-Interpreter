#include "../include/memory.h"


Memory::Memory()
{

}


//Memory::Memory(const char* filename, uint16_t offset)
Memory::Memory(const std::string filename, uint16_t offset)
{
	std::streampos size;
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);		// opens input file stream, input, points to end of file and in binary mode

	if (file.is_open())
	{
		size = file.tellg();
		file.seekg(0, std::ios::beg);
		file.read(m_mem, size);
		file.close();
	}

	else
	{
		std::cout << "UNABLE TO OPEN FILE";
	}

	 memmove (&m_mem[512], &m_mem[0], size);
}


Memory::~Memory()
{
}





char& Memory::operator[](const uint16_t addr)
{
		//if (addr >= MEMORY_SIZE)
		//{
		//	std::cout << "INVALID MEMORY ACCESS: "<< (uint16_t)addr << " , OUT OF MEMORY RANGE.\n";
		//	std::cin.get();
			//return;
		//}
		return m_mem[addr];
}
