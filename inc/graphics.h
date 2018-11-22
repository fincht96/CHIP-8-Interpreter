

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SFML/Graphics.hpp"
#include "memory.h"




class Graphics
{
private:
	Memory* m_pMem;
	sf::VertexArray m_pixel_array;			// holds pixel array used to represent graphics
	sf::RenderWindow* m_pWindow;			// holds a pointer to the render window
	float cumulative_time = 0;


public:
	Graphics(Memory* mem, sf::RenderWindow* window);
	~Graphics();

	void updateAndRender();		// refreshes graphics displayed on screen

	void setPixel(uint8_t val, Vec2 px_coor);
	uint8_t getPixel(Vec2 px_coor);
	void clearDisplay();
};



#endif
