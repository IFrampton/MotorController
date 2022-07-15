#include "MemoryStructure.h"

MemoryStructure::MemoryStruct MemoryStructure::_memStruct;
MemoryStructure::NonVolatileStruct MemoryStructure::_nvmStruct;

void MemoryStructure::Initialize()
{
	Loading::LinkMemorySpace(&_memStruct.AnalogOutputs.Load[0]);
	BspAnalog::LinkMemorySpace(&_nvmStruct.AnalogConfig.Analog);
}
