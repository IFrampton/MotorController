/*
 * BspFlash.cpp
 *
 *  Created on: Mar 30, 2024
 *      Author: Isaac Frampton
 */

#include "BspFlash.h"

long BspFlash::_flashBuffer[ANALOG_SIZE];
char BspFlash::_flashDigitalBuffer[DIGITAL_SIZE];
long BspFlash::_flashTempBuffer[8];

char BspFlash::Initialize()
{
	register long *nvmLocation = (long *)DATA_ADDRESS;
	register long *ramLocation = _flashBuffer;
	for(long idx = 0; idx < ANALOG_SIZE; idx++)
	{
		*(ramLocation++) = *(nvmLocation++);
	}

	register unsigned char *flashLocation = (unsigned char *)(DATA_ADDRESS + DATA_SIZE - (DIGITAL_SIZE >> 2));
	register char *digLocation = _flashDigitalBuffer;
	for(long idx = 0; idx < (DIGITAL_SIZE >> 2); idx++)
	{
		// Each boolean value is stored as a char. This allows tracking of validity
		// Note: Flash defaults to 1 when cleared, so the MSb needs to be low to indicate validity.
		// 0b00 = valid data and low
		// 0b01 = valid data and high
		// 0b10 = invalid data and low
		// 0b11 = invalid data and high
		register unsigned char data = *(flashLocation++);
		*(digLocation++) = (data & 0x3);
		data >>= 2;
		*(digLocation++) = (data & 0x3);
		data >>= 2;
		*(digLocation++) = (data & 0x3);
		data >>= 2;
		*(digLocation++) = (data & 0x3);
	}
	return 0;
}

void BspFlash::Write()
{
	NVIC_DisableIRQ(TIM6_DAC_IRQn);
	NVIC_DisableIRQ(TIM1_UP_IRQn);

	//char bank = FLASH->OPTCR >> 31;
	//UnlockFlash(bank);
	//ErasePage(bank, 7);
	//It turns out that Bank 1 registers always point to the active bank for M7 processor We want this in the M4 space.
	UnlockFlash(1);
	EraseSector(1, 7);
	WriteData(1, (unsigned long *)_flashBuffer, (unsigned long *)DATA_ADDRESS, ANALOG_SIZE);
	register unsigned long *digBuf = (unsigned long *) _flashTempBuffer;
	register unsigned char *charBuf = (unsigned char *)_flashDigitalBuffer;
	for(char x = 8; x; x--)
	{
		*digBuf = 0;
		for(char y = 16; y; y--)
		{
			*digBuf >>= 2;
			*digBuf += (*charBuf & 0x3) << 30;
			charBuf++;
		}
		digBuf++;
	}
	WriteData(1, (unsigned long *)_flashTempBuffer, (unsigned long *)(DATA_ADDRESS + DATA_SIZE - (DIGITAL_SIZE >> 2)), 8);
	LockFlash(1);

	NVIC_EnableIRQ(TIM1_UP_IRQn);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

void BspFlash::EraseSector(char bank, char sector)
{
	sector &= 7;
	if(bank)
	{
		FLASH->CR2 = (0 << 28)	|	// CRCRDERRIE1 = 0; Bank 1 CRC read error interrupt enable bit (0 = disabled)
					(0  << 27)	|	// CRCENDIE1 = 0; Bank 1 CRC end of calculation interrupt enable bit (0 = disabled)
					(0  << 26)	|	// DBECCERRIE1 = 0; Bank 1 ECC double detection error interrupt enable bit (0 = disabled)
					(0  << 25)	|	// SNECCERRIE1 = 0; Bank 1 ECC single correction error interrupt enable bit (0 = disabled)
					(0  << 24)	|	// RDSERRIE1 = 0; Bank 1 secure error interrupt enable bit (0 = disabled)
					(0  << 23)	|	// RDPERRIE1 = 0; Bank 1 read protection error interrupt enable bit (0 = disabled)
					(0  << 22)	|	// OPERRIE1 = 0; Bank 1 write/erase error interrupt enable bit (0 = disabled)
					(0  << 21)	|	// INCERRIE1 = 0; Bank 1 inconsistency error interrupt enable bit (0 = disabled)
					(0  << 19)	|	// STRBERRIE1 = 0; Bank 1 strobe error interrupt enable bit (0 = disabled)
					(0  << 18)	|	// PGSERRIE1 = 0; Bank 1 programming sequence error interrupt enable bit (0 = disabled)
					(0  << 17)	|	// WRPERRIE1 = 0; Bank 1 write protection error interrupt enable bit (0 = disabled)
					(0  << 16)	|	// EOPIE1 = 0; Bank 1 end-of-program interrupt enable bit  (0 = no interrupt generated when program finishes)
					(0  << 15)	|	// CRC_EN = 0; Bank 1 CRC control bit (0 = CRC not used)
				(sector <<  8)	|	// SNB1 = sector; Bank 1 sector erase selection number (sector = select appropriate page)
					(1  <<  7)	|	// START1 = 0; Bank 1 erase start control bit (1 = Start erase)
					(0  <<  6)	|	// FW1 = 0; Bank 1 CRC end of calculation interrupt enable bit
					(3  <<  4)	|	// PSIZE1 = 3; Bank 1 program size (3 = programming executed with double word parallelism)
					(0  <<  3)	|	// BER11 = 0; Bank 1 erase request (only erase a sector, not the entire bank)
					(1  <<  2)	|	// SER1 = 1; Bank 1 sector erase request (1 = erase associated sector)
					(0  <<  1)	|	// PG1 = 0; Bank 1 internal buffer control bit (0 = buffer disabled, 1 = buffer enabled)
					(0  <<  0)	;	// LOCK1 = 0; Bank 1 configuration lock bit (0 = leave unlocked)

		// wait for erase to complete
		while(FLASH->SR2 & 0x4);
	}
	else
	{
		FLASH->CR1 = (0 << 28)	|	// CRCRDERRIE1 = 0; Bank 1 CRC read error interrupt enable bit (0 = disabled)
					(0  << 27)	|	// CRCENDIE1 = 0; Bank 1 CRC end of calculation interrupt enable bit (0 = disabled)
					(0  << 26)	|	// DBECCERRIE1 = 0; Bank 1 ECC double detection error interrupt enable bit (0 = disabled)
					(0  << 25)	|	// SNECCERRIE1 = 0; Bank 1 ECC single correction error interrupt enable bit (0 = disabled)
					(0  << 24)	|	// RDSERRIE1 = 0; Bank 1 secure error interrupt enable bit (0 = disabled)
					(0  << 23)	|	// RDPERRIE1 = 0; Bank 1 read protection error interrupt enable bit (0 = disabled)
					(0  << 22)	|	// OPERRIE1 = 0; Bank 1 write/erase error interrupt enable bit (0 = disabled)
					(0  << 21)	|	// INCERRIE1 = 0; Bank 1 inconsistency error interrupt enable bit (0 = disabled)
					(0  << 19)	|	// STRBERRIE1 = 0; Bank 1 strobe error interrupt enable bit (0 = disabled)
					(0  << 18)	|	// PGSERRIE1 = 0; Bank 1 programming sequence error interrupt enable bit (0 = disabled)
					(0  << 17)	|	// WRPERRIE1 = 0; Bank 1 write protection error interrupt enable bit (0 = disabled)
					(0  << 16)	|	// EOPIE1 = 0; Bank 1 end-of-program interrupt enable bit  (0 = no interrupt generated when program finishes)
					(0  << 15)	|	// CRC_EN = 0; Bank 1 CRC control bit (0 = CRC not used)
				(sector <<  8)	|	// SNB1 = sector; Bank 1 sector erase selection number (sector = select appropriate page)
					(1  <<  7)	|	// START1 = 0; Bank 1 erase start control bit (1 = Start erase)
					(0  <<  6)	|	// FW1 = 0; Bank 1 CRC end of calculation interrupt enable bit
					(3  <<  4)	|	// PSIZE1 = 3; Bank 1 program size (3 = programming executed with double word parallelism)
					(0  <<  3)	|	// BER11 = 0; Bank 1 erase request (only erase a sector, not the entire bank)
					(1  <<  2)	|	// SER1 = 1; Bank 1 sector erase request (1 = erase associated sector)
					(0  <<  1)	|	// PG1 = 0; Bank 1 internal buffer control bit (0 = buffer disabled, 1 = buffer enabled)
					(0  <<  0)	;	// LOCK1 = 0; Bank 1 configuration lock bit (0 = leave unlocked)

		// wait for erase to complete
		while(FLASH->SR1 & 0x4);
	}
}

void BspFlash::WriteData(char bank, unsigned long *ram, unsigned long *flash, unsigned short length)
{
	if(bank)
	{
		FLASH->CR2 = (0 << 28)	|	// CRCRDERRIE1 = 0; Bank 1 CRC read error interrupt enable bit (0 = disabled)
					(0  << 27)	|	// CRCENDIE1 = 0; Bank 1 CRC end of calculation interrupt enable bit (0 = disabled)
					(0  << 26)	|	// DBECCERRIE1 = 0; Bank 1 ECC double detection error interrupt enable bit (0 = disabled)
					(0  << 25)	|	// SNECCERRIE1 = 0; Bank 1 ECC single correction error interrupt enable bit (0 = disabled)
					(0  << 24)	|	// RDSERRIE1 = 0; Bank 1 secure error interrupt enable bit (0 = disabled)
					(0  << 23)	|	// RDPERRIE1 = 0; Bank 1 read protection error interrupt enable bit (0 = disabled)
					(0  << 22)	|	// OPERRIE1 = 0; Bank 1 write/erase error interrupt enable bit (0 = disabled)
					(0  << 21)	|	// INCERRIE1 = 0; Bank 1 inconsistency error interrupt enable bit (0 = disabled)
					(0  << 19)	|	// STRBERRIE1 = 0; Bank 1 strobe error interrupt enable bit (0 = disabled)
					(0  << 18)	|	// PGSERRIE1 = 0; Bank 1 programming sequence error interrupt enable bit (0 = disabled)
					(0  << 17)	|	// WRPERRIE1 = 0; Bank 1 write protection error interrupt enable bit (0 = disabled)
					(0  << 16)	|	// EOPIE1 = 0; Bank 1 end-of-program interrupt enable bit  (0 = no interrupt generated when program finishes)
					(0  << 15)	|	// CRC_EN = 0; Bank 1 CRC control bit (0 = CRC not used)
					(7  <<  8)	|	// SNB1 = 7; Bank 1 sector erase selection number (0 = select page 7)
					(0  <<  7)	|	// START1 = 0; Bank 1 erase start control bit (1 = Start erase)
					(0  <<  6)	|	// FW1 = 0; Bank 1 CRC end of calculation interrupt enable bit
					(3  <<  4)	|	// PSIZE1 = 3; Bank 1 program size (3 = programming executed with double word parallelism)
					(0  <<  3)	|	// BER11 = 0; Bank 1 erase request (only erase a sector, not the entire bank)
					(0  <<  2)	|	// SER1 = 1; Bank 1 sector erase request (1 = erase associated sector)
					(1  <<  1)	|	// PG1 = 0; Bank 1 internal buffer control bit (0 = buffer disabled, 1 = buffer enabled)
					(0  <<  0)	;	// LOCK1 = 0; Bank 1 configuration lock bit (0 = leave unlocked)
		register unsigned long *nvm = flash;
		register unsigned long *vm = ram;
		for(long x = length; x; x--)
		{
			if( x >= 8)
			{
				for(char y = 8; y; y--)
				{
					*(nvm++) = *(vm++);
				}
				x -= 7;
				while(FLASH->SR2 & 0x4);
			}
			else
			{
				for(char y = x; y; y--)
				{
					*(nvm++) = *(vm++);
				}
				FLASH->CR1 |= (1 << 6);
				while(FLASH->SR2 & 0x4);
				break;
			}
		}
	}
	else
	{
		FLASH->CR1 = (0 << 28)	|	// CRCRDERRIE1 = 0; Bank 1 CRC read error interrupt enable bit (0 = disabled)
					(0  << 27)	|	// CRCENDIE1 = 0; Bank 1 CRC end of calculation interrupt enable bit (0 = disabled)
					(0  << 26)	|	// DBECCERRIE1 = 0; Bank 1 ECC double detection error interrupt enable bit (0 = disabled)
					(0  << 25)	|	// SNECCERRIE1 = 0; Bank 1 ECC single correction error interrupt enable bit (0 = disabled)
					(0  << 24)	|	// RDSERRIE1 = 0; Bank 1 secure error interrupt enable bit (0 = disabled)
					(0  << 23)	|	// RDPERRIE1 = 0; Bank 1 read protection error interrupt enable bit (0 = disabled)
					(0  << 22)	|	// OPERRIE1 = 0; Bank 1 write/erase error interrupt enable bit (0 = disabled)
					(0  << 21)	|	// INCERRIE1 = 0; Bank 1 inconsistency error interrupt enable bit (0 = disabled)
					(0  << 19)	|	// STRBERRIE1 = 0; Bank 1 strobe error interrupt enable bit (0 = disabled)
					(0  << 18)	|	// PGSERRIE1 = 0; Bank 1 programming sequence error interrupt enable bit (0 = disabled)
					(0  << 17)	|	// WRPERRIE1 = 0; Bank 1 write protection error interrupt enable bit (0 = disabled)
					(0  << 16)	|	// EOPIE1 = 0; Bank 1 end-of-program interrupt enable bit  (0 = no interrupt generated when program finishes)
					(0  << 15)	|	// CRC_EN = 0; Bank 1 CRC control bit (0 = CRC not used)
					(7  <<  8)	|	// SNB1 = 7; Bank 1 sector erase selection number (0 = select page 7)
					(0  <<  7)	|	// START1 = 0; Bank 1 erase start control bit (1 = Start erase)
					(0  <<  6)	|	// FW1 = 0; Bank 1 CRC end of calculation interrupt enable bit
					(3  <<  4)	|	// PSIZE1 = 3; Bank 1 program size (3 = programming executed with double word parallelism)
					(0  <<  3)	|	// BER11 = 0; Bank 1 erase request (only erase a sector, not the entire bank)
					(0  <<  2)	|	// SER1 = 1; Bank 1 sector erase request (1 = erase associated sector)
					(1  <<  1)	|	// PG1 = 0; Bank 1 internal buffer control bit (0 = buffer disabled, 1 = buffer enabled)
					(0  <<  0)	;	// LOCK1 = 0; Bank 1 configuration lock bit (0 = leave unlocked)
		register unsigned long *nvm = flash;
		register unsigned long *vm = ram;
		for(long x = length; x; x--)
		{
			if( x >= 8)
			{
				for(char y = 8; y; y--)
				{
					*(nvm++) = *(vm++);
				}
				x -= 8;
				while(FLASH->SR1 & 0x4);
			}
			else
			{
				for(char y = x; y; y--)
				{
					*(nvm++) = *(vm++);
				}
				FLASH->CR1 |= (1 << 6);
				while(FLASH->SR1 & 0x4);
				break;
			}
		}
	}
}

void BspFlash::UnlockFlash(char bank)
{
	if(bank)
	{
		FLASH->KEYR2 = 0x45670123;
		FLASH->KEYR2 = 0xCDEF89AB;
	}
	else
	{
		FLASH->KEYR1 = 0x45670123;
		FLASH->KEYR1 = 0xCDEF89AB;
	}
	//FLASH->OPTKEYR = 0x08192A3B;
	//FLASH->OPTKEYR = 0x4C5D6E7F;
}

void BspFlash::LockFlash(char bank)
{
	if(bank)
	{
		FLASH->CR2 = (0 << 28)	|	// CRCRDERRIE1 = 0; Bank 1 CRC read error interrupt enable bit (0 = disabled)
					(0  << 27)	|	// CRCENDIE1 = 0; Bank 1 CRC end of calculation interrupt enable bit (0 = disabled)
					(0  << 26)	|	// DBECCERRIE1 = 0; Bank 1 ECC double detection error interrupt enable bit (0 = disabled)
					(0  << 25)	|	// SNECCERRIE1 = 0; Bank 1 ECC single correction error interrupt enable bit (0 = disabled)
					(0  << 24)	|	// RDSERRIE1 = 0; Bank 1 secure error interrupt enable bit (0 = disabled)
					(0  << 23)	|	// RDPERRIE1 = 0; Bank 1 read protection error interrupt enable bit (0 = disabled)
					(0  << 22)	|	// OPERRIE1 = 0; Bank 1 write/erase error interrupt enable bit (0 = disabled)
					(0  << 21)	|	// INCERRIE1 = 0; Bank 1 inconsistency error interrupt enable bit (0 = disabled)
					(0  << 19)	|	// STRBERRIE1 = 0; Bank 1 strobe error interrupt enable bit (0 = disabled)
					(0  << 18)	|	// PGSERRIE1 = 0; Bank 1 programming sequence error interrupt enable bit (0 = disabled)
					(0  << 17)	|	// WRPERRIE1 = 0; Bank 1 write protection error interrupt enable bit (0 = disabled)
					(0  << 16)	|	// EOPIE1 = 0; Bank 1 end-of-program interrupt enable bit  (0 = no interrupt generated when program finishes)
					(0  << 15)	|	// CRC_EN = 0; Bank 1 CRC control bit (0 = CRC not used)
					(0  <<  8)	|	// SNB1 = 0; Bank 1 sector erase selection number (page = select appropriate page)
					(0  <<  7)	|	// START1 = 0; Bank 1 erase start control bit (1 = Start erase)
					(0  <<  6)	|	// FW1 = 0; Bank 1 CRC end of calculation interrupt enable bit
					(3  <<  4)	|	// PSIZE1 = 3; Bank 1 program size (3 = programming executed with double word parallelism)
					(0  <<  3)	|	// BER11 = 0; Bank 1 erase request (only erase a sector, not the entire bank)
					(0  <<  2)	|	// SER1 = 0; Bank 1 sector erase request (0 = do not erase associated sector)
					(0  <<  1)	|	// PG1 = 0; Bank 1 internal buffer control bit (0 = buffer disabled)
					(1  <<  0)	;	// LOCK1 = 0; Bank 1 configuration lock bit (0 = leave unlocked)
	}
	else
	{
		FLASH->CR1 = (0 << 28)	|	// CRCRDERRIE1 = 0; Bank 1 CRC read error interrupt enable bit (0 = disabled)
					(0  << 27)	|	// CRCENDIE1 = 0; Bank 1 CRC end of calculation interrupt enable bit (0 = disabled)
					(0  << 26)	|	// DBECCERRIE1 = 0; Bank 1 ECC double detection error interrupt enable bit (0 = disabled)
					(0  << 25)	|	// SNECCERRIE1 = 0; Bank 1 ECC single correction error interrupt enable bit (0 = disabled)
					(0  << 24)	|	// RDSERRIE1 = 0; Bank 1 secure error interrupt enable bit (0 = disabled)
					(0  << 23)	|	// RDPERRIE1 = 0; Bank 1 read protection error interrupt enable bit (0 = disabled)
					(0  << 22)	|	// OPERRIE1 = 0; Bank 1 write/erase error interrupt enable bit (0 = disabled)
					(0  << 21)	|	// INCERRIE1 = 0; Bank 1 inconsistency error interrupt enable bit (0 = disabled)
					(0  << 19)	|	// STRBERRIE1 = 0; Bank 1 strobe error interrupt enable bit (0 = disabled)
					(0  << 18)	|	// PGSERRIE1 = 0; Bank 1 programming sequence error interrupt enable bit (0 = disabled)
					(0  << 17)	|	// WRPERRIE1 = 0; Bank 1 write protection error interrupt enable bit (0 = disabled)
					(0  << 16)	|	// EOPIE1 = 0; Bank 1 end-of-program interrupt enable bit  (0 = no interrupt generated when program finishes)
					(0  << 15)	|	// CRC_EN = 0; Bank 1 CRC control bit (0 = CRC not used)
					(0  <<  8)	|	// SNB1 = 0; Bank 1 sector erase selection number (page = select appropriate page)
					(0  <<  7)	|	// START1 = 0; Bank 1 erase start control bit (1 = Start erase)
					(0  <<  6)	|	// FW1 = 0; Bank 1 CRC end of calculation interrupt enable bit
					(3  <<  4)	|	// PSIZE1 = 3; Bank 1 program size (3 = programming executed with double word parallelism)
					(0  <<  3)	|	// BER11 = 0; Bank 1 erase request (only erase a sector, not the entire bank)
					(0  <<  2)	|	// SER1 = 0; Bank 1 sector erase request (0 = do not erase associated sector)
					(0  <<  1)	|	// PG1 = 0; Bank 1 internal buffer control bit (0 = buffer disabled)
					(1  <<  0)	;	// LOCK1 = 0; Bank 1 configuration lock bit (0 = leave unlocked)
	}
}

#if 0
	RCC->D2CCIP1R &= ~(3 << 12);
	RCC->D2CCIP1R |= (1 << 12); // use pll2_p_clk (which is unchanged with CPU speed)
	// Turn on the kernel clock to the peripheral
	// Remove Reset
	RCC->APB2RSTR &= ~(1 << 12);
	// Enable
	RCC->APB2ENR |= (1 << 12);
	RCC_C2->APB2ENR |= (1 << 12);

	spi->CR1 = 	(0  << 16)	|	// IOLOCK = 0; Locking the AF configuration of associated I/Os is not locked
				(0  << 15)	|	// TCRCINI = 0; CRC calculation initialization pattern for transmitter (All zero pattern is applied)
				(0  << 14)	|	// RCRCINI = 0; CRC calculation initialization pattern for receiver (All zero pattern is applied)
				(0  << 13)	|	// CRC33_17 = 0; 32-bit CRC polynomial configuration (full size, CRC polynomial is not used)
				(1  << 12)	|	// SSI = 1; Internal SS signal input level (this feature is not used, requires SSM)
				(0  << 11)	|	// HDDIR = 0; RX/TX direction at half-duplex mode (set as receiver, but unused)
				(0  << 10)	|	// CSUSP = 0; Master suspend request (No suspend requested)
				(0  <<  9)	|	// CSTART = 0; Master Transfer start (Not requested)
				(1  <<  8)	|	// MASRX = 1; Master automatic suspend in receive mode (Set to suspend if buffer full).
				(0  <<  0)	;	// SPE = 0; Serial peripheral enable (disabled to allow configuration)
	spi->CR2 = 	(0  << 16)	|	// TSER = 0 Data transfer extensions to reload into TSIZE when transaction is completed
				(0  <<  0)	;	// TSIZE = 0; Number of Data in Current Transfer (SPI is in endless mode)
	spi->CFG1 = (5  << 28)	|	// MBR = 4; Master baud rate = SPI clock / 32
				(0  << 22)	|	// CRCEN = 0; Hardware CRC computation disable
				(7  << 16)	|	// CRCSIZE = 7; Length of CRC frame to be transacted and compared (7 = 8 bits, required because CRC is disabled)
				(0  << 15)	|	// TXDMAEN = 0; Transmit DMA is disabled
				(0  << 14)	|	// RXDMAEN = 0; Receive DMA is disabled
				(1  << 11)	|	// UDRDET = 1; Detection of underrun condition at slave transmitter is at end of last data frame
				(0  <<  9)	|	// UDRCFG = 0; Behavior of slave transmitter at underrun condition (slave sends defined pattern on underrun)
				(0  <<  5)	|	// FTHLV = 0; FIFO Threshold Level (1 data frames)
				(15 <<  0)	;	// DSIZE = 15; Number of bits in a SPI data frame (each SPI packet contains 16 bits)
	spi->CFG2 = (0  << 31)	|	// AFCNTR = 0; Alternate Function GPIO Control (the peripheral takes no control of GPIO when disabled)
				(0  << 30)	|	// SSOM = 0; SS Output management in master mode (SS is kept active until data transfer is complete, inactive with EOT flag)
				(0  << 29)	|	// SSOE = 0; SS Output is disabled and the SPI can work in multi-master configuration
				(0  << 28)	|	// SSIOP = 0; SS Input / Output Polarity (low level is active of SS signal)
				(1  << 26)	|	// SSM = 1; Software management of SS signal input (SS input value depends software (SSI), not SS pad)
				(0  << 25)	|	// CPOL = 0; Clock Polarity (SCK signal is at 0 when Idle)
				(1  << 24)	|	// CPHA = 1; Clock Phase (The second clock transition is the first data capture edge)
				(0  << 23)	|	// LSBFIRST = 0; Data Frame first (0 = MSB transmitted first, 1 = LSB Transmitted first)
				(1  << 22)	|	// MASTER = 1; SPI is acting as a master
				(0  << 19)	|	// SP = 0; Serial Protocol (SPI Motorola)
				(2  << 17)	|	// COMM = 2; Simplex Received
				(0  << 15)	|	// IOSWP = 0; MISO = MISO and MOSI = MOSI
				(7  <<  4)	|	// MIDI = 7; Master Inter-Data Idleness (no extra delay)
				(0  <<  0)	;	// MSSI = 0; Master SS idleness (no extra delay)
	spi->IER = 0;	// No interrupts supported
	spi->CRCPOLY = 0;	// No CRC is used, therefore, no polynomial is required
	//spi->TXCRC = 0;	// No CRC is used, therefore, no reading of the CRC is required
	//spi->RXCRC = 0;	// No CRC is used, therefore, no reading of the CRC is required
	spi->UDRDR = 0xDEADBEEF;	// Send oxDEADBEEF if there is an underrun (this is never used because this device is operating as a master).
	spi->I2SCFGR = 	(1  << 25)	|	// MCKOE = 1; Master clock output is enabled
					(0  << 24)	|	// ODD = 0;	Real divider value is I2SDIV * 2
					(5  << 16)	|	// I2SDIV = 5; Real divider value is I2SDIV * 2 = 10
					(0  << 14)	|	// DATFMT = 0; Data Format (The data is right-aligned)
					(0  << 13)	|	// WSINV = 0; Word select inversion (Left Channel first)
					(0  << 12)	|	// FIXCH = 0; Fixed Channel length in slave (the channel length is not 16 or 32 bits)
					(0  << 11)	|	// CKPOL = 0; Serial Audio Clock Polarity (The signals are changed on falling edge, read on rising edge)
					(0  << 10)	|	// CHLEN = 0; Channel Length (16 bits)
					(0  <<  8)	|	// DATLEN = 0; Data length to be transferred (0 = 16 bits)
					(0  <<  7)	|	// PCMSYNC = 0; PCM Frame synchronization (short frame synchronization)
					(0  <<  4)	|	// I2SSTD = 0; I2S Standard selection (0 = Philips)
					(3  <<  1)	|	// I2SCFG = 0; I2S Configuration Mode (3 = Master Receive)
					(0  <<  0)	;	// I2SMOD = 0; I2S Mode Selection (0 = Spi Mode Selected)

	*dataReg = (volatile unsigned short *)&spi->RXDR;
	*newDataFlag = (volatile unsigned char *)&spi->SR;
	*readComplete = (unsigned short *)&spi->IFCR;

	spi->IFCR = (1  <<  9);
	//spi->CFG2 |= (1  << 22);	// MASTER = 1; SPI is acting as a master (Does not need to be set a second time)
	// Enable SPI
	spi->CR1 |= (1  <<  0); // SPE = 1;
	spi->CR1 |= (1  <<  9); // CSTART = 1;
#endif

