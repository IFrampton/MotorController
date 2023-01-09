#include "SlowTimer.h"

SlowTimer::SlowTimerData SlowTimer::_slowTimers[8];
unsigned char SlowTimer::_nextTimer = 0;
bool SlowTimer::_initialized = false;

void SlowTimer::Initialize()
{
	for(unsigned char x = 0; x < sizeof(_slowTimers)/sizeof(SlowTimerData); x++ )
	{
		_slowTimers[x].Period = 0;
		_slowTimers[x].Elapsed = 0;
		_slowTimers[x].Callback = DummyFunction;
	}
	_initialized = true;
}

void SlowTimer::PeriodicUpdate(unsigned long timePeriod)
{
	if(!_initialized)
		return;

	for(unsigned char x = 0; x < sizeof(_slowTimers)/sizeof(SlowTimerData); x++ )
	{
		// This was a previous version that passed processor clocks in for slow timer period
		//_timers[x].Elapsed += timePeriod;
		_slowTimers[x].Elapsed++;
		if(_slowTimers[x].Elapsed >= _slowTimers[x].Period)
		{
			_slowTimers[x].Elapsed = 0;
			if(_slowTimers[x].Period)
			{
				(*_slowTimers[x].Callback)();
			}
		}
	}
}

unsigned char SlowTimer::SetupTimer(unsigned long period, void (*callback)())
{
	if(_nextTimer < sizeof(_slowTimers)/sizeof(SlowTimerData))
	{
		_slowTimers[_nextTimer].Period = period;
		_slowTimers[_nextTimer].Callback = callback;
		unsigned char tmr = _nextTimer;
		_nextTimer++;
		return tmr;
	}
	else
	{
		return 0xFF;
	}
}

void SlowTimer::DummyFunction(void)
{
	//__asm("NOP");
}
