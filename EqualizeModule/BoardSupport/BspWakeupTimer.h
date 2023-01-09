#include "LPC822.h"

#ifndef BSP_WAKEUP_TIMER_H
#define BSP_WAKEUP_TIMER_H

#if defined (__cplusplus)
class BspWakeupTimer
{
	/* Define Structures */

	/* Define Variables */
	private: static void (*_callback)();
	private: static bool _initialized;
	/* Define Functions */
	public:  static void Initialize(void);
	public:  static unsigned char SetupTimer(unsigned long period, void (*callback)());
	private: static void DummyFunction(void);
};
#endif

#endif //BSP_WAKEUP_TIMER_H
