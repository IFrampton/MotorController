/*
 * BspTimer.cpp
 *
 *  Created on: Jan 4, 2024
 *      Author: Isaac Frampton
 */

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

char BspTimer::Setup(unsigned long period_in_ns, void (*funct)(void), unsigned char pri, bool oneShot)
{
	unsigned long period = (unsigned long long)period_in_ns * (unsigned long long)TIMER_CLOCK_FREQUENCY / (unsigned long long)1000000000;
	unsigned long minimumPrescaler = period >> 16;
	unsigned long maximumPrescaler = period >> 15;
	unsigned long error = period;
	unsigned long bestPsc = 0;
	unsigned long tempArr = 0;
	for(unsigned long pscTst = minimumPrescaler; pscTst < maximumPrescaler; pscTst++)
	{
		tempArr = period / (pscTst + 1);
		// ARR can't exceed 65535, but the bitshift above won't always give a divider that works
		if(tempArr > 65535)
		{
			tempArr = 65535;
		}
		unsigned long calcPeriod = (pscTst + 1) * tempArr;
		unsigned long tempError = (calcPeriod - period);
		if(tempError < 0)
		{
			tempError = -tempError;
		}
		if(tempError < error)
		{
			error = tempError;
			bestPsc = pscTst;
			// Perfect match
			if(error == 0)
			{
				break;
			}
		}
	}

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
	tim->PSC = bestPsc & 0xFFFF;
	tim->ARR = tempArr & 0xFFFF;

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
	lptim->ARR = requiredPeriod - 1;
	// Start the timer
	// Done elsewhere
	//lptim->CR |= (1 << 2);

	char nxtTmr = _nextLpTimer;
	_nextLpTimer++;
	return nxtTmr;
}

void BspTimer::SetupFreeRunningCounter(void)
{
	// Note: this is up/down counting to achieve deadtime.
	unsigned long period = 0xFFFFFFFF;
	// Setup Timer
	TIM5->CR1 =  (0  << 11)	|	// UIFREMAP = 0; UIF status bit not copied to TIMx_CNT bit 31
				(0  <<  8)	|	// CKD = 0; Clock division is / 1
				(0  <<  7)	|	// ARPE = 0; TIMx_ARR is not buffered
				(0  <<  5)	|	// CMS = 1; Center Alignment mode is set to center alignment, only at 0 rollover
				(0  <<  4)	|	// DIR = 0; Used as an up-counter
				(0  <<  3)	|	// OPM = configured; One Pulse mode is set in function call
				(1  <<  2)	|	// URS = 1; Update request source is only a counter overflow / underflow
				(0  <<  1)	|	// UDIS = 0; Update event (UEV) is enabled
				(0  <<  0)	;	// CEN = 1; Counter enabled
	TIM5->CR2 = 0;
	TIM5->SMCR = 0;
	TIM5->DIER = (0  <<  8)	|	// UDE = 0; Update DMA request disabled
				 (1  <<  0)	;	// UIE = 1; Update interrupt enabled
	TIM5->CCMR1 = 	(0  << 24)	|	// OC2M[3] = 0; Output Compare 2 Mode Bit 3
					(0  << 16)	|	// OC1M[3] = 0; Output Compare 1 Mode Bit 3
					(0  << 15)	|	// OC2CE = 0; Output compare 2 Clear Enable (disabled)
					(6  << 12)	|	// OC2M = 6; Output compare 2 mode = 6 (1 if CNT < CCR2 on upcount, 1 if CNT > CCR2 on downcount)
					(1  << 11)	|	// OC2PE = 1; Output Compare 2 preload Enable (load only on update event)
					(0  << 10)	|	// OC2FE = 0; Output Compare 2 fast enable (behaves normally, regardless of trigger)
					(0  <<  8)	|	// CC2S = 0; Capture Compare 2 selection (CC2 Channel is configured as output)
					(0  <<  7)	|	// OC1CE = 0; Output 1 Clear Enable (disabled)
					(7  <<  4)	|	// OC1M = 7; Output compare 1 mode = 7 (1 if CNT > CCR1 on upcount, 1 if CNT < CCR1 on downcount)
					(1  <<  3)	|	// OC1PE = 1; Output Compare 1 preload Enable (load only on update event)
					(0  <<  2)	|	// OC1FE = 0; Output Compare 1 fast enable (behaves normally, regardless of trigger)
					(0  <<  0)	;	// CC1S = 0; Capture Compare 1 selection (CC1 Channel is configured as output)
	TIM5->CCMR2 = 	(0  << 24)	|	// OC2M[3] = 0; Output Compare 4 Mode Bit 3
					(0  << 16)	|	// OC1M[3] = 0; Output Compare 3 Mode Bit 3
					(0  << 15)	|	// OC2CE = 0; Output compare 4 Clear Enable (disabled)
					(6  << 12)	|	// OC2M = 6; Output compare 4 mode = 6 (1 if CNT < CCR4 on upcount, 1 if CNT > CCR4 on downcount)
					(1  << 11)	|	// OC2PE = 1; Output Compare 4 preload Enable (load only on update event)
					(0  << 10)	|	// OC2FE = 0; Output Compare 4 fast enable (behaves normally, regardless of trigger)
					(0  <<  8)	|	// CC2S = 0; Capture Compare 4 selection (CC4 Channel is configured as output)
					(0  <<  7)	|	// OC1CE = 0; Output 3 Clear Enable (disabled)
					(7  <<  4)	|	// OC1M = 7; Output compare 3 mode = 7 (1 if CNT > CCR3 on upcount, 1 if CNT < CCR3 on downcount)
					(1  <<  3)	|	// OC1PE = 1; Output Compare 3 preload Enable (load only on update event)
					(0  <<  2)	|	// OC1FE = 0; Output Compare 3 fast enable (behaves normally, regardless of trigger)
					(0  <<  0)	;	// CC1S = 0; Capture Compare 3 selection (CC3 Channel is configured as output)
	TIM5->CCER = 	(0  << 15)	|	// CC4NP = 0; Unused because channel is configured as an output.
					(0  << 13)	|	// CC4P = 0; Output polarity = Active High
					(0  << 12)	|	// CC4E = 0; Capture Mode disabled
					(0  << 11)	|	// CC3NP = 0; Unused because channel is configured as an output.
					(0  <<  9)	|	// CC3P = 0; Output polarity = Active High
					(0  <<  8)	|	// CC3E = 0; Capture Mode disabled
					(0  <<  7)	|	// CC2NP = 0; Unused because channel is configured as an output.
					(0  <<  5)	|	// CC2P = 0; Output polarity = Active High
					(0  <<  4)	|	// CC2E = 1; Capture Mode enabled
					(0  <<  3)	|	// CC1NP = 0; Unused because channel is configured as an output.
					(0  <<  1)	|	// CC1P = 0; Output polarity = Active High
					(0  <<  0)	;	// CC1E = 1; Capture Mode enabled
	TIM5->PSC = 0;
	TIM5->ARR = period;

	TIM5->CCR1 = period >> 1;  // Set to 50% duty cycle, add half of deadtime
	TIM5->CCR2 = period >> 1;  // Set to 50% duty cycle, subtract half of deadtime

	TIM5->CCR3 = 0; // Unused
	TIM5->CCR4 = 0; // Unused

	//TIM5->DMAR = 0;	// Unused
	TIM5->AF1 = 0;	// Unused
	TIM5->TISEL = 0;	// Unused
	TIM5->EGR = 	(0  <<  6)	|	// TG = 0; Trigger Generation is false (no trigger is generated by software)
				(0  <<  4)	|	// CC4G = 0; Capture Compare 4 generation is disabled
				(0  <<  3)	|	// CC4G = 0; Capture Compare 3 generation is disabled
				(0  <<  2)	|	// CC4G = 0; Capture Compare 2 generation is enabled
				(0  <<  1)	|	// CC4G = 0; Capture Compare 1 generation is enabled
				(0  <<  0)	;	// CC4G = 0; Update Generation is enabled
	TIM5->CR1 |= (1 << 0);	// Enable the Timer
}

void BspTimer::DummyFunction(void)
{
}

extern "C"
{
void TIM6_DAC_IRQHandler(void)
{
	BspTimer::_function[0]();
	TIM6->SR = 0;
}
void TIM7_IRQHandler(void)
{
	BspTimer::_function[1]();
	TIM7->SR = 0;
}
}
