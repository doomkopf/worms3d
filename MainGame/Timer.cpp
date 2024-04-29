#include "Timer.h"

void Timer::Init()
{
	if(!QueryPerformanceFrequency((LARGE_INTEGER *)&frequency))
	{
		performance_timer=false;
		mm_timer_start=timeGetTime();
		resolution=0.001f;
		frequency=1000;
		mm_timer_elapsed=mm_timer_start;
	}
	else
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&performance_timer_start);
		performance_timer=true;
		resolution=(float)(((double)1.0f)/((double)frequency));
		performance_timer_elapsed=performance_timer_start;
	}
}

float Timer::GetTime()
{
	__int64 time;

	if(performance_timer)
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&time);
		return ((float)(time-performance_timer_start)*resolution)*1000.0f;
	}

	return ((float)(timeGetTime()-mm_timer_start)*resolution)*1000.0f;
}