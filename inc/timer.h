#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include "SFML/System.hpp"

class Timer
{
public:
	Timer();
	~Timer();
	void setTimer(uint8_t tim_value);
	uint8_t getTimer();

private:
	uint8_t m_set_tim_value;	// holds time value set, 0 - 255 (0 - 255*16.6 ms)
	uint8_t m_current_tim_value;	// holds the current time value, 0 - 255 (0 - 255*16.6 ms)
	float elapsedTime;				// holds the total time elapsed since timer set

	sf::Clock m_clk;
};


#endif
