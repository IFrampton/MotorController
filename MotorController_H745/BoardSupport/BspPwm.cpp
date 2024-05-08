/*
 * BspPwm.cpp
 *
 *  Created on: Jan 6, 2024
 *      Author: Isaac Frampton
 */

#include "stm32h7xx.h"
#include "BspClock.h"
#include "BspPwm.h"

void (*BspPwm::_function[2])(void) = {DummyFunction, DummyFunction};
unsigned char BspPwm::_nextPwm = 0;
unsigned short BspPwm::_period = 0;


void BspPwm::Initialize(void)
{
	// Note: The following Timers are used by Core 1:
	// The following timers are available to Core 2
	// TIM1 (used for Switch Control PWM)
	// TIM2 (used for Input power control)
	// TIM3 (used for CAN power control)
	// TIM4 (used for Metering power control)
	// TIM5 (used for Switch power supply control or a 32-bit free-running counter)
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
	unsigned long period = (CpuClockFrequency) / (frequency);
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
				(0  <<  1)	|	// UDIS = 0; Update event (UEV) is enabled
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

void BspPwm::SetupSwitchPwm(unsigned long frequency, unsigned short deadtime, void (*funct)(void), unsigned char pri)
{
	unsigned long period = (CpuClockFrequency) / (frequency >> 1);
	// Setup Timer
	TIM1->CR1 = (0  << 11)	|	// UIFREMAP = 0; UIF status bit not copied to TIMx_CNT bit 31
				(0  <<  8)	|	// CKD = 0; Clock Division is not enabled (t_DTS = t_ck_int)
				(0  <<  7)	|	// ARPE = 0; TIMx_ARR is not buffered
				(0  <<  5)	|	// CMS = 0; Center-aligned mode selection is set to 0 (Edge Aligned PWM)
				(0  <<  4)	|	// DIR = 0; Direction (Counter used as an up-counter)
				(0  <<  3)	|	// OPM = 0; One Pulse mode is false (operates continuously)
				(1  <<  2)	|	// URS = 1; Update request source is only a counter overflow / underflow
				(0  <<  1)	|	// UDIS = 0; Update event is enabled
				(1  <<  0)	;	// CEN = 1; Counter enabled
	TIM1->CR2 = (0  << 20)	|	// MMS2 = 0; Master Mode Selection 2 (0 = Reset)
				(0  << 18)	|	// OIS6 = 0; Output Idle State for OC6 output is 0 (logic low)
				(0  << 16)	|	// OIS5 = 0; Output Idle State for OC5 output is 0 (logic low)
				(0  << 14)	|	// OIS4 = 0; Output Idle State for OC4 output is 0 (logic low)
				(0  << 13)	|	// OIS3N = 0; Output Idle State for OC3N output is 0 (logic low)
				(0  << 12)	|	// OIS3 = 0; Output Idle State for OC3 output is 0 (logic low)
				(0  << 11)	|	// OIS2N = 0; Output Idle State for OC2N output is 0 (logic low)
				(0  << 10)	|	// OIS2 = 0; Output Idle State for OC2 output is 0 (logic low)
				(0  <<  9)	|	// OIS1N = 0; Output Idle State for OC1N output is 0 (logic low)
				(0  <<  8)	|	// OIS1 = 0; Output Idle State for OC1 output is 0 (logic low)
				(0  <<  7)	|	// TI1 = 0; The TIM1_CH1 pin is connected to TI1 input
				(2  <<  4)	|	// MMS = 2; Master Mode Selection (0 = Reset, 2 = reload event makes trigger)
				(0  <<  3)	|	// CCDS = 0; Capture/Compare DMA Selection (DMA request sent when CCx event occurs)
				(0  <<  2)	|	// CCUS = 0; Capture/Compare Control Update Selection (0 = When bits are loaded, they are updated by setting the COMG bit only)
				(0  <<  0)	;	// CCPC = 0; Capture/Compare Preloaded Control (CCxE, CCxNE, and OCxM bits are not preloaded)
	TIM1->SMCR = (0 << 20)	|	// TS[4:3] = 0; ***SEE BELOW***
				(0  << 16)	|	// SMS[3] = 0;  ***SEE BELOW***
				(0  << 15)	|	// ETP[3] = 0; External Trigger polarity (ETR is non inverted)
				(0  << 14)	|	// ECE[3] = 0; External Clock Enable (0 = external clock mode 2 disabled)
				(0  << 12)	|	// ETPS[3] = 0; External Trigger Prescaler (0 = Prescaler off)
				(0  <<  8)	|	// ETF[3] = 0; External Trigger filter (0 = no filter, sampling is done at f_DTS)
				(0  <<  7)	|	// MSM[3] = 0; Master Slave Mode (0 = no action)
				(0  <<  4)	|	// TS[2:0] = 0; Trigger Selection (0 = Internal Trigger 0 (ITR0))
				(0  <<  0)	;	// SMS[2:0] = 0; Slave Mode Selection (0 = Slave mode disabled)
	TIM1->DIER = (0 << 14)	|	// TDE = 0; Trigger DMA Request Enable (0 = disabled)
				(0  << 13)	|	// COMDE = 0; COM DMA Request Enable (0 = disabled)
				(0  << 12)	|	// CC4DE = 0; Capture/Compare 4 DMA Request Enable (0 = disabled)
				(0  << 11)	|	// CC3DE = 0; Capture/Compare 3 DMA Request Enable (0 = disabled)
				(0  << 10)	|	// CC2DE = 0; Capture/Compare 2 DMA Request Enable (0 = disabled)
				(0  <<  9)	|	// CC1DE = 0; Capture/Compare 1 DMA Request Enable (0 = disabled)
				(0  <<  8)	|	// UDE = 0; Update DMA request disabled
				(0  <<  7)	|	// BIE = 0; Break interrupt disabled
				(0  <<  6)	|	// TIE = 0; Trigger interrupt disabled
				(0  <<  5)	|	// COMIE = 0; COM interrupt disabled
				(0  <<  4)	|	// CC4IE = 0; Capture/Compare 4 interrupt disabled
				(0  <<  3)	|	// CC3IE = 0; Capture/Compare 3 interrupt disabled
				(0  <<  2)	|	// CC2IE = 0; Capture/Compare 2 interrupt disabled
				(0  <<  1)	|	// CC1IE = 0; Capture/Compare 1 interrupt disabled
				(1  <<  0)	;	// UIE = 1; Update interrupt enabled
	// Clear all flags
	TIM1->SR = 0;
	// Make sure that no events are generated
	TIM1->EGR = 0;
	TIM1->CCMR1 = (0<< 24)	|	// OC2M[3] = 0; ***SEE BELOW***
				(0  << 16)	|	// OC1M[3] = 0; ***SEE BELOW***
				(0  << 15)	|	// OC2CE = 0; Output Compare 2 Clear Enable (0 = OC2Ref is not affected by the ETRF input)
				(6  << 12)	|	// OC2M[2:0] = 6; Output Compare 2 Mode (6 = PWM Mode 1: Active if TIM1->CNT < TIM1->CCR1, else inactive)
				(1  << 11)	|	// OC2PE = 1; Output Compare 2 Preload Enable (0 = preload on TIM1->CCR2 is enabled)
				(0  << 10)	|	// OC2FE = 0; Output Compare 2 Fast Enable (0 = CC1 output behaves normally, even if trigger is on; this is unimportant because the trigger is unused)
				(0  <<  8)	|	// CC2S = 0; Capture/Compare 2 Selection (0 = CC2 Channel is configured as an output)
				(0  <<  7)	|	// OC1CE = 0; Output Compare 1 Clear Enable (0 = OC1Ref is not affected by the ETRF input)
				(6  <<  4)	|	// OC1M[2:0] = 6; Output Compare 1 Mode (6 = PWM Mode 1: Active if TIM1->CNT < TIM1->CCR1, else inactive)
				(1  <<  3)	|	// OC1PE = 1; Output Compare 1 Preload Enable (0 = preload on TIM1->CCR1 is enabled)
				(0  <<  2)	|	// OC1FE = 0; Output Compare 1 Fast Enable (0 = CC1 output behaves normally, even if trigger is on; this is unimportant because the trigger is unused)
				(0  <<  0)	;	// CC1S = 0; Capture/Compare 1 Selection (0 = CC1 Channel is configured as an output)
	TIM1->CCMR2 = (0<< 24)	|	// OC4M[3] = 0; ***SEE BELOW***
				(0  << 16)	|	// OC3M[3] = 0; ***SEE BELOW***
				(0  << 15)	|	// OC4CE = 0; Output Compare 4 Clear Enable (0 = OC2Ref is not affected by the ETRF input)
				(0  << 12)	|	// OC4M[2:0] = 0; Output Compare 4 Mode (0 = Freeze: maintain previous value)
				(0  << 11)	|	// OC4PE = 0; Output Compare 4 Preload Enable (0 = preload on TIM1->CCR4 is disabled, CCR4 can be written at any time)
				(0  << 10)	|	// OC4FE = 0; Output Compare 4 Fast Enable (0 = CC1 output behaves normally, even if trigger is on; this is unimportant because the trigger is unused)
				(0  <<  8)	|	// CC4S = 0; Capture/Compare 4 Selection (0 = CC2 Channel is configured as an output)
				(0  <<  7)	|	// OC3CE = 0; Output Compare 3 Clear Enable (0 = OC1Ref is not affected by the ETRF input)
				(6  <<  4)	|	// OC3M[2:0] = 6; Output Compare 3 Mode (6 = PWM Mode 1: Active if TIM1->CNT < TIM1->CCR1, else inactive)
				(1  <<  3)	|	// OC3PE = 1; Output Compare 3 Preload Enable (0 = preload on TIM1->CCR3 is enabled)
				(0  <<  2)	|	// OC3FE = 0; Output Compare 3 Fast Enable (0 = CC1 output behaves normally, even if trigger is on; this is unimportant because the trigger is unused)
				(0  <<  0)	;	// CC3S = 0; Capture/Compare 3 Selection (0 = CC1 Channel is configured as an output)
	TIM1->CCMR3 = (0<< 24)	|	// OC6M[3] = 0; ***SEE BELOW***
				(0  << 16)	|	// OC5M[3] = 0; ***SEE BELOW***
				(0  << 15)	|	// OC6CE = 0; Output Compare 6 Clear Enable (0 = OC2Ref is not affected by the ETRF input)
				(0  << 12)	|	// OC6M[2:0] = 0; Output Compare 6 Mode (0 = Freeze: maintain previous value)
				(0  << 11)	|	// OC6PE = 0; Output Compare 6 Preload Enable (0 = preload on TIM1->CCR6 is disabled, CCR6 can be written at any time)
				(0  << 10)	|	// OC6FE = 0; Output Compare 6 Fast Enable (0 = CC1 output behaves normally, even if trigger is on; this is unimportant because the trigger is unused)
				(0  <<  8)	|	// CC6S = 0; Capture/Compare 6 Selection (0 = CC2 Channel is configured as an output)
				(0  <<  7)	|	// OC5CE = 0; Output Compare 5 Clear Enable (0 = OC1Ref is not affected by the ETRF input)
				(0  <<  4)	|	// OC5M[2:0] = 0; Output Compare 5 Mode (0 = Freeze: maintain previous value)
				(0  <<  3)	|	// OC5PE = 0; Output Compare 5 Preload Enable (0 = preload on TIM1->CCR5 is disabled, CCR5 can be written at any time)
				(0  <<  2)	|	// OC5FE = 0; Output Compare 5 Fast Enable (0 = CC1 output behaves normally, even if trigger is on; this is unimportant because the trigger is unused)
				(0  <<  0)	;	// CC5S = 0; Capture/Compare 5 Selection (0 = CC1 Channel is configured as an output)
	TIM1->CCER = (0 << 21)	|	// CC6P = 0; Capture/Compare 6 Output Polarity
				(0  << 20)	|	// CC6E = 0; Capture/Compare 6 Output Enable
				(0  << 17)	|	// CC5P = 0; Capture/Compare 5 Output Polarity
				(0  << 16)	|	// CC5E = 0; Capture/Compare 5 Output Enable
				(0  << 15)	|	// CC4NP = 0; Capture/Compare 4 Complementary Output Polarity
				(0  << 13)	|	// CC4P = 0; Capture/Compare 4 Output Polarity
				(0  << 12)	|	// CC4E = 0; Capture/Compare 4 Output Enable
				(0  << 11)	|	// CC3NP = 1; Capture/Compare 3 Complementary Output Polarity (Active High)
				(1  << 10)	|	// CC3NE = 1; Capture/Compare 3 Complementary Output Enable (Enabled)
				(0  <<  9)	|	// CC3P = 0; Capture/Compare 3 Output Polarity (Active High)
				(1  <<  8)	|	// CC3E = 1; Capture/Compare 3 Output Enable (Enabled)
				(0  <<  7)	|	// CC2NP = 0; Capture/Compare 2 Complementary Output Polarity (Active High)
				(1  <<  6)	|	// CC2NE = 0; Capture/Compare 2 Complementary Output Enable (Enabled)
				(0  <<  5)	|	// CC2P = 0; Capture/Compare 2 Output Polarity (Active High)
				(1  <<  4)	|	// CC2E = 0; Capture/Compare 2 Output Enable (Enabled)
				(0  <<  3)	|	// CC1NP = 0; Capture/Compare 1 Complementary Output Polarity (Active High)
				(1  <<  2)	|	// CC1NE = 0; Capture/Compare 1 Complementary Output Enable (Enabled)
				(0  <<  1)	|	// CC1P = 0; Capture/Compare 1 Output Polarity (Active High)
				(1  <<  0)	;	// CC1E = 0; Capture/Compare 1 Output Enable (Enabled)
	TIM1->CNT = 0;
	TIM1->PSC = period >> 16;
	period--;
	period &= 0xFFFF;
	TIM1->ARR = period;
	_period = period;
	// Initial Duty Cycle = 50% for all outputs
	period >>= 1;
	TIM1->CCR1 = period;
	TIM1->CCR2 = period;
	TIM1->CCR3 = period;
	// Note: The following outputs are unused.
	TIM1->CCR4 = 0;
	TIM1->CCR5 = 0;
	TIM1->CCR6 = 0;

	// deadtime behavior is a bit strange, so adjust to give maximum resolution)
	if(deadtime > 512)
	{
		// In this case, the upper bit (bit 7) must be set, bit 6 must be set, bit 5 must be set, and the other bits must be shifted one to account for the different timer scaling
		deadtime = 224 + ((deadtime & 0x1FF) >> 4);
	}
	else if(deadtime > 256)
	{
		// In this case, the upper bit (bit 7) must be set, bit 6 must be set, bit 5 must be clear, and the other bits must be shifted one to account for the different timer scaling
		deadtime = 192 + ((deadtime & 0xFF) >> 3);
	}
	else if(deadtime > 128)
	{
		// In this case, the upper bit (bit 7) must be set, bit 6 must be clear, and the other bits must be shifted one to account for the different timer scaling
		deadtime = 128 + ((deadtime & 0x7F) >> 1);
	}
	// The logic above should catch this (deadtime should always be confined to 8 bits), but if not, correct here.
	deadtime &= 0xFF;

	// Setup deadtime
	TIM1->BDTR = (0 << 25)	|	// BK2P = 0; Break 2 polarity (Break input 2 is active low)
				(0  << 24)	|	// BK2E = 0; Break 2 enable (Break 2 function disabled)
				(0  << 20)	|	// BK2F = 0; Break 2 filter (No filter, BRK2 acts asynchronously)
				(0  << 16)	|	// BKF = 0; Break 1 filter (No filter, BRK1 acts asynchronously)
				(1  << 15)	|	// MOE = 1; Main Output Enable (1 = outputs OC and OCN are enabled)
				(0  << 14)	|	// AOE = 0; Automatic Output Enable (0 = output must be enabled by software)
				(0  << 13)	|	// BKP = 0; Break 1 polarity (Break input 1 is active low)
				(0  << 12)	|	// BKE = 0; Break 1 enable (Break 1 function disabled)
				(1  << 11)	|	// OSSR = 1; Off-State Selection for Run Mode (Outputs are driven low, not forced to high impedance)
				(0  << 10)	|	// OSSI = 0; Off-State Selection for Idle Mode (Outputs are high impedance in idle mode)
				(0  <<  8)	|	// LOCK = 0; Lock Configuration (0 = No bit is write protected)
		 (deadtime  <<  0)	;	// DTG = configured;
	TIM1->DCR = (0  <<  8)	|	// DBL = 0; DMA Burst Length (0 = 1 transfer)
				(0  <<  0)	;	// DBA = 0; DMA Base Address (0 = TIM1->CR1)
	// Don't write to this register; it will access CR1 and clear it.
//	TIM1->DMAR = 0;				// DMAB = 0; (The address for burst accesses is not pointing to RAM)
	TIM1->AF1 = (0  << 14)	|	// ETRSEL = 0; ETR Source Selection (0 = ETR input is connected to GPIO)
				(0  << 11)	|	// BKCMP2P = 0; BRK COMP2 Input Polarity (0 = COMP2 input polarity is not inverted)
				(0  << 10)	|	// BKCMP1P = 0; BRK COMP1 Input Polarity (0 = COMP1 input polarity is not inverted)
				(0  <<  9)	|	// BKINP = 0; BRK BKIN Input Polarity (0 = BKIN input polarity is not inverted)
				(0  <<  8)	|	// BKDF1BK0E = 0; BRK dfsdm1_break[0] Enable (0 = disabled)
				(0  <<  2)	|	// BKCMP2E = 0; BRK COMP2 Enable (0 = disabled)
				(0  <<  1)	|	// BKCMP1E = 0; BRK COMP1 Enable (0 = disabled)
				(0  <<  0)	;	// BKINE = 0; BRK BKIN Input Enable (0 = disabled)
	TIM1->AF2 = (0  << 11)	|	// BK2CMP2P = 0; BRK2 COMP2 Input Polarity (0 = COMP2 input polarity is not inverted)
				(0  << 10)	|	// BK2CMP1P = 0; BRK2 COMP1 Input Polarity (0 = COMP1 input polarity is not inverted)
				(0  <<  9)	|	// BK2INP = 0; BRK2 BKIN Input Polarity (0 = BKIN input polarity is not inverted)
				(0  <<  8)	|	// BK2DF1BK0E = 0; BRK2 dfsdm1_break[0] Enable (0 = disabled)
				(0  <<  2)	|	// BK2CMP2E = 0; BRK2 COMP2 Enable (0 = disabled)
				(0  <<  1)	|	// BK2CMP1E = 0; BRK2 COMP1 Enable (0 = disabled)
				(0  <<  0)	;	// BK2INE = 0; BRK2 BKIN Input Enable (0 = disabled)
	TIM1->TISEL = (0<< 24)	|	// TI4SEL = 0; Selects TI4[0] to TI4[15] input (0 = TIM1_CH4)
				(0  << 16)	|	// TI3SEL = 0; Selects TI3[0] to TI3[15] input (0 = TIM1_CH3)
				(0  <<  8)	|	// TI2SEL = 0; Selects TI2[0] to TI2[15] input (0 = TIM1_CH2)
				(0  <<  0)	;	// TI1SEL = 0; Selects TI1[0] to TI1[15] input (0 = TIM1_CH1)

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
