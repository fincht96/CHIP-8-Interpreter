#include "../include/graphics.h"



Graphics::Graphics(Memory* mem, sf::RenderWindow* window)
	:	m_pMem(mem), m_pWindow(window)
{

	m_pixel_array.setPrimitiveType(sf::Quads);
	m_pixel_array.resize(8192);



	for (unsigned y = 0; y < screen_height; y++)
	{
		for (unsigned x = 0; x < screen_width; x++)
		{
			sf::Vertex* quad = &m_pixel_array[(x + y * screen_width) * 4];

			// updates the location for each pixel vertice
			// starts from bottom left vertice and goes clockwise
			quad[0].position = sf::Vector2f(x*10, (y+10)*10);
			quad[1].position = sf::Vector2f(x*10, y*10);
			quad[2].position = sf::Vector2f((x+10)*10, y*10);
			quad[3].position = sf::Vector2f((x+10)*10, (y+10)*10);



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

	if (px_coor.m_x > (screen_width-1))
		px_coor.m_x -= screen_width;

	else if (px_coor.m_x < 0)
		px_coor.m_x += screen_width;

	if (px_coor.m_y > (screen_height-1))
		px_coor.m_y -= screen_height;

	else if (px_coor.m_y < 0)
		px_coor.m_y += screen_height;


	uint16_t px_num = px_coor.m_x + px_coor.m_y * screen_width;

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

	//m_pWindow->draw(m_pixel_array);
}


uint8_t Graphics::getPixel(Vec2 px_coor)
{
	if (px_coor.m_x > (screen_width-1))
		px_coor.m_x -= screen_width;

	else if (px_coor.m_x < 0)
		px_coor.m_x += screen_width;

	if (px_coor.m_y > (screen_height-1))
		px_coor.m_y -= screen_height;

	else if (px_coor.m_y < 0)
		px_coor.m_y += screen_height;


	uint8_t val = 0;

	uint16_t px_num = px_coor.m_x + px_coor.m_y * screen_width;

	sf::Vertex* quad = &m_pixel_array[(px_num) * 4];

	if(quad[0].color == sf::Color::Green)
		val = 1;

	return val;
}


void Graphics::clearDisplay()
{
	for (unsigned y = 0; y < screen_height; y++)
	{
		for (unsigned x = 0; x < screen_width; x++)
		{
			sf::Vertex* quad = &m_pixel_array[(x + y * screen_width) * 4];

			quad[0].color = sf::Color::Black;
			quad[1].color = sf::Color::Black;
			quad[2].color = sf::Color::Black;
			quad[3].color = sf::Color::Black;
		}
	}
}
