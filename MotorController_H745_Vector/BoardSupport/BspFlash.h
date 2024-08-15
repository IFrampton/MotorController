// BspIo.h
// Header file for simplified Board support GPIO Setup.
// Includes templates for GPIO functions and inlined functions

#ifndef BSPFLASH_H
#define BSPFLASH_H

#include "stm32h7xx.h"

#define ANALOG_SIZE 512
#define DIGITAL_SIZE 128
#define DATA_ADDRESS 0x081E0000
#define DATA_SIZE 0x0020000
#define DEFINITION_ADDRESS 0x0810001C
#define DEFINITION_MASK 0x3

#ifdef __cplusplus
class BspFlash
{
	private: static long _flashBuffer[ANALOG_SIZE];
	private: static char _flashDigitalBuffer[DIGITAL_SIZE];
	private: static long _flashTempBuffer[8];

	public:  static char Initialize();

	public:  static void Write();
	public:  static void UnlockFlash(char bank);
	public:  static void EraseSector(char bank, char sector);
	public:  static void WriteData(char bank, unsigned long *ram, unsigned long *flash, unsigned short length);
	public:  static void LockFlash(char bank);

	public:  static _inline_ long *GetAnalogBufferLocation(){return((long *)_flashBuffer);}
	public:  static _inline_ char *GetDigitalBufferLocation(){return((char *)_flashDigitalBuffer);}
	public:  static _inline_ unsigned long GetDefinition(unsigned long addr) {return(*(unsigned long *)((DEFINITION_ADDRESS + addr) & DEFINITION_MASK));}
};
#endif

#endif //BSPFLASH_H
