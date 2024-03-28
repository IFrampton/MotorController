// BspTimer.h
// Header file for simplified Board support Timer Setup.
// Includes templates for timer functions and inlined functions

#ifndef BSPTIMER_H
#define BSPTIMER_H

#define SUPPORTED_TIMERS 2
#define SUPPORTED_LP_TIMERS 5

#ifdef __cplusplus
class BspTimer
{
	public:  static void (*_function[2])(void);
	private: static unsigned char _nextTimer;
	private: static unsigned char _nextLpTimer;

	public:  static void Initialize(void);
	public:  static char Setup(long clockCycles, void (*funct)(void), unsigned char pri, bool oneShot);
	public:  static char SetupLpTimer(unsigned long period_in_ns);
	private: static void DummyFunction(void);
};
#endif

#endif //BSPTIMER_H
