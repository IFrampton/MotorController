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
	public:  static unsigned char SetupRxChannel(unsigned char input, unsigned long *periphSource, unsigned long *memDest, unsigned char size, unsigned short length);
	public:  static unsigned char SetupTxChannel(unsigned char input, unsigned long *memSource, unsigned long *periphDest, unsigned char size, unsigned short length);
	public:  static void UpdateLength(unsigned char streamNum, unsigned char length)
	{
		DMA_Stream_TypeDef *stream = DMA1_Stream0;
		switch(streamNum)
		{
			case 0:
			default:
			{
				stream = DMA1_Stream0;
				break;
			}
			case 1:
			{
				stream = DMA1_Stream1;
				break;
			}
			case 2:
			{
				stream = DMA1_Stream2;
				break;
			}
			case 3:
			{
				stream = DMA1_Stream3;
				break;
			}
			case 4:
			{
				stream = DMA1_Stream4;
				break;
			}
			case 5:
			{
				stream = DMA1_Stream5;
				break;
			}
			case 6:
			{
				stream = DMA1_Stream6;
				break;
			}
			case 7:
			{
				stream = DMA1_Stream7;
				break;
			}
		}
		stream->CR &= ~(1<<0);
		stream->NDTR = length;
		stream->CR |= (1<<0);
	}
};
#endif

#endif //BSPDMA_H
