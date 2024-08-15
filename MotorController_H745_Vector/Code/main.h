// Main.h
// Header file for simplified Board support Main program.
// Includes templates for main program and inlined functions

#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
class Main
{
	public:  static void PwmFunct(void);
	public:  static void Tick_10ms(void);
	public:  static void Tick_100ms(void);
	public:  static void Tick_1s(void);
	public:  static void Tick_10s(void);
};
#endif

#endif // MAIN_H

