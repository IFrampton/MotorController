#include "main.h"
#include "SineTable.h"
#include "BspClock.h"
#include "BspFlash.h"
#include "BspTimer.h"
#include "BspIo.h"
#include "BspDma.h"
#include "BspPwm.h"
#include "BspCan.h"
#include "BspSpi.h"
#include "Motor.h"
#include "DataMan.h"
//#include "Fccp.h"
#include "SlowTimer.h"
#include "Loading.h"
extern "C"
{
#include "P2319ASW01.h"
}
#include "xcp_par.h"

int _tempVar = 0;

int main(void)
{
	_tempVar = sizeof(unsigned long);
	//unsigned long long counts = 0;
	// Setup the clocks
	BspClock::Initialize(8000000, 240000000);

	// Read Data from NVM
	BspFlash::Initialize();

	// Setup the timers
	BspTimer::Initialize();

	// Setup the I/O
	BspIo::Initialize();

	// Power on the DMA
	BspDma::Initialize();

	// Setup Analog Inputs and Outputs
	BspAnalog::InitializeAdc();
	BspAnalog::InitializeExternal();

	// Load valid Values
	BspAnalog::StartConversion();

	// Initial PWM setup
	BspPwm::Initialize();

#if 1

	// Setup the fixed PWM
	BspPwm::SetupFixedPwm(2, 2000000, 5);
	BspPwm::SetupFixedPwm(3, 2000000, 20);
	BspPwm::SetupFixedPwm(4, 2000000, 20);
#ifndef USE_TIM2_TWICE
	BspPwm::SetupFixedPwm(5, 2000000, 20);
#endif

	BspAnalog::InitializeDac();
	// LP Timer Triggers DAC
	// To create 10kHz, we need a counter at 16us (64 points in sine wave).
#ifdef STEP_SINE
	BspTimer::SetupLpTimer(1562);
#else
#ifdef SYNC_SINE_WITH_PWM
	BspTimer::SetupLpTimer(500);
#else
	BspTimer::SetupLpTimer(390);
#endif
#endif

	// Setup the switch PWM
	//BspPwm::SetupSwitchPwm(10000, 300, Main::PwmFunct, 6);
	// Invoked in Data man below, so required.
	BspCan::Initialize();
	//BspCan::SetupDevice(500000, 0);

#endif
	DataMan::Initialize();
#if 1

	MotorControl::Initialize();


	SysTick->CTRL = 5;//1;// bit 2 uses CPU clock vs. CPU / 8
	SysTick->LOAD = 0xFFFFFF;

#endif
	// Initialize the low priority timer
	SlowTimer::Initialize();

	// Initialize Model
	P2319ASW01_initialize();

	//Initialize XCP
	InitializeXcp();

	// Setup 10ms and 100ms tick for model
	BspTimer::Setup(10000000, Main::Tick_10ms, 12, false);
	SlowTimer::Setup(0.1F, Main::Tick_100ms);
	SlowTimer::Setup(1.0F, Main::Tick_1s);
	SlowTimer::Setup(10.0F, Main::Tick_10s);
	VectorControl::UpdateConfig();


	// Dummy Function
	SlowTimer::Setup(1.0F, Main::PwmFunct);


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

bool _toggle = false;

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
	ProcLoading::EndTask(ProcLoading::Spare_Task);
}

void Main::Tick_10ms(void)
{
	P2319ASW01_step1();
	Xcp_10ms_Tick();
}

void Main::Tick_100ms(void)
{
	P2319ASW01_step2();
}

void Main::Tick_1s(void)
{
	// Nothing to do here.
}

void Main::Tick_10s(void)
{
	VectorControl::UpdateConfig();
}

extern "C"
{
void HardFault_Handler(void)
{
	BspPwm::DisablePWM();
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
