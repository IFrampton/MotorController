#include "BspTimer.h"

BspTimer::TimerInfo BspTimer::_timerData[4];
unsigned char BspTimer::_nextTimer;
bool BspTimer::_initialized = false;

void BspTimer::Initialize(void)
{
	// Initialize Structure (to prevent unintended execution)
	for(unsigned char x = 0; x < sizeof(_timerData) / sizeof(TimerInfo); x++)
	{
		_timerData[x].Period = 0;
		_timerData[x].Callback = DummyFunction;
	}
	// Enable clocks
	SYSCON->SYSAHBCLKCTRL |= (1 << 10); // Enable Clock
	// Clear the Reset input
	SYSCON->PRESETCTRL |= (1 << 7);
	// Put the timers in a known state (first 3 are repeat interrupt, last is one shot)
	MRT0->CHANNEL[0].CTRL = (0 << 1)	|	// MODE = 0 (Timer operates in Repeat Interrupt Mode)
				   	   	    (0 << 0) ;	// INTEN = 1 (Interrupt is disabled)
	MRT0->CHANNEL[1].CTRL = (0 << 1)	|	// MODE = 0 (Timer operates in Repeat Interrupt Mode)
				   	   	    (0 << 0) ;	// INTEN = 1 (Interrupt is disabled)
	MRT0->CHANNEL[2].CTRL = (0 << 1)	|	// MODE = 0 (Timer operates in Repeat Interrupt Mode)
				   	   	    (0 << 0) ;	// INTEN = 1 (Interrupt is disabled)
	MRT0->CHANNEL[3].CTRL = (1 << 1)	|	// MODE = 0 (Timer operates in one shot Mode)
				   	   	   	(1 << 0) ;	// INTEN = 1 (Interrupt is disabled)
	// Enable Interrupts and set priority (nothing will happen until timers are configured)
	NVIC_EnableIRQ(MRT0_IRQn);
	NVIC_SetPriority(MRT0_IRQn, 11);
	// Update Initialized Status for other function calls
	_initialized = true;
}

unsigned char BspTimer::SetupTimer(unsigned long period, void (*callback)())
{
	// Make sure that there are timers available
	// Note: The last one is now dedicated purpose
	if(_nextTimer >= sizeof(_timerData) / sizeof(TimerInfo) - 1)
		return 0xFF;
	// Store Data
	_timerData[_nextTimer].Period = period;
	_timerData[_nextTimer].Callback = callback;
	MRT_Type *tmr = MRT0;
	unsigned char timer = _nextTimer & 3;
	// Clear Interrupt flag
	tmr->CHANNEL[timer].STAT = (1 << 0);
	// Include in Interrupt
	tmr->CHANNEL[timer].CTRL = (0 << 1)	|	// MODE = 0 (Timer operates in Repeat Interrupt Mode)
				   (1 << 0) ;	// INTEN = 1 (Interrupt is disabled)
	// Setup next Timeout (load immediately)
	tmr->CHANNEL[timer].INTVAL = ((unsigned int)1 << 31) |
					 	 	 	 (period << 0);
	unsigned char tmer = _nextTimer;
	_nextTimer++;
	return tmer;
}

unsigned char BspTimer::SetupDmaResetTimer(BspDma::DmaChannelData *data, unsigned long *timeout, void (*callback)())
{
	*timeout = *timeout | ((unsigned long)1 << 31);
	BspDma::LinkAdditionalTransferToPeripheral(data, 0, 3, (unsigned char *)timeout, (unsigned char *)&MRT0->CHANNEL[3].INTVAL, 4, 1, 0);
	_timerData[_nextTimer].Period = *timeout;
	_timerData[_nextTimer].Callback = callback;
	return 3;
}

void BspTimer::SetupFreeRunningCounter(void)
{
	//if(!_initialized)
	//	return;
	//Setup Clock for SysTick Timer
	SysTick->CTRL = 5; // Use Main Clock and Enable
	SysTick->LOAD = 0xFFFFFF; // Reload with maximum
}

void BspTimer::DummyFunction(void)
{
	//__asm("NOP");
}

extern "C"
{
void MRT0_IRQHandler(void)
{
	for(unsigned char timer = 0; timer < 4; timer++)
	{
		if(MRT0->CHANNEL[timer].STAT & 0x1)
		{
			// Call Callback Function
			(*BspTimer::_timerData[timer].Callback)();
			// Clear Interrupt flag
			MRT0->CHANNEL[timer].STAT = (1 << 0);
		}
	}
}
}
