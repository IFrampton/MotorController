/*
 * BspTimer.cpp
 *
 *  Created on: Jan 4, 2024
 *      Author: Isaac Frampton
 */

#include "stm32h7xx.h"
#include "BspTimer.h"

void (*BspTimer::_function[2])(void) = {DummyFunction, DummyFunction};
unsigned char BspTimer::_nextTimer = 0;
unsigned char BspTimer::_nextLpTimer = 0;

void BspTimer::Initialize(void)
{
	// Note: The following Timers are used by Core 1:
	// The following timers are available to Core 2
	// TIM1 (used for Switch Control PWM)
	// TIM2 (used for Input power control)
	// TIM3 (used for CAN power control)
	// TIM4 (used for Metering power control)
	// TIM5 (used for Switch power supply control)
	// TIM6 (used as a general purpose timer)
	// TIM7 (used as a general purpose timer)

	// This module controls the general purpose timers only.
	// Turn on clocks to timers
	RCC->APB1LENR |= (3 << 4);
	RCC_C2->APB1LENR |= (3 << 4);

	// The Low power timers are also referenced here
	// LPTIM1
	// Use pll2_p_ck (100MHz)
	RCC->D2CCIP2R &= ~(7 << 28);
	RCC->D2CCIP2R |= (1 << 28);
	// Remove Reset
	RCC->APB1LRSTR &= ~(1 << 9);
	// Enable Clock
	RCC->APB1LENR |= (1 << 9);
	RCC_C2->APB1LENR |= (1 << 9);
	// Disable in Sleep Mode
	RCC->APB1LLPENR &= ~(1 << 9);

	// LPTIM2
	// Use pll2_p_ck (100MHz)
	RCC->D3CCIPR &= ~(7 << 10);
	RCC->D3CCIPR |= (1 << 10);
	// Remove Reset
	RCC->APB4RSTR &= ~(1 << 9);
	// Disable in autonomous mode
	RCC->D3AMR &= ~(1 << 9);
	// Enable Clock
	RCC->APB4ENR |= (1 << 9);
	RCC_C2->APB4ENR |= (1 << 9);
	// Disable in Sleep Mode
	RCC->APB4LPENR &= ~(1 << 9);

	// LPTIM345
	// Use pll2_p_ck (100MHz)
	RCC->D3CCIPR &= ~(7 << 13);
	RCC->D3CCIPR |= (1 << 13);
	// Remove Reset
	RCC->APB4RSTR &= ~(7 << 10);
	// Disable in autonomous mode
	RCC->D3AMR &= ~(7 << 10);
	// Enable Clock
	RCC->APB4ENR |= (7 << 10);
	RCC_C2->APB4ENR |= (7 << 10);
	// Disable in Sleep Mode
	RCC->APB4LPENR &= ~(7 << 10);

	// Everything else is configured in the setup routine.
}

char BspTimer::Setup(long clockCycles, void (*funct)(void), unsigned char pri, bool oneShot)
{
	if(_nextTimer >= SUPPORTED_TIMERS)
	{
		return -1;
	}
	TIM_TypeDef *tim = TIM6;
	switch(_nextTimer)
	{
		case 0:
		{
			tim = TIM6;
			break;
		}
		case 1:
		{
			tim = TIM7;
			break;
		}
	}
	// Setup Timer
	tim->CR1 = 	(0  << 11)	|	// UIFREMAP = 0; UIF status bit not copied to TIMx_CNT bit 31
				(0  <<  7)	|	// ARPE = 0; TIMx_ARR is not buffered
			(oneShot<<  3)	|	// OPM = configured; One Pulse mode is set in function call
				(1  <<  2)	|	// URS = 1; Update request source is only a counter overflow / underflow
				(0  <<  1)	|	// UDIS = 0; Update event (UEV) is enabled
				(1  <<  0)	;	// CEN = 1; Counter enabled
	tim->CR2 = 0;
	tim->DIER = (0  <<  8)	|	// UDE = 0; Update DMA request disabled
				(1  <<  0)	;	// UIE = 1; Update interrupt enabled
	tim->PSC = clockCycles >> 16;
	tim->ARR = clockCycles & 0xFFFF;

	// Setup Interrupt
	_function[_nextTimer] = funct;
	NVIC_SetPriority((IRQn_Type)((long)TIM6_DAC_IRQn + (long)_nextTimer), pri);
	NVIC_EnableIRQ((IRQn_Type)((long)TIM6_DAC_IRQn + (long)_nextTimer));
	char nxtTmr = _nextTimer;
	_nextTimer++;
	return nxtTmr;
}

char BspTimer::SetupLpTimer(unsigned long period_in_ns)
{
	if(_nextLpTimer >= SUPPORTED_LP_TIMERS)
	{
		return -1;
	}
	LPTIM_TypeDef *lptim = LPTIM1;
	switch(_nextLpTimer)
	{
		case 0:
		{
			lptim = LPTIM1;
			break;
		}
		case 1:
		{
			lptim = LPTIM2;
			break;
		}
		case 2:
		{
			lptim = LPTIM3;
			break;
		}
		case 3:
		{
			lptim = LPTIM4;
			break;
		}
		case 4:
		{
			lptim = LPTIM5;
			break;
		}
	}
	long requiredPeriod = period_in_ns / 10;
	unsigned char shiftCount = 0;
	while(requiredPeriod > 65535)
	{
		shiftCount++;
		requiredPeriod >>= 1;
	}
	if(shiftCount >= 8)
	{
		return -2;
	}
	lptim->CFGR =   (0  << 24)	|	// ENC = 0; Encoder mode enable (0 = disabled)
					(0  << 23)	|	// COUNTMODE = 0; Counter mode enabled (0 = the counter is incremented from the internal clock)
					(1  << 22)	|	// PRELOAD = 1; Registers update mode (1 = registers are updated on timeout)
					(0  << 21)	|	// WAVPOL = 0; Waveform shape polarity (0 = compare of LPTIM_CNT and LPTIM_CMP) (unused)
					(0  << 20)	|	// WAVE = 0; Waveform shape (0 = deactive set once mode)
					(0  << 19)	|	// TIMEOUT = 0; Timeout enable (0 = a trigger arriving while the timer is active will be ignored)
					(0  << 17)	|	// TRIGEN = 0; Trigger enable and polarity (0 = software trigger)
					(0  << 13)	|	// TRIGSEL = 0; Trigger selector (0 = lptim_ext_trig0) (unused)
			(shiftCount <<  9)	|	// PRESC = variable; Clock Prescaler (0 = /1, 1 = /2, 2 = /4 ...)
					(0  <<  6)	|	// TRGFLT = 0; Configurable digital filter for trigger (0 = any trigger active level change is considered a valid trigger) (unused)
					(0  <<  3)	|	// TCKFLT = 0; Configurable digital filter for external clock (0 = any clock signal level change is considered a valid transition) (unused)
					(0  <<  1)	|	// CKPOL = 0; Clock polarity (0 = the rising edge is the active edge for counting)
					(0  <<  0)	;	// CKSEL = 0; Clock Selector (0 = LPTIM is clocked by the internal clock source)
	lptim->CFGR2 =  (0  <<  4)	|	// IN2SEL = 0; LPTIM input 2 selection (0 = lptim_in2_mux0)
					(0  <<  0)	;	// IN1SEL = 0; LPTIM input 1 selection (0 = lptim_in1_mux0)
	lptim->CR = (0  <<  4)	|	// RSTARE = 0; Reset after read enable (0 = disabled, 1 = reset count if read)
				(0  <<  3)	|	// COUNTRST = 0; Counter Reset (0 = don't reset counter)
				(0  <<  2)	|	// CNTSTART = 0; LPTIM start in Continuous mode (0 = don't start yet)
				(0  <<  1)	|	// SNGSTART = 0; LPTIM start in Continuous mode (0 = don't start)
				(1  <<  0)	;	// ENABLE = 1; LPTIM enable (1 = enable)
	lptim->CMP = requiredPeriod >> 1;
	lptim->ARR = requiredPeriod;
	// Start the timer
	lptim->CR |= (1 << 2);

	char nxtTmr = _nextLpTimer;
	_nextLpTimer++;
	return nxtTmr;
}

void BspTimer::DummyFunction(void)
{
}

extern "C"
{
void TIM6_DAC_IRQHandler(void)
{
	BspTimer::_function[0]();
	TIM7->SR = 1;
}
void TIM7_IRQHandler(void)
{
	BspTimer::_function[1]();
	TIM7->SR = 1;
}
}
