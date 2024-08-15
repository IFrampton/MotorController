// BspIo.h
// Header file for simplified Board support GPIO Setup.
// Includes templates for GPIO functions and inlined functions

#ifndef BSPSPI_H
#define BSPSPI_H

#include "stm32h7xx.h"

#ifdef __cplusplus
class BspSpi
{
	public:  static char Initialize(char port, unsigned long bitRate, volatile unsigned short **dataReg, volatile unsigned char **newDataFlag, unsigned short **readComplete);

	public:  static _inline_ bool IsDataAvailable(volatile unsigned char *newDataFlag) {return(*newDataFlag & 0x1);}
	public:  static _inline_ unsigned long ReadData(volatile unsigned short *dataReg) {return(*dataReg);}
	public:  static _inline_ void SetReadComplete(unsigned short *readComplete) {*readComplete = (1 << 11) | (1 << 6);}

	private: static void Initialize_SystemConfig(void);
};
#endif

#endif //BSPSPI_H
