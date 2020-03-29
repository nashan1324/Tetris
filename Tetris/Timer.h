#pragma once
#include <thread>
#include <chrono>

class Timer
{
public:
	Timer();
	~Timer();
	void IntervalTimer(int intervalTime, bool& timerFlag);

private:
	void MainThread(int intervalTime, bool& timerFlag);
};

