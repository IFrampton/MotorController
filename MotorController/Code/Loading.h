#include "BspTimer.h"

#ifndef LOADING_H
#define LOADING_H

#if defined (__cplusplus)
class Loading
{
	/* Enumerated Type Definition */
	public: enum Tasks
	{
		TOTALS,
		ANALOG,
		MOTOR_CONTROLLER_INPUTS,
		MOTOR_CONTROLLER_MODEL,
		MOTOR_CONTROLLER_OUTPUTS,
		PROTECTION,
		CAN,
		NUMBER_OF_ELEMENTS
	};
	/* Structure Definition */
	public: struct LoadingData
	{
		long CallCounter;
		long TimesCalled;
		long StartTime;
		long CyclesUsed;
		//long MinCycles;
		//long MaxCycles;
		float Loading;
	};
	/* Variable Declarations */
	private: static LoadingData *_data;
	private: static bool _initialized;
	//private: static unsigned long _temp2;
	/* Function Declarations */
	public:  static void Initialize(void);
	public:  static void UpdateEvery1Sec(unsigned long timePeriod);
	public:  static void LinkMemorySpace(LoadingData *data) {_data = data; _initialized = true;}
	public:  static void inline StartMeasuredSection(unsigned char index)
	{
		_data[index].StartTime = BspTimer::GetFreeRunningCounter();
		_data[index].CallCounter++;
	}
	public:  static void inline StopMeasuredSection(unsigned char index)
	{
		long timing = (_data[index].StartTime - BspTimer::GetFreeRunningCounter());
		if(timing < 0)
			timing += 0x1000000;
		_data[index].CyclesUsed += timing;
	}
};
#endif

#endif //LOADING_H
