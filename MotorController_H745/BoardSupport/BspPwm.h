// BspPwm.h
// Header file for simplified Board support PWM Setup.
// Includes templates for PWM functions and inlined functions

#ifndef BSPPWM_H
#define BSPTIMER_H

#define CpuClockSpeed 120000000

#ifdef __cplusplus
class BspPwm
{
	public:  static void (*_function[2])(void);
	private: static unsigned char _nextPwm;

	public:  static void Initialize(void);
	public:  static void SetupFixedPwm(unsigned char timer, unsigned long frequency, unsigned short deadtime);
	public:  static void SetupSwitchPwm(unsigned long frequency, void (*funct)(void), unsigned char pri);
	private: static void DummyFunction(void);
};
#endif

#endif //BSPTIMER_H
