#include "timer.h"



Timer::Timer()
{
	m_current_tim_value = 0;
	m_set_tim_value = 0;
	elapsedTime = 0.0f;
}


Timer::~Timer()
{
}


void Timer::setTimer(uint8_t tim_value)
{
	m_set_tim_value = tim_value;
	m_current_tim_value = tim_value;
	elapsedTime = 0.0f;
	m_clk.restart();
}


uint8_t Timer::getTimer()
{
	elapsedTime = m_clk.getElapsedTime().asSeconds(); 		// elapsed time in seconds since clock restarted

	if (elapsedTime > (m_set_tim_value*0.016))						// time elapsed > time set, current timer value is 0
		m_current_tim_value = 0;

	else
		m_current_tim_value = (uint8_t)(m_set_tim_value - (elapsedTime / 0.016));		// updates current timer value


	return m_current_tim_value;
}
