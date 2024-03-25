// BspPwm.h
// Header file for simplified Board support PWM Setup.
// Includes templates for PWM functions and inlined functions

#ifndef BSPPWM_H
#define BSPTIMER_H

#define CpuClockSpeed 100000000

#ifdef __cplusplus
class BspPwm
{
	public:  static void (*_function[2])(void);
	private: static unsigned char _nextPwm;
	private: static unsigned short _period;

	public:  static void Initialize(void);
	public:  static void SetupFixedPwm(unsigned char timer, unsigned long frequency, unsigned short deadtime);
	public:  static void SetupSwitchPwm(unsigned long frequency, unsigned short deadtime, void (*funct)(void), unsigned char pri);
	private: static void DummyFunction(void);
	public:  static inline volatile unsigned short GetSwitchPeriod() {return(_period);}
	public:  static inline void SetSwitchDutyCycle(char channel, short dutyCycle) {*((unsigned short *)(unsigned long)&TIM1->CCR1 + ((unsigned long)channel << 1)) = dutyCycle;}
};
#endif

#endif //BSPTIMER_H
