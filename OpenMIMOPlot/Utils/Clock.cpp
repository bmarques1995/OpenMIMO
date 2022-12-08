#include "Clock.hpp"

void Clock::Start()
{
	m_Start = steady_clock::now();
}

double Clock::GetEllapsedTime()
{
	steady_clock::time_point end = steady_clock::now();
	size_t timeEllapsed = duration_cast<std::chrono::microseconds>(end - m_Start).count();
	return timeEllapsed*1.0/1.0e6;
}

void Clock::Wait(size_t waitTimeInMicroseconds)
{
	steady_clock::time_point end = steady_clock::now();
	size_t timeEllapsed = duration_cast<std::chrono::microseconds>(end-m_Start).count();
	while (timeEllapsed < waitTimeInMicroseconds)
	{
		end = steady_clock::now();
		timeEllapsed = duration_cast<std::chrono::microseconds>(end - m_Start).count();
	}
}
