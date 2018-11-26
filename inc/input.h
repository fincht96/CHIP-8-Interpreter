
//$Header$
//---------------------------------------------------------------------------------------------------------
//												Input
//---------------------------------------------------------------------------------------------------------
//	Chip8 Interpreter
//
// Author: Thomas Finch
// Created: 22/11/2018
//
/**
*	Provides the user input capabilities of the system.
*
*	@note: n/a
*
*/
//---------------------------------------------------------------------------------------------------------


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
