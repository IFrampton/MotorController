#include "BspAnalog.h"
#include "MemoryStructure.h"

BspAnalog::AnalogConfig *BspAnalog::_config = 0;
bool BspAnalog::_initialized = false;
bool BspAnalog::_channel4 = false;
void (*BspAnalog::_callback)() = DummyFunction;

void BspAnalog::Initialize(void)
{
	// Enable clocks
	SYSCON->ADCCLKSEL = 0; // Use System Clock for ADC
	SYSCON->AHBCLKCTRLX[0] |= (1 << 27); // Enable ADC Clock
	SYSCON->ADCCLKDIV = 1; // Use 48MHz ADC0 Clock (System / 2)

	// Power up the Auxiliary Biasing
	PMC->PDRUNCFG0 &= ~(1 << 19);

	// Setup ADC0
	// Clear all data to reset values
	ADC0->CTRL = (7 << 16)	| // CAL_AVGS = 4 (Average 16 samples in hardware), gives 25kHz update rate
				 (1 << 9)	| // RSTFIFO1 = 0 (Reset FIFO1)
				 (1 << 8)	| // RSTFIFO0 = 0 (Reset FIFO0)
				 (0 << 4)	| // CALOFS = 0 (Do not request Offset Calibration)
				 (0 << 3)	| // CAL_REQ = 0 (Do not request Calibration)
				 (1 << 2)	| // DOZEN = 0 (ADC is disabled in doze mode)
				 (1 << 1)	| // RST = 1 (Reset ADC Logic)
				 (0 << 0)	; // ADCEN = 0 (ADC is Disabled, Enable Later)
	ADC0->CTRL = (7 << 16)	| // CAL_AVGS = 4 (Average 16 samples in hardware), gives 25kHz update rate
				 (0 << 9)	| // RSTFIFO1 = 0 (Reset FIFO1)
				 (0 << 8)	| // RSTFIFO0 = 0 (Reset FIFO0)
				 (0 << 4)	| // CALOFS = 0 (Do not request Offset Calibration)
				 (0 << 3)	| // CAL_REQ = 0 (Do not request Calibration)
				 (0 << 2)	| // DOZEN = 0 (ADC is disabled in doze mode)
				 (0 << 1)	| // RST = 1 (Reset ADC Logic)
				 (0 << 0)	; // ADCEN = 0 (ADC is Disabled, Enable Later)
	// Do not power ADC yet
	ADC0->CFG =	 (1 << 28)	| // PWREN = 1 (ADC is powered at all times)
				 (127 << 16)| // PUDLY = 127 (ADC is activated after a power up delay of 127)
				 (1 << 10)	| // HPT_EXDI = 1 (High Priority Trigger Exceptions are disabled)
				 (1 << 9)	| // TCMDRES = 1 (Interrupted sequences will resume, not restart)
				 (1 << 8)	| // TRES = 1 (Interrupted sequences will be resumed)
				 (2 << 6)	| // REFSEL = 2 (Use VREFP pin voltage as a reference) (Trying VDDA instead)
				 (3 << 4)	| // PWRSEL = 3 (Highest power mode)
				 (3 << 0)	; // TPRICTRL = 3 (Complete all queued transactions before triggering)
	ADC0->PAUSE = 0;		  // No Pause applied at all (Read as fast as possible)
	// Analog Trigger Setup
	ADC0->TCTRL[0] = (1 << 24)	| // TCMD = 1 (Execute Command 1)
					 (0 << 16)	| // TDLY = 0 (Trigger Delay Set to minimum)
					 (0 << 15)	| // RSYNC = 0 (Trigger will not Resync)
					 (0 << 8)	| // TPRI = 0 (Trigger Priority set to 1 = highest)
					 (0 << 2)	| // FIFO_SEL_B = 0 (FIFO 1 Selected for Channel B)
					 (0 << 1)	| // FIFO_SEL_A = 0 (FIFO 0 Selected for Channel A)
					 (0 << 0)	; // HTEN = 0 (Hardware Trigger source is disabled)
	ADC0->TCTRL[1] = (2 << 24)	| // TCMD = 1 (Execute Command 1)
					 (0 << 16)	| // TDLY = 0 (Trigger Delay Set to minimum)
					 (0 << 15)	| // RSYNC = 0 (Trigger will not Resync)
					 (1 << 8)	| // TPRI = 1 (Trigger Priority set to 2 = lower)
					 (0 << 2)	| // FIFO_SEL_B = 0 (FIFO 1 Selected for Channel B)
					 (0 << 1)	| // FIFO_SEL_A = 0 (FIFO 0 Selected for Channel A)
					 (0 << 0)	; // HTEN = 0 (Hardware Trigger source is disabled)
	ADC0->TCTRL[2] = (3 << 24)	| // TCMD = 1 (Execute Command 1)
					 (0 << 16)	| // TDLY = 0 (Trigger Delay Set to minimum)
					 (0 << 15)	| // RSYNC = 0 (Trigger will not Resync)
					 (2 << 8)	| // TPRI = 2 (Trigger Priority set to 3 = lower)
					 (0 << 2)	| // FIFO_SEL_B = 0 (FIFO 1 Selected for Channel B)
					 (0 << 1)	| // FIFO_SEL_A = 0 (FIFO 0 Selected for Channel A)
					 (0 << 0)	; // HTEN = 0 (Hardware Trigger source is disabled)
	ADC0->TCTRL[3] = (4 << 24)	| // TCMD = 1 (Execute Command 1)
					 (0 << 16)	| // TDLY = 0 (Trigger Delay Set to minimum)
					 (0 << 15)	| // RSYNC = 0 (Trigger will not Resync)
					 (3 << 8)	| // TPRI = 3 (Trigger Priority set to 4 = lower)
					 (0 << 2)	| // FIFO_SEL_B = 0 (FIFO 1 Selected for Channel B)
					 (0 << 1)	| // FIFO_SEL_A = 0 (FIFO 0 Selected for Channel A)
					 (0 << 0)	; // HTEN = 0 (Hardware Trigger source is disabled)
	ADC0->TCTRL[4] = (5 << 24)	| // TCMD = 5 (Execute Command 5)
					 (0 << 16)	| // TDLY = 0 (Trigger Delay Set to minimum)
					 (0 << 15)	| // RSYNC = 0 (Trigger will not Resync)
					 (4 << 8)	| // TPRI = 4 (Trigger Priority set to 5 = lower)
					 (0 << 2)	| // FIFO_SEL_B = 0 (FIFO 1 Selected for Channel B)
					 (0 << 1)	| // FIFO_SEL_A = 0 (FIFO 0 Selected for Channel A)
					 (0 << 0)	; // HTEN = 0 (Hardware Trigger source is disabled)
	// Analog Command Registers
	// These are set up to loop through 5 measurements before ending.
	// Note: The last measurement will toggle between two readings:
	// Heat-sink Temperature (Channel 4) and
	// Internal Temperature (Channel 26)
	ADC0->CMD[0].CMDL = (1 << 7)	| // MODE = 1 (High Resolution Mode)
						(3 << 5)	| // CTYPE = 3 (Dual single-ended conversion)
						(0 << 0)	; // ADCH = 0 (Select Channel A = 0 and Channel B = 0)
	ADC0->CMD[0].CMDH = (2 << 24)	| // NEXT = 2 (Perform Command 2 Next)
						(0 << 16)	| // LOOP = 0 (Don't repeat this command)
						(7 << 12)	| // AVGS = 4 (Average 16 samples)
						(0 << 8)	| // STS = 0 (Minimum sample time)
						(0 << 7)	| // LWI = 0 (Don't loop through the channels)
						(0 << 2)	| // WAIT_TRIG = 0 (Execute this command immediately)
						(0 << 0)	; // CMPEN = 0 (Compare is Disabled)
	ADC0->CMD[1].CMDL = (1 << 7)	| // MODE = 1 (High Resolution Mode)
						(3 << 5)	| // CTYPE = 3 (Dual single-ended conversion)
						(1 << 0)	; // ADCH = 1 (Select Channel A = 1 and Channel B = 1)
	ADC0->CMD[1].CMDH = (3 << 24)	| // NEXT = 3 (Perform Command 3 Next)
						(0 << 16)	| // LOOP = 0 (Don't repeat this command)
						(4 << 12)	| // AVGS = 4 (Average 16 samples)
						(0 << 8)	| // STS = 0 (Minimum sample time)
						(0 << 7)	| // LWI = 0 (Don't loop through the channels)
						(0 << 2)	| // WAIT_TRIG = 0 (Execute this command immediately)
						(0 << 0)	; // CMPEN = 0 (Compare is Disabled)
	ADC0->CMD[2].CMDL = (1 << 7)	| // MODE = 1 (High Resolution Mode)
						(3 << 5)	| // CTYPE = 3 (Dual single-ended conversion)
						(2 << 0)	; // ADCH = 2 (Select Channel A = 2 and Channel B = 2)
	ADC0->CMD[2].CMDH = (4 << 24)	| // NEXT = 4 (Perform Command 4 Next)
						(0 << 16)	| // LOOP = 0 (Don't repeat this command)
						(4 << 12)	| // AVGS = 4 (Average 16 samples)
						(0 << 8)	| // STS = 0 (Minimum sample time)
						(0 << 7)	| // LWI = 0 (Don't loop through the channels)
						(0 << 2)	| // WAIT_TRIG = 0 (Execute this command immediately)
						(0 << 0)	; // CMPEN = 0 (Compare is Disabled)
	ADC0->CMD[3].CMDL = (1 << 7)	| // MODE = 1 (High Resolution Mode)
						(3 << 5)	| // CTYPE = 3 (Dual single-ended conversion)
						(3 << 0)	; // ADCH = 3 (Select Channel A = 3 and Channel B = 3)
	ADC0->CMD[3].CMDH = (5 << 24)	| // NEXT = 5 (Perform Command 5 Next)
						(0 << 16)	| // LOOP = 0 (Don't repeat this command)
						(4 << 12)	| // AVGS = 4 (Average 16 samples)
						(0 << 8)	| // STS = 0 (Minimum sample time)
						(0 << 7)	| // LWI = 0 (Don't loop through the channels)
						(0 << 2)	| // WAIT_TRIG = 0 (Execute this command immediately)
						(0 << 0)	; // CMPEN = 0 (Compare is Disabled)
	ADC0->CMD[4].CMDL = (1 << 7)	| // MODE = 1 (High Resolution Mode)
						(1 << 5)	| // CTYPE = 3 (Channel A single-ended conversion)
						(4 << 0)	; // ADCH = 4 (Select Channel A = 4 and Channel B = 4)
	ADC0->CMD[4].CMDH = (0 << 24)	| // NEXT = 1 (Start Over) (Note: This does not require re-triggering)
						(0 << 16)	| // LOOP = 0 (Don't repeat this command)
						(4 << 12)	| // AVGS = 4 (Average 16 samples)
						(0 << 8)	| // STS = 0 (Minimum sample time)
						(0 << 7)	| // LWI = 0 (Don't loop through the channels)
						(0 << 2)	| // WAIT_TRIG = 0 (Execute this command immediately)
						(0 << 0)	; // CMPEN = 0 (Compare is Disabled)
	_channel4 = true;

	// Enable the ADC
	ADC0->CTRL |=  (1 << 0);

	// Calibrate the ADC
	Calibrate();

	// Setup Interrupts (to allow Analog Monitoring)
	// Note: Only Trigger at end of conversion (trigger 0)
	// Set Watermark to 8
	ADC0->FCTRL[0] = (8 << 16);
	// Now Triggering on Watermark
	ADC0->IE = (1 << 0); //(1 << 16);
	NVIC_EnableIRQ(ADC0_IRQn);
	NVIC_SetPriority(ADC0_IRQn, 10);
	// Kick off Conversion
	ADC0->SWTRIG = (0x1 << 0); // Software Trigger

	// Update Initialized Status for other function calls
	// Note: This is only valid if the configuration is pointed to the correct location in NVM
	if(_config)
	{
		_initialized = true;
	}
}

unsigned char BspAnalog::Calibrate(void)
{
	// Calibrate the comparison
	/* 1. Run the CALOFS calibration routine by asserting CTRL[CALOFS] to 0b1 with the
	number of averages controlled by CTRL[CAL_AVGS].*/
#ifdef CALL_INTERNAL_OFFSET
	ADC0->CTRL |= (1 << 4);
	//while(ADC0->STAT & (1 << 11))
	while(!(ADC0->STAT & (1 << 10)))
	{
		__asm("NOP");
	}
	if(!(ADC0->STAT & (1 << 10)))
		return 0xFF;
#else
	ADC0->OFSTRIM = (16 << 16) + (16 << 0);
#endif
	/*2. Initiate the ADC to run a calibration routine. Assert CTRL[CAL_REQ] to 0b1 with the
	number of averages controlled by CTRL[CAL_AVGS].*/
	ADC0->CTRL |= (1 << 3);
	//while(ADC0->STAT & (1 << 11))
	//while(!(ADC0->STAT & (1 << 10)))
	/*Poll the GCCa[RDY] flags until they are asserted. It will indicate the ADC calibration
	data has been calculated.*/
	while(!(ADC0->GCC[0] & (1 << 24)))
	{
		__asm("NOP");
	}
	/*4. Read the GCCa[GAIN_CAL] registers and store these value for use in later
	calculations.*/
	float gccGainCal = (float)(ADC0->GCC[0] & 0xFFFF);
	/*5. Calculate gain_offset = (131072)/(131072-GCCa[GAIN_CAL]). It will result in a
	floating point value somewhere within the range of 1 to 2.*/
	float gain_offset = 131072.0f / (131072.0f - gccGainCal);
	gain_offset *= 65536.0f;
	/*6. Round the fractional component of each gain_offset to 16-bits, and write these values
	to the GCRa[GCALR] registers.*/
	unsigned long val = ((unsigned long)gain_offset & 0xFFFF);
	/*7. Once GCRa[GCALR] contains the 16-bit fractional result from gain_offset, set the
	GCRa[RDY] flag to indicate this value is valid.*/
	ADC0->GCR[0] = val | ( 1 << 24);
	while(!(ADC0->GCC[1] & (1 << 24)))
	{
		__asm("NOP");
	}
	/*4. Read the GCCa[GAIN_CAL] registers and store these value for use in later
	calculations.*/
	gccGainCal = (float)(ADC0->GCC[1] & 0xFFFF);
	/*5. Calculate gain_offset = (131072)/(131072-GCCa[GAIN_CAL]). It will result in a
	floating point value somewhere within the range of 1 to 2.*/
	gain_offset = 131072.0f / (131072.0f - gccGainCal);
	gain_offset *= 65536.0f;
	/*6. Round the fractional component of each gain_offset to 16-bits, and write these values
	to the GCRa[GCALR] registers.*/
	val = ((unsigned long)gain_offset & 0xFFFF);
	/*7. Once GCRa[GCALR] contains the 16-bit fractional result from gain_offset, set the
	GCRa[RDY] flag to indicate this value is valid.*/
	ADC0->GCR[1] = val | (1 << 24);
	if(ADC0->STAT & (1 << 10))
		return 0;
	else
		return 0xFF;
}

void BspAnalog::DummyFunction(void)
{
	//__asm("NOP");
}

extern "C"
{
void ADC0_IRQHandler(void)
{
	Loading::StartMeasuredSection(4);
	register long *offset = (long *)BspAnalog::_config->Offset;
	register float *gain = (float *)BspAnalog::_config->Gain;
	register float *loc = (float *)MemoryStructure::_memStruct.AnalogInputs.Analog.Data;
	register volatile unsigned short *fifo = (volatile unsigned short *)ADC0->RESFIFO;
	// Unrolled loop for performance
	//for(unsigned char x = (sizeof(_config->Offset) / sizeof(long) >> 1); x ; x--)
	//{
		register unsigned short sample = *fifo;
		register float correctedSample = (float)((long)sample - *(offset++)) * *(gain++);
		*(loc++) = correctedSample;
		sample = *fifo;
		correctedSample = (float)((long)sample - *(offset++)) * *(gain++);
		*(loc++) = correctedSample;
		sample = *fifo;
		correctedSample = (float)((long)sample - *(offset++)) * *(gain++);
		*(loc++) = correctedSample;
		sample = *fifo;
		correctedSample = (float)((long)sample - *(offset++)) * *(gain++);
		*(loc++) = correctedSample;
		sample = *fifo;
		correctedSample = (float)((long)sample - *(offset++)) * *(gain++);
		*(loc++) = correctedSample;
		sample = *fifo;
		correctedSample = (float)((long)sample - *(offset++)) * *(gain++);
		*(loc++) = correctedSample;
		sample = *fifo;
		correctedSample = (float)((long)sample - *(offset++)) * *(gain++);
		*(loc++) = correctedSample;
		sample = *fifo;
		correctedSample = (float)((long)sample - *(offset++)) * *(gain++);
		*(loc++) = correctedSample;
		// Note: Use Position 10 if Reading the Temperature Sensor
		if(!BspAnalog::_channel4)
		{
			offset++;
			gain++;
			loc++;
			ADC0->CMD[4].CMDL = (1 << 7)	| // MODE = 1 (High Resolution Mode)
								(1 << 5)	| // CTYPE = 3 (Channel A single-ended conversion)
								(4 << 0)	; // ADCH = 4 (Select Channel A = 4 and Channel B = 4)
			BspAnalog::_channel4 = true;
		}
		else
		{
			ADC0->CMD[4].CMDL = (1 << 7)	| // MODE = 1 (High Resolution Mode)
								(1 << 5)	| // CTYPE = 3 (Channel A single-ended conversion)
								(4 << 0)	; // ADCH = 4 (Select Channel A = 4 and Channel B = 4)
			// Note: The internal Temperature Sensor requires too many hoops to use.
			//BspAnalog::_channel4 = false;
		}
		sample = *fifo;
		correctedSample = (float)((long)sample - *(offset++)) * *(gain++);
		*(loc++) = correctedSample;
		// Read one extra from the FIFO to make sure it's empty
		sample = *fifo;
	//}
	ADC0->SWTRIG = (0x1 << 0); // Software Trigger
	(*BspAnalog::_callback)();
	Loading::StopMeasuredSection(4);
}
}
