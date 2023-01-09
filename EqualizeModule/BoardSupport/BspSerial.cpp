#include "BspSerial.h"
#include "MemoryStructure.h"

bool BspSerial::_initialized = false;
unsigned char BspSerial::_transmitBuffer[11];
unsigned char BspSerial::_receiveBuffer[10];
unsigned char BspSerial::_receiveLookup[16] =
{
//	*  *  *  *  *  5  1  7  *  6  2  0  3  4  0  0
	0, 0, 0, 0, 0, 5, 1, 7, 0, 6, 2, 0, 3, 4, 0, 0
};
unsigned char BspSerial::_transmitLookup[8] =
{
	0x0B, 0x06, 0x0A, 0x0C, 0x0D, 0x05, 0x09, 0x07
};
BspDma::DmaChannelData BspSerial::_fastReference[2];
unsigned long BspSerial::_characterTimeout = 0;

void BspSerial::Initialize(void)
{
	// Disable Interrupt
	//NVIC_DisableIRQ(USART0_IRQn);
	// Enable Clocks
	SYSCON->SYSAHBCLKCTRL |= (1 << 14); // Enable USART0
	//SYSCON->UARTCLKDIV = 2; // Give the USART 48MHz
	SYSCON->UARTCLKDIV = 1; // Give the USART maximum frequency (96 MHz)

	// Setup USART
	USART0->CFG = (1 << 23)	|	// TXPOL = 1 (Invert the TX signal to only be active when transmitting)
				  (1 << 22)	|	// RXPOL = 1 (Invert the RX signal to match the hardware, which is only active when receiving)
				  (0 << 21)	|	// OEPOL = 0 (The output enable bit is not used, so the polarity doesn't matter)
				  (1 << 20)	|	// OESEL = 1 (Use the output select like RS485, endorse hardware RS485 support, even when unused)
				  (0 << 19)	|	// AUTOADDR = 0 (Do not detect an address)
				  (1 << 18)	|	// OETA = 1 (Leave the output enable asserted for 1 bit after the end of transmission)
				  (0 << 15)	|	// LOOP = 0 (Do not use loop-back)
				  (0 << 14)	|	// SYNCMST = 0 (Not a synchronous master; synchronous = SPI)
				  (0 << 12)	|	// CLKPOL = 0 (Synchronous clock polarity is normal because it is unused)
				  (0 << 11)	|	// SYNCEN = 0 (Synchronous is disabled; this would give SPI functionality)
				  (0 << 9)	|	// CTSEN = 0 (Flow control is disabled)
				  (0 << 6)	|	// STOPLEN = 0 (1 stop bit)
				  (0 << 4)	|	// PARITYSEL = 0 (No parity)
				  (1 << 2)	|	// DATALEN = 1 (8 bit data length)
				  (1 << 0)	;	// ENABLE = 1 (Enable the UART)

	USART0->CTL = (0 << 16)	|	// AUTOBAUD = 1 (Auto Baud is disabled)
				  (0 << 9)	|	// CLRCCONRX = 1 (CC is not clear on Receive)
				  (0 << 8)	|	// CC = 0 (The clock only runs when transmitting or receiving)
				  (0 << 6)	|	// TXDIS = 0 (Leave Transmit enabled)
				  (0 << 2)	|	// ADDRDET = 0 (Do not detect an address)
				  (0 << 1)	;	// TXBRKEN = 0 (Do not transmit a break character)

	USART0->INTENCLR = (1 << 16)	|	// ABERREN = 1 (Don't interrupt on Autobaud error)
					   (1 << 15)	|	// RXNOISEEN = 1 (Don't interrupt on Rx noise)
					   (1 << 14)	|	// PARITYERREN = 1 (Don't interrupt on Parity Error)
					   (1 << 13)	|	// FRAMEERREN = 1 (Don't interrupt on Frame Error)
					   (1 << 12)	|	// STARTEN = 1 (Don't interrupt on Start Bit)
					   (1 << 11)	|	// DELTARXBRKEN = 1 (Don't interrupt on Change in Break state)
					   (1 << 8)		|	// OVERRUNEN = 1 (Don't interrupt on overrun)
					   (1 << 6)		|	// TXDISEN = 1 (Don't interrupt on transmit disable)
					   (1 << 5)		|	// DELTACTSEN = 1 (Don't interrupt on Change in CTS signal)
					   (1 << 3)		|	// TXIDLEEN = 1 (Don't interrupt on Tx Idle)
					   (1 << 2)		|	// TXRDYEN = 1 (Don't interrupt on Tx Ready)
					   (1 << 0)		;	// RXRDYEN = 1 (Don't interrupt on Rx Ready)

	USART0->INTENSET = (0 << 16)	|	// ABERREN = 0 (Don't interrupt on Autobaud error)
					   (0 << 15)	|	// RXNOISEEN = 0 (Don't interrupt on Rx noise)
					   (0 << 14)	|	// PARITYERREN = 0 (Don't interrupt on Parity Error)
					   (0 << 13)	|	// FRAMEERREN = 0 (Don't interrupt on Frame Error)
					   (1 << 12)	|	// STARTEN = 1 (Interrupt on Start Bit)
					   (0 << 11)	|	// DELTARXBRKEN = 0 (Don't interrupt on Change in Break state)
					   (0 << 8)		|	// OVERRUNEN = 0 (Don't interrupt on overrun)
					   (0 << 6)		|	// TXDISEN = 0 (Don't interrupt on transmit disable)
					   (0 << 5)		|	// DELTACTSEN = 0 (Don't interrupt on Change in CTS signal)
					   (0 << 3)		|	// TXIDLEEN = 0 (Don't interrupt on Tx Idle)
					   (0 << 2)		|	// TXRDYEN = 0 (Don't interrupt on Tx Ready)
					   (0 << 0)		;	// RXRDYEN = 0 (Don't interrupt on Rx Ready)
	//USART0->OSR = 0x9;	// Sample over 10 clocks (allows 4.8Mbps)
	//USART0->OSR = 0xB;	// Sample over 12 clocks (allows 4Mbps)
	USART0->OSR = 0xF;	// Sample over 16 clocks (allows 3MBps or 6Mbps)

	// Initialize Structure (to prevent unintended execution)
	// Enable DMA for receive function
	BspDma::SetupReceiveFromPeripheral(&_fastReference[0], 0, 3, (unsigned char *)&USART0->RXDAT, &_receiveBuffer[9], 0, 10);
	//unsigned char channel, unsigned char pri, unsigned char *source, unsigned char *dest, unsigned char dataBytes, unsigned char length
	BspDma::InitiateTransferToPeripheral(&_fastReference[1], 1, 3, &_transmitBuffer[6], (unsigned char *)&USART0->TXDAT, 0, 7);

	// Compute the number of cycles for a single character
	unsigned long characterClockCycles = (SYSCON->UARTCLKDIV / SYSCON->SYSAHBCLKDIV) * (USART0->OSR + 1);
	_characterTimeout = 8 * characterClockCycles;
	// Note: The Receive DMA Re-enable flags will need to be updated based on this logic.
	BspTimer::SetupDmaResetTimer(&_fastReference[0], &_characterTimeout, EnableInterrupt);

	// setup Character Timeout indicator
	// Enable Interrupts and set priority (nothing will happen until other tasks are configured)
	NVIC_EnableIRQ(USART0_IRQn);
	NVIC_SetPriority(USART0_IRQn, 10);
	// Update Initialized Status for other function calls
	_initialized = true;
}

void BspSerial::PrepareTransmission(void)
{
#if 0
	// Word 0 indicates normal data.
	_transmitBuffer[1] = 0x0;
	unsigned short word = PrepareTransmitWord(MemoryStructure::_memStruct.AnalogInputs.Analog.RawData[0]);
	_transmitBuffer[1] = word >> 8;
	_transmitBuffer[2] = word & 0xFF;
	word = PrepareTransmitWord(MemoryStructure::_memStruct.AnalogInputs.Analog.RawData[1]);
	_transmitBuffer[3] = word >> 8;
	_transmitBuffer[4] = word & 0xFF;
	word = PrepareTransmitWord(MemoryStructure::_memStruct.AnalogInputs.Analog.RawData[3]);
	_transmitBuffer[5] = word >> 8;
	_transmitBuffer[6] = word & 0xFF;
#else
	_transmitBuffer[0] = 0x55;
	_transmitBuffer[1] = 0x55;
	_transmitBuffer[2] = 0x55;
	_transmitBuffer[3] = 0x55;
	_transmitBuffer[4] = 0x55;
	_transmitBuffer[5] = 0x55;
	_transmitBuffer[6] = 0x55;
#endif
}


void BspSerial::DummyFunction(void)
{
	//__asm("NOP");
}

extern "C"
{
void USART0_IRQHandler(void)
{
	// Clear Interrupt flag
	USART0->STAT = (1 << 12);
	USART0->INTENCLR = (1 << 12);
	// Transmit immediately (to improve timing)
	BspDma::FastReEnable(&BspSerial::_fastReference[1]);
	//USART0->TXDAT = 0x55;
	// The start bit occurs immediately preceding the first character, so set up the serial to listen
	BspDma::FastReEnable(&BspSerial::_fastReference[0]);
}
}
