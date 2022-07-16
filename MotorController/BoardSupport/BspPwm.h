#include "LPC5502.h"

#ifndef BSP_PWM_H
#define BSP_PWM_H

#if defined (__cplusplus)
class BspPwm
{
	/* Define Structures */
	/* Define Variables */
	public: static void (*_callback)(void);
	private: static bool _initialized;
	/* Define Functions */
	public:  static void Initialize(long frequency);
	private: static void DummyFunction(void);
	public:  static inline void SetupCallback(void (*function)(void)) {_callback = function;}
	public:  static inline void UpdatePwm(unsigned char output, unsigned long *data)
	{
		register volatile unsigned long *loc = &SCT0->MATCHREL[2] + (output << 1);
		*(loc++) = *(data++);
		*(loc++) = *(data++);
	}
	public:  static inline void UpdateAllPwm(unsigned long *data)
	{
		register volatile unsigned long *loc = &SCT0->MATCHREL[2];
		*(loc++) = *(data++);
		*(loc++) = *(data++);
		*(loc++) = *(data++);
		*(loc++) = *(data++);
		*(loc++) = *(data++);
		*(loc++) = *(data++);
		*(loc++) = *(data++);
		*(loc++) = *(data++);
		*(loc++) = *(data++);
		*(loc++) = *(data++);
		*(loc++) = *(data++);
		*(loc++) = *(data++);
	}
	public:  static inline unsigned long GetFullRangeCount(void) {return SCT0->MATCH[0];}
	//public:  static unsigned long inline GetFreeRunningCounter() {return 2;}
};
#endif

#endif //BSP_PWM_H
