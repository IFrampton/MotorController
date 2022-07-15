#include "LPC5502.h"

#ifndef BSP_TIMER_H
#define BSP_TIMER_H

#if defined (__cplusplus)
class BspTimer
{
	/* Define Structures */
	struct TimerInfo
	{
		unsigned long Period;
		void (*Callback)(void);
	};
	/* Define Variables */
	public:  static TimerInfo _timerData[20];
	private: static unsigned char _nextTimer;
	private: static bool _initialized;
	/* Define Functions */
	public:  static void Initialize(void);
	public:  static void SetupFreeRunningCounter(void);
	public:  static unsigned char SetupTimer(unsigned long period, void (*callback)());
	public:  static long inline GetFreeRunningCounter() {return ((long)SysTick->VAL);}
	public:  static unsigned short inline GetFastFreeRunningCounter() {return ((unsigned short)SysTick->VAL);}
	private: static void DummyFunction(void);
};
#endif

#endif //BSP_TIMER_H
