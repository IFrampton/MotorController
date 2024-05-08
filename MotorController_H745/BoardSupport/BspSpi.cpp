/*
 * BspSpi.cpp
 *
 *  Created on: Jan 12, 2024
 *      Author: Isaac Frampton
 */

#include "BspClock.h"
#include "BspSpi.h"


char BspSpi::Initialize(char port, unsigned long bitRate, volatile unsigned short **dataReg, volatile unsigned char **newDataFlag, unsigned short **readComplete)
{
	RCC->D2CCIP1R &= ~(3 << 12);
	RCC->D2CCIP1R |= (1 << 12); // use pll2_p_clk (which is unchanged with CPU speed)
	SPI_TypeDef *spi = SPI1;
	// Turn on the kernel clock to the peripheral
	switch(port)
	{
		default:
		{
			return -1;
		}
		case 1:
		{
			spi = SPI1;
			// Remove Reset
			RCC->APB2RSTR &= ~(1 << 12);
			// Enable
			RCC->APB2ENR |= (1 << 12);
			RCC_C2->APB2ENR |= (1 << 12);
			break;
		}
		case 2:
		{
			spi = SPI2;
			// Remove Reset
			RCC->APB1LRSTR &= ~(1 << 14);
			// Enable
			RCC->APB1LENR |= (1 << 14);
			RCC_C2->APB1LENR |= (1 << 14);
			Initialize_SystemConfig();
			break;
		}
		case 3:
		{
			spi = SPI3;
			// Remove Reset
			RCC->APB1LRSTR &= ~(1 << 15);
			// Enable
			RCC->APB1LENR |= (1 << 15);
			RCC_C2->APB1LENR |= (1 << 15);
			break;
		}
		case 4:
		{
			spi = SPI4;
			// Remove Reset
			RCC->APB2RSTR &= ~(1 << 13);
			// Enable
			RCC->APB2ENR |= (1 << 13);
			RCC_C2->APB2ENR |= (1 << 13);
			break;
		}
		case 5:
		{
			spi = SPI5;
			// Remove Reset
			RCC->APB2RSTR &= ~(1 << 20);
			// Enable
			RCC->APB2ENR |= (1 << 20);
			RCC_C2->APB2ENR |= (1 << 20);
			break;
		}
		case 6:
		{
			spi = SPI6;
			// Remove Reset
			RCC->APB4RSTR &= ~(1 << 5);
			// Enable
			RCC->APB4ENR |= (1 << 5);
			RCC_C2->APB4ENR |= (1 << 5);
			break;
		}
	}

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
				(7 <<  4)	|	// MIDI = 7; Master Inter-Data Idleness (no extra delay)
				(0  <<  0)	;	// MSSI = 0; Master SS idleness (no extra delay)
	spi->IER = 0;	// No interrupts supported
	spi->CRCPOLY = 0;	// No CRC is used, therefore, no polynomial is required
	//spi->TXCRC = 0;	// No CRC is used, therefore, no reading of the CRC is required
	//spi->RXCRC = 0;	// No CRC is used, therefore, no reading of the CRC is required
	spi->UDRDR = 0xDEADBEEF;	// Send oxDEADBEEF if there is an underrun (this is never used because this device is operating as a master).
	spi->I2SCFGR = 	(1  << 25)	|	// MCKOE = 1; Master clock output is enabled
					(0  << 24)	|	// ODD = 0;	Real divider value is I2SDIV * 2
					(7  << 16)	|	// I2SDIV = 5; Real divider value is I2SDIV * 2 = 10
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
	return 0;
}

void BspSpi::Initialize_SystemConfig(void)
{
	// Remove reset
	RCC->APB4RSTR &= ~(1 << 1);
	// Enable Clock
	RCC->APB4ENR |= (1 << 1);
	RCC_C2->APB4ENR |= (1 << 1);
	// Disable in low power mode
	RCC->APB4LPENR &= ~(1 << 1);

	// Connect Analog switches
	SYSCFG->PMCR =  (0  << 27)	|	// PC3SO = 0; PC3 Switch Open (0 = closed, PC3_C = PC3)
					(0  << 26)	|	// PC2SO = 0; PC2 Switch Open (0 = closed, PC2_C = PC2)
					(0  << 26)	|	// PA1SO = 0; PA1 Switch Open (0 = closed, PA1_C = PA1)
					(0  << 26)	|	// PA0SO = 0; PA0 Switch Open (0 = closed, PA0_C = PA0)
					(0  << 21)	|	// EPIS = 0; Ethernet PHY Interface Selection (0 = MII)
					(1  <<  9)	|	// BOOSTVDDSEL = 1; Analog switch supply voltage selection (VDD/VDDS/booster)(1 = Vdd selected)
					(0  <<  8)	|	// BOOSTE = 1; Booster Enable (1 = Booster is enabled)
					(0  <<  7)	|	// PB9FMP = 0; PB(9) FM+ (0 = disabled)
					(0  <<  6)	|	// PB8FMP = 0; PB(8) FM+ (0 = disabled)
					(0  <<  5)	|	// PB7FMP = 0; PB(7) FM+ (0 = disabled)
					(0  <<  4)	|	// PB6FMP = 0; PB(6) FM+ (0 = disabled)
					(0  <<  3)	|	// I2C4FMP = 0; I2C4 FM+ (0 = disabled)
					(0  <<  2)	|	// I2C3FMP = 0; I2C3 FM+ (0 = disabled)
					(0  <<  1)	|	// I2C2FMP = 0; I2C2 FM+ (0 = disabled)
					(0  <<  0)	;	// I2C1FMP = 0; I2C1 FM+ (0 = disabled)
}
