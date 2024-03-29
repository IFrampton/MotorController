// BspIo.h
// Header file for simplified Board support GPIO Setup.
// Includes templates for GPIO functions and inlined functions

#ifndef BSPSPI_H
#define BSPSPI_H

#include "stm32h7xx.h"

#ifdef __cplusplus
class BspSpi
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

	public:  static char Initialize(char port, unsigned long bitRate, volatile unsigned short **dataReg, volatile unsigned char **newDataFlag, unsigned short **readComplete);

	public:  static inline bool IsDataAvailable(volatile unsigned char *newDataFlag) {return(*newDataFlag & 0x1);}
	public:  static inline unsigned long ReadData(volatile unsigned short *dataReg) {return(*dataReg);}
	public:  static inline void SetReadComplete(unsigned short *readComplete) {*readComplete = (1 << 11) | (1 << 6);}

	private: static void Initialize_SystemConfig(void);
};
#endif

#endif //BSPSPI_H
