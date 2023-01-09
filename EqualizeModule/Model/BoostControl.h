#ifndef BOOST_CONTROL_H
#define BOOST_CONTROL_H

#include <LPC822.h>

#if defined (__cplusplus)
class BoostControl
{
	/* Enumerated Type Definitions */


	/* Variable Declarations */


	/* Function Declarations */
	public:  static void Initialize(void);
	private: static long GuessDC(long highSideVoltage, long lowSideVoltageTimeMaxDc);
	private: static void BoostController(void);
};
#endif

#endif //SLEEP_LOGIC_H
