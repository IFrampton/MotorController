// BspTimer.h
// Header file for simplified Board support Timer Setup.
// Includes templates for timer functions and inlined functions

#ifndef SLOWTIMER_H
#define SLOWTIMER_H

#define SLOW_TIMER_UPDATE_RATE 0.01f

#ifdef __cplusplus
class SlowTimer
{
	private: struct TimerData
	{
		unsigned long Period;
		unsigned long Count;
		void(*Function)(void);
	};
	private: static TimerData _timerData[8];
	private: static unsigned char _nextTimer;

	public:  static void Initialize(void);
	public:  static char Setup(long clockCycles, void (*funct)(void));
	public:  static void Update(void);
	private: static void DummyFunction(void);
};
#endif

#endif //SlowTIMER_H
