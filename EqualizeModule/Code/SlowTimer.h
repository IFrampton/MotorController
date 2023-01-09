#ifndef SLOW_TIMER_H
#define SLOW_TIMER_H

#if defined (__cplusplus)
class SlowTimer
{
	/* Enumerated Type Definition */

	/* Structure Definition */
	public: struct SlowTimerData
	{
		unsigned long Period;
		unsigned long Elapsed;
		void (*Callback)(void);
	};
	/* Variable Declarations */
	private: static SlowTimerData _slowTimers[8];
	private: static bool _initialized;
	private: static unsigned char _nextTimer;
	//private: static unsigned long _temp2;
	/* Function Declarations */
	public:  static void Initialize(void);
	public:  static void PeriodicUpdate(unsigned long timePeriod);
	public:  static unsigned char SetupTimer(unsigned long period, void (*callback)());
	private: static void DummyFunction(void);
};
#endif

#endif //SLOW_TIMER_H
