// BspDma.h
// Header file for simplified Board support DMA features.
// Includes templates for DMA functions and inlined functions

#ifndef BSPDMA_H
#define BSPDMA_H

#include "stm32h7xx.h"

#ifdef __cplusplus
class BspDma
{
	private: static unsigned char _nextStream;

	public:  static void Initialize(void);
	public:  static unsigned char SetupRxChannel(unsigned char input, unsigned long *periphSrc, unsigned long *memDest, unsigned char length);
	public:  static unsigned char SetupTxChannel(unsigned char input, unsigned long *memSource, unsigned long *periphDest, unsigned char length);
};
#endif

#endif //BSPDMA_H
