#ifndef TIMER
#define TIMER

#include <windows.h>
#pragma comment (lib,"winmm.lib")

class Timer
{
public:
	void Init();
	float GetTime();

protected:
	__int64 frequency;
	float resolution;
	unsigned long mm_timer_start;
	unsigned long mm_timer_elapsed;
	bool performance_timer;
	__int64 performance_timer_start;
	__int64 performance_timer_elapsed;
};

#endif