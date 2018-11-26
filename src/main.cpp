

#include <iostream>
#include "chip8.h"
#include "memory.h"
#include "graphics.h"
#include "timer.h"
#include "input.h"


#include "SFML/Graphics.hpp"


int main()
{
	Memory mem(PROG_MEM_OFFSET);

	sf::RenderWindow window(sf::VideoMode(640, 320), "Chip8");
	window.setKeyRepeatEnabled(false);


	Timer delayTimer, soundTimer;
	Graphics gpu(&mem, &window);
	Chip8 cpu(&mem, &gpu, &delayTimer, &soundTimer);

	sf::Event event;
	bool stepFlag = false;
	bool runFlag = true;

	while (window.isOpen())
	{
		stepFlag = false;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space)			// pause/resume execution
				{
					if (runFlag)
						runFlag = false;
					else
						runFlag = true;
				}

				else if (event.key.code == sf::Keyboard::Up) 	// step execution
				{
					runFlag = false;
					stepFlag = true;
				}
				break;
			}

		}

		if (runFlag || stepFlag)
		{
			cpu.update();
			window.clear();
			gpu.updateAndRender();
			window.display();
		}

	}

	return 0;
}




