#include "input.h"



Input::Input()
{
}


Input::~Input()
{
}

uint8_t Input::getKeyPress()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
	{
		return (uint8_t)0;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		return (uint8_t)1;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		return (uint8_t)2;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		return (uint8_t)3;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		return (uint8_t)4;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		return (uint8_t)5;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		return (uint8_t)6;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
		return (uint8_t)7;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		return (uint8_t)8;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	{
		return (uint8_t)9;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		return (uint8_t)10;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		return (uint8_t)11;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		return (uint8_t)12;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		return (uint8_t)13;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		return (uint8_t)14;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		return (uint8_t)15;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		return (uint8_t)16;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		return (uint8_t)17;
	}

	else
	{
		return (uint8_t)255;		// default case
	}
}


std::string Input::getCharStream()
{
	std::string char_stream;
	std::cin >> char_stream;
	return char_stream;
}
