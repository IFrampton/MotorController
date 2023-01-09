#include "BspWakeupTimer.h"

void (*BspWakeupTimer::_callback)();
bool BspWakeupTimer::_initialized = false;

void BspWakeupTimer::Initialize(void)
{
	// Initialize Structure (to prevent unintended execution)
	 _callback = BspWakeupTimer::DummyFunction;

	// Enable clocks
	SYSCON->SYSAHBCLKCTRL |= (1 << 10); // Enable Clock
	// Clear the Reset input
	SYSCON->PRESETCTRL |= (1 << 7);
	// Put the timers in a known state
	MRT0->CHANNEL[0].CTRL = (0 << 1)	|	// MODE = 0 (Timer operates in Repeat Interrupt Mode)
				   	   	    (0 << 0) ;	// INTEN = 1 (Interrupt is disabled)
	MRT0->CHANNEL[1].CTRL = (0 << 1)	|	// MODE = 0 (Timer operates in Repeat Interrupt Mode)
				   	   	    (0 << 0) ;	// INTEN = 1 (Interrupt is disabled)
	MRT0->CHANNEL[2].CTRL = (0 << 1)	|	// MODE = 0 (Timer operates in Repeat Interrupt Mode)
				   	   	    (0 << 0) ;	// INTEN = 1 (Interrupt is disabled)
	MRT0->CHANNEL[3].CTRL = (0 << 1)	|	// MODE = 0 (Timer operates in Repeat Interrupt Mode)
				   	   	   	(0 << 0) ;	// INTEN = 1 (Interrupt is disabled)
	// Enable Interrupts and set priority (nothing will happen until timers are configured)
	NVIC_EnableIRQ(WKT_IRQn);
	NVIC_SetPriority(WKT_IRQn, 11);
	// Update Initialized Status for other function calls
	_initialized = true;
}

unsigned char BspWakeupTimer::SetupTimer(unsigned long period, void (*callback)())
{
	return 0xFF;
}

void BspWakeupTimer::DummyFunction(void)
{
	//__asm("NOP");
}


extern "C"
{
void WKT_IRQHandler(void)
{
	// This is really only intended to wake the processor, but we can execute logic from here too.
}
}
