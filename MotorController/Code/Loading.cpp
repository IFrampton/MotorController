#include "Loading.h"

Loading::LoadingData *Loading::_data;
bool Loading::_initialized = false;
//unsigned long Loading::_temp1 = 0;

void Loading::Initialize()
{
	while(1)
	{
		if(_initialized)
		{
			break;
		}
	}
}

void Loading::UpdateEvery1Sec(unsigned long timePeriod)
{
	long totalCalls = 0;
	long totalCyclesUsed = 0;
	float cyclesPerPeriodFactor = 100.0f / (float)timePeriod;
	for(unsigned char index = 1; index < NUMBER_OF_ELEMENTS; index++)
	{
		totalCalls += _data[index].CallCounter;
		_data[index].TimesCalled = _data[index].CallCounter;
		_data[index].CallCounter = 0;
		totalCyclesUsed += _data[index].CyclesUsed;
		_data[index].Loading = (float)_data[index].CyclesUsed * cyclesPerPeriodFactor;
		_data[index].CyclesUsed = 0;
	}
	_data[0].TimesCalled = totalCalls;
	_data[0].Loading = (float)totalCyclesUsed * cyclesPerPeriodFactor;
}
