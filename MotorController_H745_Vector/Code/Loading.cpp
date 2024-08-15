#include "Loading.h"

ProcLoading::LoadingConfig *ProcLoading::_config;
//ProcLoading::LoadingDigitalConfig *ProcLoading::_digitalConfig;
ProcLoading::LoadingInputs *ProcLoading::_analogIn;
//ProcLoading::LoadingDigitalInputs *ProcLoading::_digitalIn;
ProcLoading::LoadingOutputs *ProcLoading::_analogOut;
//ProcLoading::LoadingDigitalOutputs *ProcLoading::_digitalOut;
bool ProcLoading::_dataLinked = false;
#ifdef TRAP_DOUBLE_COUNTED_TIME
bool ProcLoading::_inTask = false;
#endif

void ProcLoading::Initialize(void)
{
	if(!_dataLinked)
	{
		return;
	}
}

void ProcLoading::UpdateEverySecond(unsigned long idleCounter)
{
	_analogIn->IdleTaskCounter = idleCounter;
	_analogOut->IdlePercentage = idleCounter / (float)_config->MaximumIdleTaskCounts * 100.0f;;
	register LoadingInfo *info = &_analogOut->ModuleInfo[0];
	float totalLoad = 0.0f;
#ifdef TRAP_DOUBLE_COUNTED_TIME
	float loadCountedTwice = 0.0f;
#endif
	for(char tsk = NUMBER_OF_TASKS; tsk; tsk--)
	{
// Note: clearing these every second isn't that useful.
#ifdef COLLECT_MIN_MAX
		info->MinExecutionTime = 0x7FFFFFFF;
		info->MaxExecutionTime = 0;
#endif
		info->ExecutionRate = info->ExecutionCounter;
		info->ExecutionCounter = 0;
		// Add the overhead for the ISR to the calculation.
		long accumulatedClocks = info->AccumulatedRuntimeClocks + _config->IsrOverhead * info->ExecutionRate;
		info->AccumulatedRuntimeClocks = 0;
		float processorLoad = (float)accumulatedClocks / (float)_config->CountsPerSecond * 100.0f;
		totalLoad += processorLoad;
		info->ProcessorLoad = processorLoad;
#ifdef TRAP_DOUBLE_COUNTED_TIME
		// In an ideal world, we would track the number of executions from another task
		// and subtract the overhead for the ISR from the calculation.
		accumulatedClocks = info->AccumulatedRuntimeClocksInTask;
		processorLoad = (float)accumulatedClocks / (float)_config->CountsPerSecond * 100.0f;
		loadCountedTwice += processorLoad;
#endif
		info++;
	}
	_analogOut->TotalLoad = totalLoad;
#ifdef TRAP_DOUBLE_COUNTED_TIME
	_analogOut->CorrectedLoad = totalLoad - loadCountedTwice;
#endif
}

