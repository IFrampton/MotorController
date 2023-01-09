#include "Main.h"
#include "BspTimer.h"
#include "SlowTimer.h"
#include "BspGpio.h"
#include "BspFlash.h"
#include "BspDma.h"
#include "BspSerial.h"
#include "BspPwm.h"
//#include "Protection.h"
#include "MemoryStructure.h"
#include "Loading.h"

unsigned char Main::_digitalOutputs[TOTAL_OUTPUTS];
long Main::_counterValueOnLastUpdate = 0;
unsigned long Main::_idleTaskCounter = 0;
long Main::_updatePeriod = 1200;
unsigned long Main::_periodCounter = 0;
unsigned long Main::_timePeriod = 0;

unsigned char Main::_ledTracker = 0;

unsigned long Main::_pwm[12];

bool Main::_writeToFlash = false;

#define DIR0 *((volatile unsigned int *)(0xA0002000))
#define NOT0 *((volatile unsigned int *)(0xA0002300))

int main(void)
{
	SystemCoreClockUpdate();
	Main::InitialBootup();
	return 0;
}

void Main::InitialBootup()
{
	// BspFlash::WriteConfig(); // Used to clear flash error
	// Initialize all peripherals here
	BspTimer::Initialize();
	BspTimer::SetupFreeRunningCounter();
	BspFlash::Initialize();
	MemoryStructure::Initialize();
	BspAnalog::Initialize();
	Loading::Initialize();
	SlowTimer::Initialize();
	BspGpio::Initialize();
	//Protection::Initialize();
	// Setup GPIO
	// The WAKE output allows the processor to shut the board down, conserving power.
	// The Analog inputs and PWM outputs are non-functional when the processor holding the wake output low (off).
	// The UART receive may be active with WAKE inactive, but only because it is able to power the switched
	// 2.5V power supply separately from the regulator controlled by the processor.
	// The UART transmit is only functional if the receive is active or the WAKE output is high (on).
	// The output is pulled high by a 1M resistor, so the rest of the board is powered until the processor boots.
	// NOTE: The WAKE output is only supposed to be low when the processor is in a deep sleep mode; to prevent draining the
	// cell it it responsible for. The processor wakeup logic is handled and described in the SleepLogic.cpp file.
	_digitalOutputs[WAKE] = BspGpio::SetupDigitalOutput(0, 8); // This is really 0.10, but the addresses are all mixed up.
	BspGpio::On(_digitalOutputs[WAKE]);

	// Setup Analog
	// Note: The inputs are out of order, so this has to accommodate.
	//void BspGpio::SetupGeneric(unsigned char port, unsigned char pin, unsigned char mux, bool pullup, bool pulldown, bool analog, unsigned char anInput)
	BspGpio::SetupGeneric(0, 18, 0, false, false, true, 2); // ADC0_2
	BspGpio::SetupGeneric(0, 25, 0, false, false, true, 3); // ADC0_3
	BspGpio::SetupGeneric(0, 0, 0, false, false, true, 9); 	// ADC0_9
	BspGpio::SetupGeneric(0, 1, 0, false, false, true, 10); // ADC0_10

	// Setup UART
	// P0_4 = UART0_TXD_O (MUX = 0);
	BspGpio::SetupGeneric(0, 4, 0);
	// P0_9 = UART0_RXD_I (MUX = 1);
	// Note: This is an open drain pin, thus it is used as an input.
	//BspGpio::SetupGeneric(0, 7, 1);
	BspGpio::SetupGeneric(0, 11, 1);
	BspDma::Initialize();
	BspSerial::Initialize();

	// Setup PWM
	// Note: The pins are all confused (big time)
	//BspGpio::SetupGeneric(0, 17, 31);
	BspGpio::SetupGeneric(0, 0, 31);
	//BspGpio::SetupGeneric(0, 11, 32);
	BspGpio::SetupGeneric(0, 1, 32);
	//BspGpio::SetupGeneric(0, 14, 33);
	BspGpio::SetupGeneric(0, 8, 33);
	//BspGpio::SetupGeneric(0, 13, 34);
	BspGpio::SetupGeneric(0, 9, 34);
	//BspGpio::SetupGeneric(0, 2, 35);
	BspGpio::SetupGeneric(0, 12, 35);
	//BspGpio::SetupGeneric(0, 10, 36);
	BspGpio::SetupGeneric(0, 15, 36);
	// Setup up input from the UART0_RX pin (0_11) to trigger one of the counters (this is used for Receiver Timeout detection)
	BspGpio::SetupGeneric(0, 11, 27);
	BspPwm::Initialize(50000, 10);


	// Setup Low Priority Tasks
	SlowTimer::SetupTimer(1000, ToggleLed);
	SlowTimer::SetupTimer(1000, CheckToWrite);

	// Setup Timer (Temporary - for testing)
	BspTimer::SetupTimer(960, HighPriTimer);
	BspPwm::SetupCallback(PwmUpdate);

	// When finished initializing, call idle task (with Slow Timer operating at 1kHz)
	IdleTask(1000);
}

void Main::IdleTask(unsigned long slowTimerFrequency)
{
	// TODO: insert code here
	//DIR0 = 0x00000113;
	//NOT0 = 0x00000001;

	_updatePeriod = SystemCoreClock / slowTimerFrequency;
	while(1)
	{
		_idleTaskCounter++;
		long time = BspTimer::GetFreeRunningCounter();
		long timePeriod = (_counterValueOnLastUpdate - time);
		// correct for the clumsy 24-bit counter
		if(timePeriod < 0)
		{
			timePeriod += 0x1000000;
		}
		if(timePeriod >= _updatePeriod)
		{
			_counterValueOnLastUpdate -= _updatePeriod;
			if(_counterValueOnLastUpdate < 0)
			{
				_counterValueOnLastUpdate += 0x1000000;
			}
			// Update Slow Timer
			SlowTimer::PeriodicUpdate(timePeriod);
			// Keep track of the total time elapsed
			_timePeriod += timePeriod;
			if(++_periodCounter >= slowTimerFrequency)
			{
				_periodCounter = 0;
				Loading::UpdateEvery1Sec(_timePeriod);
				_timePeriod = 0;
			}
		}
		// "Dummy" NOP to allow source level single
		// stepping of tight while() loop
		//__asm volatile ("nop");
	   //NOT0 = 0x00000013;
	}
}

void Main::ToggleLed(void)
{
	Loading::StartMeasuredSection(1);
#ifdef USE_LED_AS_DIGITAL
	switch(_ledTracker)
	{
		case 0:
		default:
		{
			BspGpio::Off(_digitalLeds[RED_LED]);
			BspGpio::Off(_digitalLeds[GREEN_LED]);
			BspGpio::Off(_digitalLeds[BLUE_LED]);
			break;
		}
		case 1:
		{
			BspGpio::On(_digitalLeds[RED_LED]);
			BspGpio::Off(_digitalLeds[GREEN_LED]);
			BspGpio::Off(_digitalLeds[BLUE_LED]);
			break;
		}
		case 2:
		{
			BspGpio::Off(_digitalLeds[RED_LED]);
			BspGpio::On(_digitalLeds[GREEN_LED]);
			BspGpio::Off(_digitalLeds[BLUE_LED]);
			break;
		}
		case 3:
		{
			BspGpio::On(_digitalLeds[RED_LED]);
			BspGpio::On(_digitalLeds[GREEN_LED]);
			BspGpio::Off(_digitalLeds[BLUE_LED]);
			break;
		}
		case 4:
		{
			BspGpio::Off(_digitalLeds[RED_LED]);
			BspGpio::Off(_digitalLeds[GREEN_LED]);
			BspGpio::On(_digitalLeds[BLUE_LED]);
			break;
		}
		case 5:
		{
			BspGpio::On(_digitalLeds[RED_LED]);
			BspGpio::Off(_digitalLeds[GREEN_LED]);
			BspGpio::On(_digitalLeds[BLUE_LED]);
			break;
		}
		case 6:
		{
			BspGpio::Off(_digitalLeds[RED_LED]);
			BspGpio::On(_digitalLeds[GREEN_LED]);
			BspGpio::On(_digitalLeds[BLUE_LED]);
			break;
		}
		case 7:
		{
			BspGpio::On(_digitalLeds[RED_LED]);
			BspGpio::On(_digitalLeds[GREEN_LED]);
			BspGpio::On(_digitalLeds[BLUE_LED]);
			break;
		}
	}
	_ledTracker++;
	_ledTracker &= 7;
#else
	   //NOT0 = 0x00000100;
#endif
	Loading::StopMeasuredSection(1);
}

void Main::CheckToWrite(void)
{
	if(_writeToFlash)
	{
		BspFlash::WriteConfig();
		_writeToFlash = false;
	}
}

void Main::HighPriTimer(void)
{
	Loading::StartMeasuredSection(2);
	BspAnalog::UpdateAnalog();
	BspSerial::PrepareTransmission();
	//BspSerial::EnableInterrupt();
	Loading::StopMeasuredSection(2);
}

void Main::PwmUpdate(void)
{
	Loading::StartMeasuredSection(5);
#ifndef USE_LED_AS_DIGITAL
	_pwm[0] = 0;
	long value = 0;
	//long value = (float)BspPwm::GetFullRangeCount() * MemoryStructure::_memStruct.AnalogInputs.Analog.Data[0] / 3.3f;
	if(value < 0)
	value = 0;
	//_pwm[1] = value;
	//BspPwm::UpdatePwm(1,_pwm);
	//_pwm[0] = 0;
	//value = (float)BspPwm::GetFullRangeCount() * MemoryStructure::_memStruct.AnalogInputs.Analog.Data[1] / 3.3f;
	if(value < 0)
	value = 0;
	//_pwm[1] = value;
#endif
	//BspPwm::UpdatePwm(3,_pwm);
	Loading::StopMeasuredSection(5);
}
