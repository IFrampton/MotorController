#ifndef SLEEP_LOGIC_H
#define SLEEP_LOGIC_H

#include <LPC822.h>

#if defined (__cplusplus)
class SleepLogic
{
	/* Enumerated Type Definitions */
	enum WakeReason
	{
		RecentPowerup,
		MainProcessorCommunication,
		TimeIntervalElapsed,
		TOTAL_REASONS
	};

	/* Variable Declarations */
	// While using the enum above would be nice, there's no guarantee that it will only use one byte of memory.
	private: static unsigned char _wakeupReason;
	private: static bool _lowBatteryCondition;

	/* Function Declarations */
	public:  static void Initialize(void);
	public:  static void CheckSleep(void);
	public:  static inline void CheckWake(unsigned char wakeReason)
	{
		// Do not wake for the periodic timeout in the case where the battery voltage is very low.
		// Try to preserve the cell charge as long as possible.
		// The main processor can override this if it wants to use this chip to transfer some charge into the cell it is responsible for
		if(!_lowBatteryCondition || wakeReason == MainProcessorCommunication)
		{
			Wake(wakeReason);
		}
	}
	private: static void Wake(unsigned char wakeReason);
};
#endif

#endif //SLEEP_LOGIC_H
