// BspTimer.h
// Header file for simplified Board support Timer Setup.
// Includes templates for timer functions and inlined functions

#ifndef BSPTIMER_H
#define BSPTIMER_H

#include "stm32h7xx.h"

#define SUPPORTED_TIMERS 2
#define SUPPORTED_LP_TIMERS 5

#define TIMER_CLOCK_FREQUENCY 200000000

#ifdef __cplusplus
class BspTimer
{
	public:  static void (*_function[2])(void);
	private: static unsigned char _nextTimer;
	private: static unsigned char _nextLpTimer;

	public:  static void Initialize(void);
	public:  static char Setup(unsigned long period_in_ns, void (*funct)(void), unsigned char pri, bool oneShot);
	public:  static char SetupLpTimer(unsigned long period_in_ns);
	public:  static void SetupFreeRunningCounter(void);
	private: static void DummyFunction(void);
	public:  static _inline_ unsigned long GetFreeRunningCounter(void)
	{
		return TIM5->CNT;
	}
};
#endif

#endif //BSPTIMER_H
