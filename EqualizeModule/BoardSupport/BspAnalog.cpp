#include "BspAnalog.h"
#include "MemoryStructure.h"

BspAnalog::AnalogConfig *BspAnalog::_config = 0;
unsigned short BspAnalog::_analogData[4][4];
unsigned char BspAnalog::_dataIndex;
bool BspAnalog::_initialized = false;
bool BspAnalog::_channel4 = false;
void (*BspAnalog::_callback)() = DummyFunction;

void BspAnalog::Initialize(void)
{
	// Power up the Analog Converter
	SYSCON->PDRUNCFG &= ~(1 << 4);

	// Enable clocks
	SYSCON->SYSAHBCLKCTRL |= (1 << 24); // Enable ADC Clock

	// Setup ADC0
	// Clear all data to reset values
	ADC0->CTRL = (0 << 30)	| // CALMODE = 0 (Not calibrating)
				 (0 << 10)	| // LPWRMODE = 0 (Normal Operation)
#ifdef USE_30MHz_SYSTEM_CLOCK
				 (1 << 0)	; // CLKDIV = 1 (Use 15MHz clock)
#else
				 //(2 << 0)	; // CLKDIV = 2 (Use 24MHz clock) // For 72MHz
				 (1 << 0)	; // CLKDIV = 1 (Use 24MHz clock) // For 48MHz
#endif
	ADC0->SEQ_CTRL[0] = 0; // Disable Sequence A
	ADC0->SEQ_CTRL[1] = 0; // Disable Sequence B

	ADC0->SEQ_CTRL[0] = ((unsigned int)0 << 31) |	// Enable Sequence A
						(1 << 30)	|	// MODE = 1 (DMA request will occur after all reads are complete)
						(0 << 29)	|	// LOWPRIO = 0 (Do not interrupt Sequence B)
						(0 << 28)	|	// SINGLESTEP = 0 (All channels are read from a single trigger)
						(1 << 27)	|	// BURST = 0 (Conversion relies on a trigger from the software to keep it synchronous)
						(0 << 26)	|	// START = 0 (Do not trigger a conversion at this time)
						(0 << 19)	|	// SYNCBYPASS = 0 (Do not bypass the synchronization flip flop)
						(0 << 18)	|	// TRIGPOL = 0 (trigger on negative edge (unused))
						(0 << 12)	|	// TRIGGER = 0 (select the hardware trigger to use (none))
						(0 << 11)	|	// CHANNEL0_11 = 0 (Do not read Channel 11)
						(1 << 10)	|	// CHANNEL0_10 = 1 (Read Channel 10, Equalize Current)
						(1 << 9)	|	// CHANNEL0_9 = 1 (Read Channel 9, Cell Voltage)
						(0 << 8)	|	// CHANNEL0_8 = 0 (Do not read Channel 8)
						(0 << 7)	|	// CHANNEL0_7 = 0 (Do not read Channel 7)
						(0 << 6)	|	// CHANNEL0_6 = 0 (Do not read Channel 6)
						(0 << 5)	|	// CHANNEL0_5 = 0 (Do not read Channel 5)
						(0 << 4)	|	// CHANNEL0_4 = 0 (Do not read Channel 4)
						(1 << 3)	|	// CHANNEL0_3 = 1 (Read Channel 3, Equalize Bus Voltage)
						(1 << 2)	|	// CHANNEL0_2 = 1 (Read Channel 2, Cell Temperature)
						(0 << 1)	|	// CHANNEL0_1 = 0 (Do not read Channel 1)
						(0 << 0)	;	// CHANNEL0_0 = 0 (Do not read Channel 0)

	ADC0->THR0_LOW = (0 << 4); // Try to get out of range (This is not used)
	ADC0->THR1_LOW = (0 << 4); // Try to get out of range (This is not used)
	ADC0->THR0_HIGH = (0xFFF << 4); // Try to get out of range (This is not used)
	ADC0->THR1_HIGH = (0xFFF << 4); // Try to get out of range (This is not used)
	ADC0->CHAN_THRSEL = 0; // Set all channels to use threshold 0 (Not that it matters; this is not used)

	ADC0->INTEN = (1 << 0); // The analog is not using interrupts; it uses DMA, which is set to the end of sequence A.
	ADC0->TRM = (1 << 5)	|	// VRANGE = 1 (Configure for low voltage (2.4-2.7V))
				(0 << 0)	;	// RESERVED = 0 (unused)

	NVIC_EnableIRQ(ADC0_SEQA_IRQn);
	NVIC_SetPriority(ADC0_SEQA_IRQn, 15);

	// Calibrate the ADC
	Calibrate();

	// Trigger a Conversion to start;
	ADC0->SEQ_CTRL[0] = ((unsigned int)1 << 31) |	// Enable Sequence A
						(1 << 30)	|	// MODE = 1 (DMA request will occur after all reads are complete)
						(0 << 29)	|	// LOWPRIO = 0 (Do not interrupt Sequence B)
						(0 << 28)	|	// SINGLESTEP = 0 (All channels are read from a single trigger)
						(1 << 27)	|	// BURST = 0 (Conversion relies on a trigger from the software to keep it synchronous)
						(1 << 26)	|	// START = 0 (Do not trigger a conversion at this time)
						(0 << 19)	|	// SYNCBYPASS = 0 (Do not bypass the synchronization flip flop)
						(0 << 18)	|	// TRIGPOL = 0 (trigger on negative edge (unused))
						(0 << 12)	|	// TRIGGER = 0 (select the hardware trigger to use (none))
						(0 << 11)	|	// CHANNEL0_11 = 0 (Do not read Channel 11)
						(1 << 10)	|	// CHANNEL0_10 = 1 (Read Channel 10, Equalize Current)
						(1 << 9)	|	// CHANNEL0_9 = 1 (Read Channel 9, Cell Voltage)
						(0 << 8)	|	// CHANNEL0_8 = 0 (Do not read Channel 8)
						(0 << 7)	|	// CHANNEL0_7 = 0 (Do not read Channel 7)
						(0 << 6)	|	// CHANNEL0_6 = 0 (Do not read Channel 6)
						(0 << 5)	|	// CHANNEL0_5 = 0 (Do not read Channel 5)
						(0 << 4)	|	// CHANNEL0_4 = 0 (Do not read Channel 4)
						(1 << 3)	|	// CHANNEL0_3 = 1 (Read Channel 3, Equalize Bus Voltage)
						(1 << 2)	|	// CHANNEL0_2 = 1 (Read Channel 2, Cell Temperature)
						(0 << 1)	|	// CHANNEL0_1 = 0 (Do not read Channel 1)
						(0 << 0)	;	// CHANNEL0_0 = 0 (Do not read Channel 0)

	// Update Initialized Status for other function calls
	// Note: This is only valid if the configuration is pointed to the correct location in NVM
	if(_config)
	{
		_initialized = true;
	}
}

unsigned char BspAnalog::Calibrate(void)
{
	// Setup ADC0
	// Call calibration routine
	ADC0->CTRL = (1 << 30)	| // CALMODE = 0 (Not calibrating)
				 (0 << 10)	| // LPWRMODE = 0 (Normal Operation)
#ifdef USE_30MHz_SYSTEM_CLOCK
				 (1 << 0)	; // CLKDIV = 0 (Use 15MHz clock)
#else
				 (2<< 0)	; // CLKDIV = 2 (Use 12MHz clock)
#endif
	while(ADC0->CTRL & (1 << 30))
	{
		__asm("NOP");
	}
	return 0xFF;
}

void BspAnalog::UpdateAnalog(void)
{
#ifdef AVERAGE_SAMPLES
	register long *offset = (long *)BspAnalog::_config->Offset;
	register long *gain = (long *)BspAnalog::_config->Gain;
	register unsigned char *bitshift = (unsigned char *)BspAnalog::_config->BitShift;
	register long *loc = (long *)MemoryStructure::_memStruct.AnalogInputs.Analog.Data;
	register unsigned short *raw = (unsigned short *)MemoryStructure::_memStruct.AnalogInputs.Analog.RawData;
	register unsigned short *bufferLoc = BspAnalog::_analogData[0];

	register long sample = 0;
	// Grab Samples
	for(unsigned char y = 4; y; y--)
	{
		for(unsigned char x = 4; x; x--)
		{
			sample += (long)*(bufferLoc); // DAT2
			bufferLoc += 4;
		}
		// Convert to 12-bit for transmission
		*(raw++) = sample >> 6;
		// Scale and correct the sample
		*(loc++) = ((sample - *(offset++)) * *(gain++)) >> *(bitshift++);
		bufferLoc -= 15;
		sample = 0;
	}
#endif
}

void BspAnalog::DummyFunction(void)
{
	//__asm("NOP");
}

extern "C"
{
void ADC0_SEQA_IRQHandler(void)
{
	Loading::StartMeasuredSection(4);
#ifdef AVERAGE_SAMPLES
	register unsigned short *loc = (unsigned short *)BspAnalog::_analogData + (BspAnalog::_dataIndex << 2);
	register volatile unsigned short *adcReg = (volatile unsigned short *)&ADC0->DAT[2];
	register unsigned short sample = *adcReg; // DAT2
	*(loc++) = sample;
	sample = *(adcReg + 2); // DAT3
	*(loc++) = sample;
	sample = *(adcReg + 14); // DAT9
	*(loc++) = sample;
	sample = *(adcReg + 16); // DAT10
	*(loc++) = sample;
	BspAnalog::_dataIndex++;
	BspAnalog::_dataIndex &= 0x3;
#else
	register long *offset = (long *)BspAnalog::_config->Offset;
	register long *gain = (long *)BspAnalog::_config->Gain;
	register unsigned char *bitshift = (unsigned char *)BspAnalog::_config->BitShift;
	register long *loc = (long *)MemoryStructure::_memStruct.AnalogInputs.Analog.Data;
	register volatile unsigned short *adcReg = (volatile unsigned short *)&ADC0->DAT[2];

	// Grab Samples
	register unsigned short sample = *adcReg; // DAT2
	register long correctedSample = (((long)sample - *(offset++)) * *(gain++)) >> *(bitshift++);
	*(loc++) = correctedSample;
	sample = *(adcReg + 2); // DAT3
	correctedSample = (((long)sample - *(offset++)) * *(gain++)) >> *(bitshift++);
	*(loc++) = correctedSample;
	sample = *(adcReg + 14); // DAT9
	correctedSample = (((long)sample - *(offset++)) * *(gain++)) >> *(bitshift++);
	*(loc++) = correctedSample;
	sample = *(adcReg + 16); // DAT10
	correctedSample = (((long)sample - *(offset++)) * *(gain++)) >> *(bitshift++);
	*(loc++) = correctedSample;
#endif
	// kick off next conversion
	//ADC0->SEQ_CTRL[0] |= (1 << 26);
	(*BspAnalog::_callback)();
	Loading::StopMeasuredSection(4);
	// Clear Sequence A flag
	ADC0->FLAGS |= (1 << 28);
}
}
