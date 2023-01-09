#include "Loading.h"
#include "BspAnalog.h"

#ifndef MEMORY_STRUCTURE_H
#define MEMORY_STRUCTURE_H

class MemoryStructure
{
	public: struct MemoryAnalogInputs
	{
		BspAnalog::AnalogInputs Analog;
		long Load;
		long Bookend;
	};

	public: struct MemoryDigitalInputs
	{
		bool Analog;
		bool Load;
		bool Bookend;
	};

	public: struct MemoryAnalogOutputs
	{
		long Analog;
		Loading::LoadingData Load[Loading::NUMBER_OF_ELEMENTS];
		long Bookend;
	};

	public: struct MemoryDigitalOutputs
	{
		bool Analog;
		bool Load;
		long Bookend;
	};

	public: struct MemoryAnalogConfig
	{
		BspAnalog::AnalogConfig Analog;
		long Load;
		long Bookend;
	};

	public: struct MemoryDigitalConfig
	{
		bool Analog;
		bool Load;
		bool Bookend;
	};

	public: struct MemoryStruct
	{
		MemoryAnalogInputs AnalogInputs;
		MemoryAnalogOutputs AnalogOutputs;
		MemoryDigitalInputs DigitalInputs;
		MemoryDigitalOutputs DigitalOutputs;
	};

	public: struct NonVolatileStruct
	{
		MemoryAnalogConfig AnalogConfig;
		MemoryDigitalConfig DigitalConfig;
	};
	/* Variable Declarations */
	public:  static MemoryStruct _memStruct;
	public:  static NonVolatileStruct _nvmStruct;
	/* Function Declarations */
	public:  static void Initialize(void);
};

#endif //MEMORY_STRUCTURE_H
