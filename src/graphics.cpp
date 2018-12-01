#include "../inc/graphics.h"



Graphics::Graphics(Memory* mem, sf::RenderWindow* window)
	: m_pMem(mem), m_pWindow(window)
{

	m_pixel_array.setPrimitiveType(sf::Quads);
	m_pixel_array.resize(8192);



	for (unsigned y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (unsigned x = 0; x < SCREEN_WIDTH; x++)
		{
			sf::Vertex* quad = &m_pixel_array[(x + y * SCREEN_WIDTH) * 4];

			// updates the location for each pixel vertice
			// starts from bottom left vertice and goes clockwise
			quad[0].position = sf::Vector2f((float)(x * 10), (float)((y + 10) * 10));
			quad[1].position = sf::Vector2f((float)(x * 10), (float)(y * 10));
			quad[2].position = sf::Vector2f((float)((x + 10) * 10), (float)(y * 10));
			quad[3].position = sf::Vector2f((float)((x + 10) * 10), (float)((y + 10) * 10));

			

			quad[0].color = sf::Color::Black;
			quad[1].color = sf::Color::Black;
			quad[2].color = sf::Color::Black;
			quad[3].color = sf::Color::Black;
		}
	}


	m_pWindow->draw(m_pixel_array);
}


Graphics::~Graphics()
{
}





void Graphics::updateAndRender()
{
	m_pWindow->draw(m_pixel_array);
}


void Graphics::setPixel(uint8_t val, Vec2 px_coor)
{

	if (px_coor.m_x > (SCREEN_WIDTH - 1))
		px_coor.m_x -= SCREEN_WIDTH;

	else if (px_coor.m_x < 0)
		px_coor.m_x += SCREEN_WIDTH;

	if (px_coor.m_y >(SCREEN_HEIGHT - 1))
		px_coor.m_y -= SCREEN_HEIGHT;

	else if (px_coor.m_y < 0)
		px_coor.m_y += SCREEN_HEIGHT;


	uint16_t px_num = px_coor.m_x + px_coor.m_y * SCREEN_WIDTH;

	sf::Vertex* quad = &m_pixel_array[(px_num) * 4];

	if (val > 0)
	{
		quad[0].color = sf::Color::Green;
		quad[1].color = sf::Color::Green;
		quad[2].color = sf::Color::Green;
		quad[3].color = sf::Color::Green;
	}

	else
	{
		quad[0].color = sf::Color::Black;
		quad[1].color = sf::Color::Black;
		quad[2].color = sf::Color::Black;
		quad[3].color = sf::Color::Black;
	}

}


uint8_t Graphics::getPixel(Vec2 px_coor)
{
	if (px_coor.m_x > (SCREEN_WIDTH - 1))
		px_coor.m_x -= SCREEN_WIDTH;

	else if (px_coor.m_x < 0)
		px_coor.m_x += SCREEN_WIDTH;

	if (px_coor.m_y >(SCREEN_HEIGHT - 1))
		px_coor.m_y -= SCREEN_HEIGHT;

	else if (px_coor.m_y < 0)
		px_coor.m_y += SCREEN_HEIGHT;


	uint8_t val = 0;

	uint16_t px_num = px_coor.m_x + px_coor.m_y * SCREEN_WIDTH;

	sf::Vertex* quad = &m_pixel_array[(px_num) * 4];

	if (quad[0].color == sf::Color::Green)
		val = 1;

	return val;
}


void Graphics::clearDisplay()
{
	for (unsigned y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (unsigned x = 0; x < SCREEN_WIDTH; x++)
		{
			sf::Vertex* quad = &m_pixel_array[(x + y * SCREEN_WIDTH) * 4];

			quad[0].color = sf::Color::Black;
			quad[1].color = sf::Color::Black;
			quad[2].color = sf::Color::Black;
			quad[3].color = sf::Color::Black;
		}
	}
}
