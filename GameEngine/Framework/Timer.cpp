//----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------
// Timer v.2.1.0
//		 v.2.5
//---------------------------------------------------------------------------- 

#include <assert.h>

// locals
#include "Timer.h"

Timer::Timer()
{
	this->privInitTimer();
	this->Reset();
}

void Timer::privInitTimer() 
{
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	this->SecondsPerCycle = 1.0f / Frequency.QuadPart;
}

LARGE_INTEGER Timer::privGetTimer()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return time;
}

void Timer::Tic()
{
	this->ticTime = this->privGetTimer();
}

void Timer::Toc()
{
	this->tocTime = this->privGetTimer();
	assert( this->tocTime.QuadPart >= this->ticTime.QuadPart );
	this->deltaTime.QuadPart = this->tocTime.QuadPart - this->ticTime.QuadPart;
}

void Timer::Reset()
{
	this->ticTime.QuadPart = 0;
	this->tocTime.QuadPart = 0;
	this->deltaTime.QuadPart = 0;
}

float Timer::TimeInSeconds()
{
	float floatTime;
	floatTime = static_cast<float>(this->deltaTime.QuadPart);
	floatTime *= this->SecondsPerCycle;
	return floatTime;
}

// ---  End of File ---------------
