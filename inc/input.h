#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <iostream>
#include "SFML/Window.hpp"

class Input
{
public:
	static uint8_t getKeyPress();
	static std::string getCharStream();

private:
	Input();
	~Input();

};

#endif
