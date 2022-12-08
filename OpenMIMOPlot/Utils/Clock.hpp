#if !defined(CLOCK_HPP)
#define CLOCK_HPP

#include <chrono>

using std::chrono::steady_clock;
using std::chrono::duration_cast;

class Clock
{
public:
	void Start();
	double GetEllapsedTime();
	void Wait(size_t waitTimeInMicroseconds);
private:
	steady_clock::time_point m_Start;
};

#endif // CLOCK_HPP
