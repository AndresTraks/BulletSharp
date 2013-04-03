#include "StdAfx.h"

#ifndef BT_NO_PROFILE

#include "QuickProf.h"

#ifdef USE_BT_CLOCK

Clock::Clock()
{
	_native = new btClock();
}

Clock::Clock(Clock^ other)
{
	_native = new btClock(*other->_native);
}

void Clock::Reset()
{
	_native->reset();
}

long Clock::TimeMicroseconds::get()
{
	return _native->getTimeMicroseconds();
}

long Clock::TimeMilliseconds::get()
{
	return _native->getTimeMilliseconds();
}

#endif

#endif
