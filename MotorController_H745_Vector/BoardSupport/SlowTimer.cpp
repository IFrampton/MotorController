/*
 * BspTimer.cpp
 *
 *  Created on: Jan 4, 2024
 *      Author: Isaac Frampton
 */

#include "SlowTimer.h"

SlowTimer::TimerData SlowTimer::_timerData[8];
unsigned char SlowTimer::_nextTimer = 0;

void SlowTimer::Initialize(void)
{
	// The Slow Timer doesn't really do anything with the hardware.
	// This is a good place to makes sure that all the data structures are defaulted to safe values.
	for(char idx = 0; idx < (sizeof(_timerData) / sizeof(TimerData)); idx++)
	{
		_timerData[(long)idx].Function = DummyFunction;
		_timerData[(long)idx].Period = 0xFFFFFFFF - idx;
		_timerData[(long)idx].Count = 0;
	}
}

char SlowTimer::Setup(long clockCycles, void (*funct)(void))
{
	if(_nextTimer >= (sizeof(_timerData) / sizeof(TimerData)))
	{
		return -1;
	}
	_timerData[(long)_nextTimer].Function = funct;
	_timerData[(long)_nextTimer].Period = clockCycles;
	_timerData[(long)_nextTimer].Count = 0;
	char nxtTmr = _nextTimer;
	_nextTimer++;
	return nxtTmr;
}

void SlowTimer::Update()
{
	TimerData *data = _timerData;
	for(char idx = (sizeof(_timerData) / sizeof(TimerData)); idx ; idx--)
	{
		if(++data->Count >= data->Period)
		{
			data->Count = 0;
			data->Function();
		}
		data++;
	}
}

void SlowTimer::DummyFunction(void)
{
}
