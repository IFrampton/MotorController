#include "main.h"
#include "SineTable.h"
#include "BspTimer.h"
#include "BspIo.h"
#include "BspDma.h"
#include "BspPwm.h"
#include "BspCan.h"
#include "BspClock.h"
#include "BspSpi.h"
#include "Motor.h"
#include "DataMan.h"
#include "SlowTimer.h"
#include "Loading.h"

//#define SEND_GIBBERISH
#define EXPECT_REAL_DATA

unsigned long _dummyVariable[4] = {0, 0, 0, 0};
unsigned long _gibberish[16] =
{
		0xDEADBEEF, 0xDEADBEEF, 0xC8, 0xDEADBEEF,
		0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF,
		0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF,
		0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF
};
unsigned long *_canLoc = _dummyVariable;
char _hndl = -2;
unsigned long _identifier = 0;
char _length = 0;
unsigned long _data[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned long _txData[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char _canMessage = 0;
bool _extended = false;
bool _error = false;
unsigned short _timeStamp = 0;
bool _toggle = false;
unsigned short _currents[3][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
unsigned char _currentLoc[3] = {0, 0, 0};
unsigned long _updatePeriod = 100000;
bool _tggle = false;

char _txHnd = -2;


int main(void)
{
	//unsigned long long counts = 0;
	// Setup the clocks
	BspClock::Initialize(8000000, 240000000);

	// Setup the timers
	BspTimer::Initialize();

	// Setup the I/O
	BspIo::Initialize();

	// Power on the DMA
	BspDma::Initialize();

	// Initial PWM setup
	BspPwm::Initialize();

#if 1

	// Setup the fixed PWM
	BspPwm::SetupFixedPwm(2, 2000000, 20);
	BspPwm::SetupFixedPwm(3, 2000000, 20);
	BspPwm::SetupFixedPwm(4, 2000000, 20);
#ifndef USE_TIM2_TWICE
	BspPwm::SetupFixedPwm(5, 2000000, 20);
#endif

	// Setup Analog Inputs and Outputs
	BspAnalog::InitializeAdc();
	BspAnalog::InitializeExternal();

	BspAnalog::InitializeDac();
	// LP Timer Triggers DAC
	// To create 10kHz, we need a counter at 16us (64 points in sine wave).
#ifdef STEP_SINE
	BspTimer::SetupLpTimer(1562);
#else
	BspTimer::SetupLpTimer(390);
#endif

	// Setup the switch PWM
	//BspPwm::SetupSwitchPwm(10000, 300, Main::PwmFunct, 6);
#endif
	DataMan::Initialize();
#if 1
	BspCan::Initialize();

	MotorControl::Initialize();

	//BspCan::SetupDevice(500000, 0);
	_hndl = BspCan::Subscribe(0x101, &_canLoc, false);
	_txHnd = BspCan::GetTxHandle();

	SysTick->CTRL = 5;//1;// bit 2 uses CPU clock vs. CPU / 8
	SysTick->LOAD = 0xFFFFFF;

#endif
	SlowTimer::Initialize();
	SlowTimer::Setup(1, Main::PwmFunct);


#ifdef USE_TIM2_TWICE
	BspTimer::SetupFreeRunningCounter();
	ProcLoading::Initialize();
#endif

#ifdef USE_TIM2_TWICE
	unsigned long oldSysTick = BspTimer::GetFreeRunningCounter();
#else
	unsigned long oldSysTick = (SysTick->VAL << 8);
#endif
	unsigned long timerElapsedTime = 0;
	unsigned long loadingElapsedTime = 0;
	unsigned long loadingIdleCounter = 0;
	while (1)
	{
		loadingIdleCounter++;
#ifdef USE_TIM2_TWICE
		register unsigned long sysTick = BspTimer::GetFreeRunningCounter();
		unsigned long intervalTime = sysTick - oldSysTick;
		oldSysTick = sysTick;
#else
		register unsigned long sysTick = (SysTick->VAL << 8);
		unsigned long intervalTime = ((oldSysTick - sysTick) >> 8);
		oldSysTick = sysTick;
#endif
		// Handle the slow timer (which is run from the idle task)
		timerElapsedTime += intervalTime;
		if(timerElapsedTime > (unsigned long)(SLOW_TIMER_UPDATE_RATE * (float)TIMER_CLOCK_FREQUENCY))
		{
			timerElapsedTime -= (unsigned long)(SLOW_TIMER_UPDATE_RATE * (float)TIMER_CLOCK_FREQUENCY);
			SlowTimer::Update();
		}
		// Handle processor loading calculations
		loadingElapsedTime += intervalTime;
		if(loadingElapsedTime > TIMER_CLOCK_FREQUENCY)
		{
			loadingElapsedTime -= TIMER_CLOCK_FREQUENCY;
			ProcLoading::UpdateEverySecond(loadingIdleCounter);
			loadingIdleCounter = 0;
		}
	}
}

void Main::PwmFunct(void)
{
	ProcLoading::BeginTask(ProcLoading::Spare_Task);
	if(_toggle)
	{
		BspIo::SetIoPin(&BspIo::_pinInfo[BspIo::LED_RED]);
		BspIo::SetIoPin(&BspIo::_pinInfo[BspIo::LED_YELLOW]);
		BspIo::SetIoPin(&BspIo::_pinInfo[BspIo::LED_GREEN]);
		_toggle = false;
	}
	else
	{
		BspIo::ClearIoPin(&BspIo::_pinInfo[BspIo::LED_RED]);
		BspIo::ClearIoPin(&BspIo::_pinInfo[BspIo::LED_YELLOW]);
		BspIo::ClearIoPin(&BspIo::_pinInfo[BspIo::LED_GREEN]);
		_toggle = true;
	}
	if(BspCan::CheckForNewData(_hndl))
	{
		BspCan::GetData(_hndl, &_identifier, &_length, _data, &_extended, &_error, &_timeStamp);
		if(((_identifier >> 18) == 0x101) && (_extended == false) && (_length == 8))
		{
			unsigned short data = _data[0] & 0xFFFF;
			if(data < 0xFFFF)
			{
				DataMan::_config.Analog.Motor.FrequencyTarget = (float)data * 0.1f;
			}
			data = _data[0] >> 16;
			if(data < 0xFFFF)
			{
				DataMan::_config.Analog.Motor.FrequencyRampRate = (float)data * 0.01f;
			}
			data = _data[1] & 0xFFFF;
			if(data < 0xFFFF)
			{
				DataMan::_config.Analog.Motor.MotorVoltsPerHz = (float)data * 0.001f;
			}
			data = _data[1] >> 16;
			if(data < 0xFFFF)
			{
				DataMan::_config.Analog.Motor.Offset = (float)data * 0.0001f;
			}
		}
		//else if()
		//{
			// Only one packet at this time
		//}
	}
	switch(_canMessage)
	{
		// Motor Voltages
		case 0:
		{
			unsigned short data = (unsigned short)(DataMan::_variables.AnalogIn.Motor.BusVoltage * 50.0f);
			_txData[1] = data;
			data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.Voltage[0] * 25.0f + 32767.0f);
			_txData[1] <<= 16;
			_txData[1] += data;
			data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.Voltage[1] * 25.0f + 32767.0f);
			_txData[0] = data;
			data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.Voltage[2] * 25.0f + 32767.0f);
			_txData[0] <<= 16;
			_txData[0] += data;
			BspCan::Transmit(_txHnd, 0x200, &_txData[0], 8, false);
			_canMessage++;
			break;
		}
		// Motor Currents
		case 1:
		{
			unsigned short data = 0xFFFF;
			_txData[1] = data;
#ifdef EXPECT_REAL_DATA
			data = (unsigned short)(DataMan::_variables.AnalogIn.Motor.Current[0] * 50.0f + 32767.0f);
			_txData[1] <<= 16;
			_txData[1] += data;
			data = (unsigned short)(DataMan::_variables.AnalogIn.Motor.Current[1] * 50.0f + 32767.0f);
			_txData[0] = data;
			data = (unsigned short)(DataMan::_variables.AnalogIn.Motor.Current[2] * 50.0f + 32767.0f);
			_txData[0] <<= 16;
			_txData[0] += data;
#else
			data = (unsigned short)(DataMan::_variables.AnalogIn.Motor.Current[0] * 1.0f + 0.0f);
			_txData[1] <<= 16;
			_txData[1] += data;
			data = (unsigned short)(DataMan::_variables.AnalogIn.Motor.Current[1] * 1.0f + 0.0f);
			_txData[0] += data;
			data = (unsigned short)(DataMan::_variables.AnalogIn.Motor.Current[2] * 1.0f + 0.0f);
			_txData[0] <<= 16;
			_txData[0] += data;
#endif
			BspCan::Transmit(_txHnd, 0x201, &_txData[0], 8, false);
			_canMessage++;
			break;
		}
		// Other Information
		case 2:
		default:
		{
			unsigned short data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.Amplitude * 10000.0f + 32767.0f);
			_txData[1] = data;
			data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.Frequency * 10.0f);
			_txData[1] <<= 16;
			_txData[1] += data;
			data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.RealCurrent * 50.0f + 32767.0f);
			_txData[0] = data;
			data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.ReactiveCurrent * 50.0f + 32767.0f);
			_txData[0] <<= 16;
			_txData[0] += data;
			BspCan::Transmit(_txHnd, 0x202, &_txData[0], 8, false);
			_canMessage = 0;
			break;
		}
	}
	ProcLoading::EndTask(ProcLoading::Spare_Task);
}

extern "C"
{
void HardFault_Handler(void)
{
	while(1)
	{
	}
}
void MemManage_Handler(void)
{
	while(1)
	{
	}
}
void  BusFault_Handler(void)
{
	while(1)
	{
	}
}

void  UsageFault_Handler(void)
{
	while(1)
	{
	}
}
}
