#include "LPC5502.h"
#include "Main.h"
#include "BspTimer.h"
#include "SlowTimer.h"
#include "BspPwm.h"
#include "BspGpio.h"
#include "BspFlash.h"
#include "Protection.h"
#include "MemoryStructure.h"
#include "Loading.h"

unsigned char Main::_digitalLeds[TOTAL_OUTPUTS];
long Main::_counterValueOnLastUpdate = 0;
unsigned long Main::_idleTaskCounter = 0;
long Main::_updatePeriod = 1200;
unsigned long Main::_periodCounter = 0;
unsigned long Main::_timePeriod = 0;

unsigned char Main::_ledTracker = 0;
bool Main::_writeToFlash = false;


extern "C"
{
int main()
{
	SystemCoreClockUpdate();
	Main::InitialBootup();
	return 0;
}
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
	BspPwm::Initialize();
	Loading::Initialize();
	SlowTimer::Initialize();
	BspGpio::Initialize();
	Protection::Initialize();
	// Setup GPIO
	_digitalLeds[GREEN_LED] = BspGpio::SetupDigitalOutput(0, 18);
	_digitalLeds[RED_LED] =   BspGpio::SetupDigitalOutput(0, 21);
	_digitalLeds[BLUE_LED] =  BspGpio::SetupDigitalOutput(0, 22);
	// Setup Analog
	BspGpio::SetupGeneric(0, 23, 0, false, false, true); 	// ADC0_0
	BspGpio::SetupGeneric(0, 10, 0, false, false, true); 	// ADC0_1
	BspGpio::SetupGeneric(0, 15, 0, false, false, true); 	// ADC0_2
	BspGpio::SetupGeneric(0, 31, 0, false, false, true); 	// ADC0_3
	BspGpio::SetupGeneric(1, 8, 0, false, false, true); 	// ADC0_4
	BspGpio::SetupGeneric(0, 16, 0, false, false, true);	// ADC0_8
//	BspGpio::SetupGeneric(0, 11, 0, false, false, true);	// ADC0_9
//	BspGpio::SetupGeneric(0, 12, 0, false, false, true);	// ADC0_10
	BspGpio::SetupGeneric(1, 0, 0, false, false, true);		// ADC0_11
	BspGpio::SetupGeneric(1, 9, 0, false, false, true);		// ADC0_12

	// Setup Low Priority Tasks
	SlowTimer::SetupTimer(1000, ToggleLed);
	SlowTimer::SetupTimer(1000, CheckToWrite);

	// Setup Timer (Temporary - for testing)
	BspTimer::SetupTimer(960000, HighPriTimer);

	// When finished initializing, call idle task (with Slow Timer operating at 100Hz)
	IdleTask(1000);
}

void Main::IdleTask(unsigned long slowTimerFrequency)
{
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
	}
}

void Main::ToggleLed(void)
{
	Loading::StartMeasuredSection(1);
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
	for(unsigned long x = 0; x < 30; x++)
	{
		__asm("NOP");
	}
	Loading::StopMeasuredSection(2);
}

