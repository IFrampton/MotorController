// Loading.h
// Header file for simplified Loading calculations
// Includes templates for loading programs and inlined functions

#ifndef LOADING_H
#define LOADING_H

#include "BspTimer.h"

#define COLLECT_MIN_MAX
#define TRAP_DOUBLE_COUNTED_TIME

#ifdef __cplusplus
class ProcLoading
{
	public: enum LoadingTasks
	{
		Spare_Task,
		Motor_Task,
		DataMan_Task,
		NUMBER_OF_TASKS
	};
	public: struct LoadingInfo
	{
#ifdef TRAP_DOUBLE_COUNTED_TIME
		bool States[4]; // Include 4 states for padding
#endif
		unsigned long ExecutionCounter;
		unsigned long BeginingOfPeriod;
		unsigned long AccumulatedRuntimeClocks;
#ifdef TRAP_DOUBLE_COUNTED_TIME
		unsigned long AccumulatedRuntimeClocksInTask;
#endif
#ifdef COLLECT_MIN_MAX
		unsigned long MinExecutionTime;
		unsigned long MaxExecutionTime;
#endif
		unsigned long ExecutionRate;
		float ProcessorLoad;
	};
	public: struct LoadingConfig
	{
		long MaximumIdleTaskCounts;
		//long TicksInASecond;
		long IsrOverhead;
		long CountsPerSecond;
		long DefaultPacketRate;
	};
	public: struct LoadingDigitalConfig
	{
		bool SendDefaultPackets;
		bool Spare;
	};
	public: struct LoadingInputs
	{
		long IdleTaskCounter;
	};
	public: struct LoadingDigitalInputs
	{
		bool Spare;
	};
	public: struct LoadingOutputs
	{
		float IdlePercentage;
		LoadingInfo ModuleInfo[NUMBER_OF_TASKS];
		float TotalLoad;
#ifdef TRAP_DOUBLE_COUNTED_TIME
		float CorrectedLoad;
#endif
	};
	public: struct LoadingDigitalOutputs
	{
		bool Spare;
	};
	private: static LoadingConfig *_config;
	//private: static LoadingDigitalConfig *_digitalConfig;
	private: static LoadingInputs *_analogIn;
	//private: static LoadingDigitalInputs *_digitalIn;
	private: static LoadingOutputs *_analogOut;
	//private: static LoadingDigitalOutputs *_digitalOut;
	private: static bool _dataLinked;
#ifdef TRAP_DOUBLE_COUNTED_TIME
	private: static bool _inTask;
#endif
	public:  static void Initialize(void);
	public:  static void UpdateEverySecond(unsigned long idleCounter);

	// Called when a task begins (ignores ISR overhead)
	public:  static _inline_ void BeginTask(unsigned char task)
	{
		register LoadingInfo *info = &_analogOut->ModuleInfo[task];
#ifdef TRAP_DOUBLE_COUNTED_TIME
		// Note: if the processor is not in a task when this task is kicked off, it shouldn't be in a
		// task when the task ends (this one is running only over the idle task)
		// If it is in a task when this on starts, this one is interrupting that task and should not
		// clear the _inTask variable when it exits.
		info->States[0] = _inTask;
		_inTask = true;
#endif
		info->ExecutionCounter++;
		// Note: Get timestamp as close to actual task as possible to improve error from the loading function calls
		info->BeginingOfPeriod = BspTimer::GetFreeRunningCounter();
	}

	// Called when a task ends (ignores ISR overhead)
	public:  static _inline_ void EndTask(unsigned char task)
	{
		// Presume that the free running counter will work correctly if this is called.
		register LoadingInfo *info = &_analogOut->ModuleInfo[task];
		register unsigned long executionTime = BspTimer::GetFreeRunningCounter() - info->BeginingOfPeriod;
#ifdef COLLECT_MIN_MAX
		if(executionTime < info->MinExecutionTime)
		{
			info->MinExecutionTime = executionTime;
		}
		if(executionTime > info->MaxExecutionTime)
		{
			info->MaxExecutionTime = executionTime;
		}
#endif
		info->AccumulatedRuntimeClocks += executionTime;
#ifdef TRAP_DOUBLE_COUNTED_TIME
		if(info->States[0])
		{
			info->AccumulatedRuntimeClocksInTask += executionTime;
		}
		_inTask = info->States[0];
#endif
	}

	public:  static void LinkData(LoadingConfig *config, LoadingInputs *analogIn, LoadingOutputs *analogOut )
	{
		_config = config;
		_analogIn = analogIn;
		_analogOut = analogOut;
		_dataLinked = true;
	}
};
#endif

#endif // LOADING_H

