/*
 * BspDma.cpp
 *
 *  Created on: Feb 7, 2024
 *      Author: Isaac Frampton
 */

#include "BspDma.h"

unsigned char BspDma::_nextStream = 0;

void BspDma::Initialize(void)
{
	// Configure clock to DMA1 and DMA2
	// Nothing to configure

	// Reset DMA1 and DMA2
	RCC->AHB1RSTR |= (3  <<  0);
	// Remove Reset from DMA1 and DMA2
	RCC->AHB1RSTR &= ~(3  <<  0);
	// Reset DMA2D
	RCC->AHB3RSTR |= (1  <<  4);
	// Remove Reset from DMA2D
	RCC->AHB3RSTR &= ~(1  <<  4);
	// Reset MDMA
	RCC->AHB3RSTR |= (1  <<  0);
	// Remove Reset from MDMA
	RCC->AHB3RSTR &= ~(1  <<  0);
	// Reset BDMA
	RCC->AHB3RSTR |= (1  << 21);
	// Remove Reset from BDMA
	RCC->AHB3RSTR &= ~(1  << 21);

	RCC->AHB3ENR |= (1  <<  0); // MDMAEN
	RCC->AHB3ENR |= (1  <<  4); // DMA2DEN
	RCC->AHB1ENR |= (1  <<  0); // DMA2EN
	RCC->AHB1ENR |= (1  <<  1); // DMA1EN

	// Disable ADC for Core 1 (Core 1 is believed to be the M7 core)
	RCC_C1->AHB3ENR &= ~(1  <<  0); // MDMAEN
	RCC_C1->AHB3ENR &= ~(1  <<  4); // DMA2DEN
	RCC_C1->AHB1ENR &= ~(1  <<  0); // DMA2EN
	RCC_C1->AHB1ENR &= ~(1  <<  1); // DMA1EN

	// Enable ADC for Core 2 (Core 2 is believed to be the M4 core)
	RCC_C2->AHB3ENR |= (1  <<  0); // MDMAEN
	RCC_C2->AHB3ENR |= (1  <<  4); // DMA2DEN
	RCC_C2->AHB1ENR |= (1  <<  0); // DMA2EN
	RCC_C2->AHB1ENR |= (1  <<  1); // DMA1EN
}

unsigned char BspDma::SetupTxChannel(unsigned char input, unsigned long *memSource, unsigned long *periphDest, unsigned char size, unsigned short length)
{
	if(_nextStream >= 8)
	{
		return 255;
	}
	DMA_Stream_TypeDef *stream = DMA1_Stream0;
	DMAMUX_Channel_TypeDef *mux = DMAMUX1_Channel0;
	switch(_nextStream)
	{
		case 0:
		default:
		{
			stream = DMA1_Stream0;
			mux = DMAMUX1_Channel0;
			break;
		}
		case 1:
		{
			stream = DMA1_Stream1;
			mux = DMAMUX1_Channel1;
			break;
		}
		case 2:
		{
			stream = DMA1_Stream2;
			mux = DMAMUX1_Channel2;
			break;
		}
		case 3:
		{
			stream = DMA1_Stream3;
			mux = DMAMUX1_Channel3;
			break;
		}
		case 4:
		{
			stream = DMA1_Stream4;
			mux = DMAMUX1_Channel4;
			break;
		}
		case 5:
		{
			stream = DMA1_Stream5;
			mux = DMAMUX1_Channel5;
			break;
		}
		case 6:
		{
			stream = DMA1_Stream6;
			mux = DMAMUX1_Channel6;
			break;
		}
		case 7:
		{
			stream = DMA1_Stream7;
			mux = DMAMUX1_Channel7;
			break;
		}
	}
	// Setup stream
	stream->CR = 	(0  << 23)	|	// MBURST = 0; Memory Burst Transfer Configuration (0 = Single Transfer)
					(0  << 21)	|	// PBURST = 0; Peripheral Burst Transfer Configuration (0 = Single Transfer)
					(0  << 20)	|	// TRBUFF = 0; Enable the DMA to handle bufferable transfers (0 = No bufferable transfers)
					(0  << 19)	|	// CT = 0; Current Target (0 = current target is memory 0)
					(0  << 18)	|	// DBM = 0; Double Buffer Mode (0 = No buffer switching at end of transfer)
					(0  << 16)	|	// PL = 0; Priority Level (0 = Low)
					(0  << 15)	|	// PINCOS = 0; Peripheral Increment Offset Size (0 = linked to PSIZE)
				  (size << 13)	|	// MSIZE = 1; Memory Data Size (1 = 16-bit)
				  (size << 11)	|	// PSIZE = 1; Peripheral Data Size (1 = 16-bit)
					(1  << 10)	|	// MINC = 1; Memory Increment Mode (1 = Memory Pointer is incremented after each data transfer)
					(0  <<  9)	|	// PINC = 0; Peripheral Increment Mode (0 = Peripheral address pointer fixed)
					(1  <<  8)	|	// CIRC = 0; Circular Mode (1 = Circular mode enabled)
					(1  <<  6)	|	// DIR = 1; Data Transfer Direction (1 = Memory to Peripheral)
					(0  <<  5)	|	// PFCTRL = 0; Peripheral flow controller (0 = DMA, 1 = Peripheral controls flow)
					(0  <<  4)	|	// TCIE = 0; Transfer Complete Interrupt Enable (0 = disabled)
					(0  <<  3)	|	// HTIE = 0; Half Transfer Interrupt Enable (0 = disabled)
					(0  <<  2)	|	// TEIE = 0; Transfer Error Interrupt Enable (0 = disabled)
					(0  <<  1)	|	// DMEIE = 0; Direct Mode Error Interrupt Enable (0 = disabled)
					(0  <<  0)	;	// EN = 0; Stream Enable (0 = disabled (enabled later))

	stream->NDTR = length;
	stream->PAR = (unsigned long)periphDest;
	stream->M0AR = (unsigned long)memSource;
	//stream->M1AR = (unsigned long)periphDest;
	stream->FCR = (0<<7)	|	// FEIE = 0; FIFO Error Interrupt Enable (0 = disabled)
						(0  <<  3)	|	// FS = 0; FIFO Status (Read only)
						(0  <<  2)	|	// DMDIS = 0; Direct Mode Disable (0 = Direct Mode Enabled)
						(0  <<  0)	;	// FTH = 0; FIFO threshold selection

	// Setup DMA MUX
	mux->CCR = 	(0  << 24)	|	// SYNC_ID = 0; Synchronization Identification = 0
				(0  << 19)	|	// NBREQ = 0; Number of DMA Requests minus 1 to forward (0 = 1 request)
				(0  << 17)	|	// SPOL = 0; Synchronization Polarity (0 = No event)
				(0  << 16)	|	// SE = 0; Synchronization Enable (0 = diabled)
				(0  <<  9)	|	// EGE = 0; Event Generation Enable (0 = disabled)
				(0  <<  8)	|	// SOIE = 0; Synchronization Overrun Interrupt Enable)
			(input  <<  0)	;	// DMAREQ_ID = configured; DMA Request Identification
	//mux->RGCR = (0  << 19)	|	// GNBREQ = 0; Number of DMA Requests to be Generated
	//			(0  << 17)	|	// GPOL = 0; DMA Request Generator Trigger Polarity (0 = no event)
	//			(0  << 16)	|	// GE = 0; DMA Request Generator Channel x Enable (0 = disabled)
	//			(0  <<  8)	|	// OIE = 0; Trigger OVerrun Interupt Enable (0 = disabled)
	//			(0  <<  0)	;	// SIG_ID = 0; DMA Request Generator Trigger Polarity (0 = dmamux1_evt0)
	// Enable the stream
	stream->CR |= (1  <<  0);
	unsigned char nextStream = _nextStream;
	_nextStream++;
	return nextStream;
}

unsigned char BspDma::SetupRxChannel(unsigned char input, unsigned long *periphSource, unsigned long *memDest, unsigned char size, unsigned short length)
{
	if(_nextStream >= 8)
	{
		return 255;
	}
	size &= 0x3;
	DMA_Stream_TypeDef *stream = DMA1_Stream0;
	DMAMUX_Channel_TypeDef *mux = DMAMUX1_Channel0;
	switch(_nextStream)
	{
		case 0:
		default:
		{
			stream = DMA1_Stream0;
			mux = DMAMUX1_Channel0;
			break;
		}
		case 1:
		{
			stream = DMA1_Stream1;
			mux = DMAMUX1_Channel1;
			break;
		}
		case 2:
		{
			stream = DMA1_Stream2;
			mux = DMAMUX1_Channel2;
			break;
		}
		case 3:
		{
			stream = DMA1_Stream3;
			mux = DMAMUX1_Channel3;
			break;
		}
		case 4:
		{
			stream = DMA1_Stream4;
			mux = DMAMUX1_Channel4;
			break;
		}
		case 5:
		{
			stream = DMA1_Stream5;
			mux = DMAMUX1_Channel5;
			break;
		}
		case 6:
		{
			stream = DMA1_Stream6;
			mux = DMAMUX1_Channel6;
			break;
		}
		case 7:
		{
			stream = DMA1_Stream7;
			mux = DMAMUX1_Channel7;
			break;
		}
	}
	// Setup stream
	stream->CR = 	(0  << 23)	|	// MBURST = 0; Memory Burst Transfer Configuration (0 = Single Transfer)
					(0  << 21)	|	// PBURST = 0; Peripheral Burst Transfer Configuration (0 = Single Transfer)
					(0  << 20)	|	// TRBUFF = 0; Enable the DMA to handle bufferable transfers (0 = No bufferable transfers)
					(0  << 19)	|	// CT = 0; Current Target (0 = current target is memory 0)
					(0  << 18)	|	// DBM = 0; Double Buffer Mode (0 = No buffer switching at end of transfer)
					(0  << 16)	|	// PL = 0; Priority Level (0 = Low)
					(0  << 15)	|	// PINCOS = 0; Peripheral Increment Offset Size (0 = linked to PSIZE)
				  (size << 13)	|	// MSIZE = 1; Memory Data Size (1 = 16-bit)
				  (size << 11)	|	// PSIZE = 1; Peripheral Data Size (1 = 16-bit)
					(1  << 10)	|	// MINC = 1; Memory Increment Mode (1 = Memory Pointer is incremented after each data transfer)
					(0  <<  9)	|	// PINC = 0; Peripheral Increment Mode (0 = Peripheral address pointer fixed)
					(1  <<  8)	|	// CIRC = 0; Circular Mode (1 = Circular mode enabled)
					(0  <<  6)	|	// DIR = 0; Data Transfer Direction (0 = Peripheral to memory, 1 = Memory to Peripheral)
					(0  <<  5)	|	// PFCTRL = 0; Peripheral flow controller (0 = DMA, 1 = Peripheral controls flow)
					(0  <<  4)	|	// TCIE = 0; Transfer Complete Interrupt Enable (0 = disabled)
					(0  <<  3)	|	// HTIE = 0; Half Transfer Interrupt Enable (0 = disabled)
					(0  <<  2)	|	// TEIE = 0; Transfer Error Interrupt Enable (0 = disabled)
					(0  <<  1)	|	// DMEIE = 0; Direct Mode Error Interrupt Enable (0 = disabled)
					(0  <<  0)	;	// EN = 0; Stream Enable (0 = disabled (enabled later))

	stream->NDTR = length;
	stream->PAR = (unsigned long)periphSource;
	stream->M0AR = (unsigned long)memDest;
	//stream->M1AR = (unsigned long)memDest;
	stream->FCR = (0<<7)	|	// FEIE = 0; FIFO Error Interrupt Enable (0 = disabled)
						(0  <<  3)	|	// FS = 0; FIFO Status (Read only)
						(0  <<  2)	|	// DMDIS = 0; Direct Mode Disable (0 = Direct Mode Enabled)
						(0  <<  0)	;	// FTH = 0; FIFO threshold selection

	// Setup DMA MUX
	mux->CCR = 	(0  << 24)	|	// SYNC_ID = 0; Synchronization Identification = 0
				(0  << 19)	|	// NBREQ = 0; Number of DMA Requests minus 1 to forward (0 = 1 request)
				(0  << 17)	|	// SPOL = 0; Synchronization Polarity (0 = No event)
				(0  << 16)	|	// SE = 0; Synchronization Enable (0 = diabled)
				(0  <<  9)	|	// EGE = 0; Event Generation Enable (0 = disabled)
				(0  <<  8)	|	// SOIE = 0; Synchronization Overrun Interrupt Enable)
			(input  <<  0)	;	// DMAREQ_ID = configured; DMA Request Identification
	//mux->RGCR = (0  << 19)	|	// GNBREQ = 0; Number of DMA Requests to be Generated
	//			(0  << 17)	|	// GPOL = 0; DMA Request Generator Trigger Polarity (0 = no event)
	//			(0  << 16)	|	// GE = 0; DMA Request Generator Channel x Enable (0 = disabled)
	//			(0  <<  8)	|	// OIE = 0; Trigger OVerrun Interupt Enable (0 = disabled)
	//			(0  <<  0)	;	// SIG_ID = 0; DMA Request Generator Trigger Polarity (0 = dmamux1_evt0)
	// Enable the stream
	stream->CR |= (1  <<  0);
	unsigned char nextStream = _nextStream;
	_nextStream++;
	return nextStream;
}
