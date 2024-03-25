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
