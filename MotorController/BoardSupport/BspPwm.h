#include "LPC5502.h"

#ifndef BSP_PWM_H
#define BSP_PWM_H

#if defined (__cplusplus)
class BspPwm
{
	/* Define Structures */
	/* Define Variables */
	//private: static TimerCallBackInfo _timers[3];
	private: static bool _initialized;
	/* Define Functions */
	public:  static void Initialize(void);
	//public:  static void SetupFreeRunningCounter(void);
	//public:  static unsigned long inline GetFreeRunningCounter() {return 2;}
};
#endif

#endif //BSP_PWM_H
