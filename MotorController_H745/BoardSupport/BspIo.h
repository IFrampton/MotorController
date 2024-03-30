// BspIo.h
// Header file for simplified Board support GPIO Setup.
// Includes templates for GPIO functions and inlined functions

#ifndef BSPIO_H
#define BSPIO_H

#include "stm32h7xx.h"

#define USE_TIM2_TWICE

#ifdef __cplusplus
class BspIo
{
	public:  struct PinInfo
	{
		unsigned short *SetReg;
		unsigned short *ClrReg;
		unsigned short *StsReg;
		unsigned short Mask;
	};
	public:  enum GpioNames
	{
		AUX_NOT_AVAIL,
		MAIN_NOT_AVAIL,
		INPUT_1,
		INPUT_2,
		INPUT_3,
		INPUT_4,
		LED_RED,
		LED_YELLOW,
		LED_GREEN,
		NUMBER_OF_GPIO
	};
	public:  static PinInfo _pinInfo[NUMBER_OF_GPIO];

	public:  static void Initialize(void);

	private: static GPIO_TypeDef *GetGpioPort(char port);

	public:  static void InitInput(char port, unsigned char pin, PinInfo *pinInfo);
	public:  static void InitOutput(char port, unsigned char pin, PinInfo *pinInfo);
	public:  static void InitAltFunction(char port, unsigned char pin, char alternate);
	public:  static void InitAnalog(char port, unsigned char pin);

	public:  static inline char GetIoPin(PinInfo *pin) {return(*pin->StsReg & pin->Mask);}
	public:  static inline void SetIoPin(PinInfo *pin) {*pin->SetReg = pin->Mask;}
	public:  static inline void ClearIoPin(PinInfo *pin) {*pin->ClrReg = pin->Mask;}
};
#endif

#endif //BSPIO_H
