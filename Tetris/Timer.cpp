#include "Timer.h"



Timer::Timer()
{
}


Timer::~Timer()
{

}

void Timer::MainThread(int intervalTime, bool& timerflag)
{
	while (1) {
	}
}

void Timer::IntervalTimer(int intervalTime, bool& timerFlag)
{
	std::thread th(&Timer::MainThread, this, intervalTime, std::ref(timerFlag));
	th.detach();
}

