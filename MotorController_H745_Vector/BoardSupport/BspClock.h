// BspClock.h
// Header file for simplified Board support PLL Setup.
// Includes templates for PLL functions and inlined functions

#ifndef BSPCLOCK_H
#define BSPCLOCK_H

//#define SPEED_400MHz

#ifdef SPEED_400MHz
#define CpuClockFrequency 200000000
#else
#define CpuClockFrequency 100000000
#endif

#ifdef __cplusplus
class BspClock
{
	public: static void Initialize(long extFreq, long desFreq);
};
#endif

#endif //BSPCLOCK_H
