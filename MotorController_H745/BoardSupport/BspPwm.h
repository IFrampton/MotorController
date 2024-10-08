// BspPwm.h
// Header file for simplified Board support PWM Setup.
// Includes templates for PWM functions and inlined functions

#ifndef BSPPWM_H
#define BSPPWM_H

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
	public:  static _inline_ volatile unsigned short GetSwitchPeriod() {return(_period);}
	public:  static _inline_ void SetSwitchDutyCycle(char channel, short dutyCycle) {*((unsigned short *)(unsigned long)&TIM1->CCR1 + ((unsigned long)channel << 1)) = dutyCycle;}
	public:  static _inline_ void DisablePWM(void) {TIM1->BDTR &= ~(1 << 15);} // Clears Main Output Enable
	public:  static _inline_ void EnablePWM(void) {TIM1->BDTR |= (1 << 15);} // Sets Main Output Enable
};
#endif

#endif //BSPPWM_H
