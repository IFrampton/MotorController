/*
 * BspPwm.cpp
 *
 *  Created on: Jan 6, 2024
 *      Author: Isaac Frampton
 */

#include "stm32h7xx.h"
#include "BspPwm.h"

void (*BspPwm::_function[2])(void) = {DummyFunction, DummyFunction};
unsigned char BspPwm::_nextPwm = 0;

void BspPwm::Initialize(void)
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

	// This module controls the PWM timers only.
	// Turn on clocks to timers
	// TIM1
	RCC->APB2ENR |= (1 << 0);
	RCC_C2->APB2ENR |= (1 << 0);

	// TIM 2 through TIM5
	RCC->APB1LENR |= (0xF << 0);
	RCC_C2->APB1LENR |= (0xF << 0);

	// Everything else is configured in the setup routine.
}

void BspPwm::SetupFixedPwm(unsigned char timer, unsigned long frequency, unsigned short deadtime)
{
	// Note: this is up/down counting to achieve deadtime.
	unsigned long period = (CpuClockSpeed) / (frequency);
	TIM_TypeDef *tim = TIM2;
	switch(timer)
	{
		case 2:
		default:
		{
			tim = TIM2;
			break;
		}
		case 3:
		{
			tim = TIM3;
			break;
		}
		case 4:
		{
			tim = TIM4;
			break;
		}
		case 5:
		{
			tim = TIM5;
			break;
		}
	}
	// Setup Timer
	tim->CR1 =  (0  << 11)	|	// UIFREMAP = 0; UIF status bit not copied to TIMx_CNT bit 31
				(0  <<  8)	|	// CKD = 0; Clock division is / 1
				(0  <<  7)	|	// ARPE = 0; TIMx_ARR is not buffered
				(1  <<  5)	|	// CMS = 1; Center Alignment mode is set to center alignment, only at 0 rollover
				(0  <<  4)	|	// DIR = 0; Used as an up-counter
				(0  <<  3)	|	// OPM = configured; One Pulse mode is set in function call
				(1  <<  2)	|	// URS = 1; Update request source is only a counter overflow / underflow
				(0  <<  1)	|	// UEV = 0; Update event is enabled
				(0  <<  0)	;	// CEN = 1; Counter enabled
	tim->CR2 = 0;
	tim->SMCR = 0;
	tim->DIER = (0  <<  8)	|	// UDE = 0; Update DMA request disabled
				 (1  <<  0)	;	// UIE = 1; Update interrupt enabled
	tim->CCMR1 = 	(0  << 24)	|	// OC2M[3] = 0; Output Compare 2 Mode Bit 3
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
	tim->CCMR2 = 	(0  << 24)	|	// OC2M[3] = 0; Output Compare 4 Mode Bit 3
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
	tim->CCER = 	(0  << 15)	|	// CC4NP = 0; Unused because channel is configured as an output.
					(0  << 13)	|	// CC4P = 0; Output polarity = Active High
					(0  << 12)	|	// CC4E = 0; Capture Mode disabled
					(0  << 11)	|	// CC3NP = 0; Unused because channel is configured as an output.
					(0  <<  9)	|	// CC3P = 0; Output polarity = Active High
					(0  <<  8)	|	// CC3E = 0; Capture Mode disabled
					(0  <<  7)	|	// CC2NP = 0; Unused because channel is configured as an output.
					(0  <<  5)	|	// CC2P = 0; Output polarity = Active High
					(1  <<  4)	|	// CC2E = 1; Capture Mode enabled
					(0  <<  3)	|	// CC1NP = 0; Unused because channel is configured as an output.
					(0  <<  1)	|	// CC1P = 0; Output polarity = Active High
					(1  <<  0)	;	// CC1E = 1; Capture Mode enabled
	tim->PSC = period >> 16;
	tim->ARR = period & 0xFFFF;

	tim->CCR1 = 	((period & 0xFFFF) >> 1) + (deadtime >> 1);  // Set to 50% duty cycle, add half of deadtime
	tim->CCR2 = 	((period & 0xFFFF) >> 1) - (deadtime >> 1);  // Set to 50% duty cycle, subtract half of deadtime

	tim->CCR3 = 0; // Unused
	tim->CCR4 = 0; // Unused

	//tim->DMAR = 0;	// Unused
	tim->AF1 = 0;	// Unused
	tim->TISEL = 0;	// Unused
	tim->EGR = 	(0  <<  6)	|	// TG = 0; Trigger Generation is false (no trigger is generated by software)
				(0  <<  4)	|	// CC4G = 0; Capture Compare 4 generation is disabled
				(0  <<  3)	|	// CC4G = 0; Capture Compare 3 generation is disabled
				(1  <<  2)	|	// CC4G = 0; Capture Compare 2 generation is enabled
				(1  <<  1)	|	// CC4G = 0; Capture Compare 1 generation is enabled
				(1  <<  0)	;	// CC4G = 0; Update Generation is enabled
	tim->CR1 |= (1 << 0);	// Enable the Timer
}

void BspPwm::SetupSwitchPwm(unsigned long frequency, void (*funct)(void), unsigned char pri)
{
	unsigned long period = (CpuClockSpeed) / (frequency >> 2);
	// Setup Timer
	TIM1->CR1 = (0  << 11)	|	// UIFREMAP = 0; UIF status bit not copied to TIMx_CNT bit 31
				(0  <<  7)	|	// ARPE = 0; TIMx_ARR is not buffered
				(0  <<  3)	|	// OPM = configured; One Pulse mode is set in function call
				(1  <<  2)	|	// URS = 1; Update request source is only a counter overflow / underflow
				(0  <<  1)	|	// UEV = 0; Update event is enabled
				(1  <<  0)	;	// CEN = 1; Counter enabled
	TIM1->CR2 = 0;
	TIM1->DIER = (0  <<  8)	|	// UDE = 0; Update DMA request disabled
				(1  <<  0)	;	// UIE = 1; Update interrupt enabled
	TIM1->PSC = period >> 16;
	TIM1->ARR = period & 0xFFFF;

	// Setup Interrupt
	_function[0] = funct;
	NVIC_SetPriority(TIM1_UP_IRQn, pri);
	NVIC_EnableIRQ(TIM1_UP_IRQn);
}

void BspPwm::DummyFunction(void)
{
}

extern "C"
{
void TIM1_UP_IRQHandler(void)
{
	BspPwm::_function[0]();
	TIM1->SR = 0;
}
}
