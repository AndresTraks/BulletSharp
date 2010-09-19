#include "StdAfx.h"

#ifndef BT_NO_PROFILE

#include "QuickProf.h"

#ifdef USE_BT_CLOCK

Clock::Clock()
{
	_clock = new btClock();
}

Clock::Clock(Clock^ other)
{
	_clock = new btClock(*other->UnmanagedPointer);
}

void Clock::Reset()
{
	_clock->reset();
}

long Clock::TimeMicroseconds::get()
{
	return _clock->getTimeMicroseconds();
}

long Clock::TimeMilliseconds::get()
{
	return _clock->getTimeMilliseconds();
}

btClock* Clock::UnmanagedPointer::get()
{
	return _clock;
}

#endif

#endif
