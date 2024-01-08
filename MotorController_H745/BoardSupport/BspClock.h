// BspClock.h
// Header file for simplified Board support PLL Setup.
// Includes templates for PLL functions and inlined functions

#ifndef BSPCLOCK_H
#define BSPCLOCK_H

#ifdef __cplusplus
class BspClock
{
	public: static void Initialize(long extFreq, long desFreq);
};
#endif

#endif //BSPCLOCK_H
