#include "BspTimer.h"

BspTimer::TimerInfo BspTimer::_timerData[20];
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
	SYSCON->CTIMERCLKSELX[0] = 0; // Use Main Clock for Timer
	SYSCON->AHBCLKCTRLX[1] |= (1 << 26); // Enable Clock
	SYSCON->CTIMERCLKSELX[1] = 0; // Use Main Clock for Timer
	SYSCON->AHBCLKCTRLX[1] |= (1 << 27); // Enable Clock
	SYSCON->CTIMERCLKSELX[2] = 0; // Use Main Clock for Timer
	SYSCON->AHBCLKCTRLX[1] |= (1 << 22); // Enable Clock
	SYSCON->CTIMERCLKSELX[3] = 0; // Use Main Clock for Timer
	SYSCON->AHBCLKCTRLX[2] |= (1 << 21); // Enable Clock
	SYSCON->CTIMERCLKSELX[4] = 0; // Use Main Clock for Timer
	SYSCON->AHBCLKCTRLX[2] |= (1 << 22); // Enable Clock
	// Enable the Timers to count, but don't interrupt on any match registers
	CTIMER0->TCR = (1 << 0);
	CTIMER1->TCR = (1 << 0);
	CTIMER2->TCR = (1 << 0);
	CTIMER3->TCR = (1 << 0);
	CTIMER4->TCR = (1 << 0);
	// Enable Interrupts and set priority (nothing will happen until timers are configured)
	NVIC_EnableIRQ(CTIMER0_IRQn);
	NVIC_EnableIRQ(CTIMER1_IRQn);
	NVIC_EnableIRQ(CTIMER2_IRQn);
	NVIC_EnableIRQ(CTIMER3_IRQn);
	NVIC_EnableIRQ(CTIMER4_IRQn);
	NVIC_SetPriority(CTIMER0_IRQn, 11);
	NVIC_SetPriority(CTIMER1_IRQn, 12);
	NVIC_SetPriority(CTIMER2_IRQn, 13);
	NVIC_SetPriority(CTIMER3_IRQn, 14);
	NVIC_SetPriority(CTIMER4_IRQn, 15);
	// Update Initialized Status for other function calls
	_initialized = true;
}

unsigned char BspTimer::SetupTimer(unsigned long period, void (*callback)())
{
	// Make sure that there are timers available
	if(_nextTimer >= sizeof(_timerData) / sizeof(TimerInfo))
		return 0xFF;
	// Store Data
	_timerData[_nextTimer].Period = period;
	_timerData[_nextTimer].Callback = callback;
	unsigned char timer = _nextTimer >> 2;
	CTIMER_Type *tmr;
	switch(timer)
	{
		case 0:
		default:
		{
			tmr = CTIMER0;
			break;
		}
		case 1:
		{
			tmr = CTIMER1;
			break;
		}
		case 2:
		{
			tmr = CTIMER2;
			break;
		}
		case 3:
		{
			tmr = CTIMER3;
			break;
		}
		case 4:
		{
			tmr = CTIMER4;
			break;
		}
	}
	unsigned char match = _nextTimer & 3;
	// Clear Interrupt flag
	tmr->IR = (1 << match);
	// Include in Interrupt
	tmr->MCR |= 1 << (match * 3);
	// Setup next Timeout
	tmr->MR[match] = tmr->TC + period;
	unsigned char tmer = _nextTimer;
	_nextTimer++;
	return tmer;
}

void BspTimer::SetupFreeRunningCounter(void)
{
	//if(!_initialized)
	//	return;
	//Setup Clock for SysTick Timer
	SYSCON->SYSTICKCLKSEL0 = 0; // Select the CPU clock
	SYSCON->SYSTICKCLKDIV0 = 0; // Do not divide the CPU clock
	SysTick->CTRL = 5; // Use Main Clock and Enable
	SysTick->LOAD = 0xFFFFFF; // Reload with maximum
}

void BspTimer::DummyFunction(void)
{
	//__asm("NOP");
}

extern "C"
{
void CTIMER0_IRQHandler(void)
{
	unsigned long mask = 0x1;
	for(unsigned char x = 0; x < 4; x++)
	{
		if(CTIMER0->IR & mask)
		{
			// Call Callback Function
			(*BspTimer::_timerData[(0<<2)+x].Callback)();
			// Update Match Register
			CTIMER0->MR[x] = CTIMER0->TC + BspTimer::_timerData[(0<<2)+x].Period;
		}
		mask <<= 1;
	}
	CTIMER0->IR = 0xF;
}
}
