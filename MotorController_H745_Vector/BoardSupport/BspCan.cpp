/*
 * BspCan.cpp
 *
 *  Created on: Jan 1, 2024
 *      Author: Isaac Frampton
 */

#include "stm32h7xx.h"
#include "BspCan.h"

unsigned char BspCan::_nextBuffer[2] = {0, 0};
unsigned char BspCan::_nextHandle[2] = {0, 0};
unsigned short BspCan::_mailBoxBase[2] = {0, 0};
unsigned short BspCan::_rxBufferBase = 0;
unsigned short BspCan::_txBufferBase = 0;
char BspCan::_dwordsToCopy[16] =
{
	0, 1, 1, 1, 1, 2, 2, 2,
	2, 3, 4, 5, 6, 8, 12, 16
};

char BspCan::_bytesInMessage[16] =
{
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 12, 16, 20, 24, 32, 48, 64
};

void BspCan::Initialize(void)
{
	// Configure clock to CAN
	RCC->D2CCIP1R &= ~(3 << 28);
	RCC->D2CCIP1R |= (0 << 28); // 0 = External Oscillator, 1 = PLL1, 2 = PLL2, 3 = disabled

	// Reset CAN
	RCC->APB1HRSTR |= (1<<8);
	// Remove Reset from CAN
	RCC->APB1HRSTR &= ~(1<<8);

	// Enable CAN in high power mode
	RCC->APB1HENR |= (1 << 8);

	// Disable CAN in low power mode
	RCC->APB1HLPENR &= ~(1 << 8);
	RCC->APB1HLPENR |= (0 << 8);

	// Disable CAN for Core 1 (Core 1 is believed to be the M7 core)
	RCC_C1->AHB1ENR &= ~(1 << 8);

	// Enable CAN for Core 2 (Core 2 is believed to be the M4 core)
	RCC_C2->AHB1ENR |= (1 << 8);

	// Setup GPIO (This should be in a separate function, but is included here for now)
	RCC->AHB4ENR |= (1 << 3);
	RCC_C1->AHB4ENR &= ~(1 << 3);
	RCC_C2->AHB4ENR |= (1 << 3);
	// Setup TX
	// Set mode to alternate
	GPIOD->MODER &= ~(3 << 2);
	GPIOD->MODER |= (2 << 2);
	// Set speed to very high speed
	GPIOD->OSPEEDR |= (3 << 2);
	// Use pull down for RX, nothing for TX
	GPIOD->PUPDR &= ~(3 << 2);
	GPIOD->PUPDR |= (0 << 2);
	// Set alternate function to 9 (FDCAN)
	GPIOD->AFR[0] &= ~(0xF << 4);
	GPIOD->AFR[0] |= (9 << 4);

	// Setup RX
	GPIOD->MODER &= ~(3 << 0);
	GPIOD->MODER |= (2 << 0);
	// Set speed to very high speed
	GPIOD->OSPEEDR |= (3 << 0);
	// Use pull down for RX, nothing for TX
	GPIOD->PUPDR &= ~(3 << 0);
	GPIOD->PUPDR |= (2 << 0);
	// Set alternate function to 9 (FDCAN)
	GPIOD->AFR[0] &= ~(0xF << 0);
	GPIOD->AFR[0] |= (9 << 0);

	// Begin Initialization, set the CCE bit and the INIT bit to enable configuration
	FDCAN1->CCCR = (3<<0);

	FDCAN1->DBTP = 	(0  << 23) |	// TDC = 0; Transceiver delay compensation is disabled.
					(0  << 16) |	// DBRO = 10; Data bitrate prescaler = 0 (/ 1)
					(10 <<  8) |	// DTSEG1 = 10; Data time segment before sample point = 10 (11 clocks)
					(3  <<  4) |	// DTSEG2 = 3; Data time segment after sample point = 3 (4 clocks)
					(3  <<  0) ;	// DSJW = 3; Synchronization jump width = 3 (4 clocks)

	FDCAN1->TEST = 	(0  <<  5) |	// TX = 0; TX is controlled by the CAN core, updated at the end of the CAN bit time
					(0  <<  4) ;	// LPBK = 0; loop back mode is disabled

	FDCAN1->RWD =   0;				// WDC = 0; This disables the message RAM watchdog.

	FDCAN1->CCCR = 	(0  << 15) |	// NISO = 0; CAN FD frame format according to ISO11898-1
					(0  << 14) |	// TXP = 0; The transmit pause (two bit times after each transmission) is disabled
					(1  << 13) |	// EFBI = 1; Two consecutive dominant tq required to detect an edge for hard synchronization
					(0  << 12) |	// PXHD = 0; Protocol exception handling is disabled
					(0  <<  9) |	// BRSE = 0; Bitrate switching for transmissions is disabled
					(0  <<  8) |	// FDOE = 0; FD operation is disabled
					(0  <<  7) |	// TEST = 0; Test Mode control of TX is disabled
					(0  <<  6) |	// DAR = 0; Automatic transmission of messages that were not successfully transmitted is enabled
					(0  <<  5) |	// MON = 0; Bus monitoring mode is disabled
					(0  <<  4) |	// CSR = 0; No clock stop requested
					(0  <<  3) |	// CSA = 0; No clock stop acknowledged
					(0  <<  2) |	// ASM = 0; ASM Restricted operation mode is disabled (normal CAN operation)
					(1  <<  1) |	// CCE = 1; Configuration change is enabled (disabled below)
					(1  <<  0) ;	// INIT = 1; Initialization is started

	FDCAN1->NBTP =  (2  << 25) |	// NSJW = 2; (3 bit times, should be less than NTSEG2 above)
					(0  << 16) |	// NBRP = 0; Bitrate prescaler (oscillator frequency is divided by 1)
					(10 <<  8) |	// NTSEG1 = 10; Nominal time segment before sample point (11 clocks)
					(3  <<  0) ;	// NTSEG2 = 3; Nominal time segment after sample point (4 clocks)

	FDCAN1->TSCC = 	(0  << 16) |	// TCP = 0; (no prescaling, CAN bits / 1)
					(1  <<  0) ;	// TSS = 1; (0 = 0, 1 = TCP, 2 = TIM3, 3 = 0)

	FDCAN1->TOCC = (0xFFFF << 16) |	// TOP = 65535; Timeout period is maximum
					(0  <<  1) |	// TOS = 0; (0 = continuous operation, 1 = TX, 2 = RX FIFO 1, 3 = RX FIFO 2)
					(0  <<  0) ;	// ETOC = 0; Timeout counter is disabled

	FDCAN1->TDCR = 	(0  <<  8) |	// TDCO = 0; The transmitter delay compensation offset is ~50ns max, which is less than one clock cycle, thus it is ignored
					(0  <<  0) ;	// TDCF = 0; The transmitter delay compensation filter window length is ~100ns max, which is less than one clock cycle, thus it is ignored

	FDCAN1->IE = 	(0  << 29) |	// ARAE = 0; Access to reserved address interrupt is disabled
					(0  << 28) |	// PEDE = 0; Protocol error in data phase interrupt is disabled
					(0  << 27) |	// PEAE = 0; Protocol error in arbitration phase interrupt is disabled
					(0  << 26) |	// WDIE = 0; Watchdog interrupt is disabled
					(0  << 25) |	// BOE = 0; Bus off interrupt is disabled
					(0  << 24) |	// EWE = 0; Warning status interrupt is disabled
					(0  << 23) |	// EPE = 0; Error passive interrupt is disabled
					(0  << 22) |	// ELOE = 0; Error logging overflow interrupt is disabled
					(0  << 19) |	// DRXE = 0; Message stored to dedicated RX buffer interrupt is disabled
					(0  << 18) |	// TDOE = 0; Timeout occurred interrupt is disabled
					(0  << 17) |	// MRAFE = 0; Message RAM access failure interrupt is disabled
					(0  << 16) |	// TSWE = 0; Timestamp wraparound interrupt is disabled
					(0  << 15) |	// TEFLE = 0; TX event FIFO element lost interrupt is disabled
					(0  << 14) |	// TEFFE = 0; TX event FIFO full interrupt is disabled
					(0  << 13) |	// TEFWE = 0; TX event FIFO watermark reached interrupt is disabled
					(0  << 12) |	// TEFNE = 0; TX event FIFO new entry interrupt is disabled
					(0  << 11) |	// TFEE = 0; TX FIFO empty interrupt is disabled
					(0  << 10) |	// TCFE = 0; Transmission cancellation finished interrupt is disabled
					(0  <<  9) |	// TCE = 0; Transmission completed interrupt is disabled
					(0  <<  8) |	// HPME = 0; High priority message interrupt is disabled
					(0  <<  7) |	// RF1LE = 0; RX FIFO 1 message lost interrupt is disabled
					(0  <<  6) |	// RF1FE = 0; RX FIFO 1 full interrupt is disabled
					(0  <<  5) |	// RF1WE = 0; RX FIFO 1 watermark reached interrupt is disabled
					(0  <<  4) |	// RF1NE = 0; RX FIFO 1 new message interrupt is disabled
					(0  <<  3) |	// RF0LE = 0; RX FIFO 0 message lost interrupt is disabled
					(0  <<  2) |	// RF0FE = 0; RX FIFO 0 full interrupt is disabled
					(1  <<  1) |	// RF0WE = 1; RX FIFO 0 watermark reached interrupt is enabled
					(0  <<  0) ;	// RF0NE = 0; RX FIFO 0 new message interrupt is disabled

	FDCAN1->ILS = 	(0  << 29) |	// ARAE = 0; Access to reserved address interrupt is set to EINT0
					(0  << 28) |	// PEDE = 0; Protocol error in data phase interrupt is set to EINT0
					(0  << 27) |	// PEAE = 0; Protocol error in arbitration phase interrupt is set to EINT0
					(0  << 26) |	// WDIE = 0; Watchdog interrupt is set to EINT0
					(0  << 25) |	// BOE = 0; Bus off interrupt is set to EINT0
					(0  << 24) |	// EWE = 0; Warning status interrupt is set to EINT0
					(0  << 23) |	// EPE = 0; Error passive interrupt is set to EINT0
					(0  << 22) |	// ELOE = 0; Error logging overflow interrupt is set to EINT0
					(0  << 19) |	// DRXE = 0; Message stored to dedicated RX buffer interrupt is set to EINT0
					(0  << 18) |	// TDOE = 0; Timeout occurred interrupt is set to EINT0
					(0  << 17) |	// MRAFE = 0; Message RAM access failure interrupt is set to EINT0
					(0  << 16) |	// TSWE = 0; Timestamp wraparound interrupt is set to EINT0
					(0  << 15) |	// TEFLE = 0; TX event FIFO element lost interrupt is set to EINT0
					(0  << 14) |	// TEFFE = 0; TX event FIFO full interrupt is set to EINT0
					(0  << 13) |	// TEFWE = 0; TX event FIFO watermark reached interrupt is set to EINT0
					(0  << 12) |	// TEFNE = 0; TX event FIFO new entry interrupt is set to EINT0
					(0  << 11) |	// TFEE = 0; TX FIFO empty interrupt is set to EINT0
					(0  << 10) |	// TCFE = 0; Transmission cancellation finished interrupt is set to EINT0
					(0  <<  9) |	// TCE = 0; Transmission completed interrupt is set to EINT0
					(0  <<  8) |	// HPME = 0; High priority message interrupt is set to EINT0
					(0  <<  7) |	// RF1LE = 0; RX FIFO 1 message lost interrupt is set to EINT0
					(0  <<  6) |	// RF1FE = 0; RX FIFO 1 full interrupt is set to EINT0
					(0  <<  5) |	// RF1WE = 0; RX FIFO 1 watermark reached interrupt is set to EINT0
					(0  <<  4) |	// RF1NE = 0; RX FIFO 1 new message interrupt is set to EINT0
					(0  <<  3) |	// RF0LE = 0; RX FIFO 0 message lost interrupt is set to EINT0
					(0  <<  2) |	// RF0FE = 0; RX FIFO 0 full interrupt is set to EINT0
					(0  <<  1) |	// RF0WE = 0; RX FIFO 0 watermark reached interrupt is set to EINT0
					(0  <<  0) ;	// RF0NE = 0; RX FIFO 0 new message interrupt is set to EINT0

	FDCAN1->ILE = 	(0  <<  1) |	// EINT1 = 0; EINT1 is disabled
					(1  <<  0) ;	// EINT0 = 1; EINT0 is enabled

	FDCAN1->GFC = 	(2  <<  4) |	// ANFS = 2; Accept non matching frames standard (0 = Accept in RX FIFO 0, 1 = Accept in RX FIFO 1, 2 = reject, 3 = reject)
					(2  <<  2) |	// ANFE = 2; Accept non matching frames extended (0 = Accept in RX FIFO 0, 1 = Accept in RX FIFO 1, 2 = reject, 3 = reject)
					(0  <<  1) |	// RRFS = 0; Filter remote frames with 11-bit standard identifier
					(1  <<  0) ;	// RRFE = 1; Reject all remote frames with 29-bit extended identifier

	unsigned char lss = SUPPORTED_BUFFERS;
	_mailBoxBase[0] = 0;
	FDCAN1->SIDFC = (lss<< 16) |	// LSS = 16; List size standard: number of message filter IDs is 16
					(0  <<  2) ;	// FLSSA = 0; The filter list standard start address is at the beginning of the message RAM.

	unsigned char lse = SUPPORTED_BUFFERS;
	unsigned short adr = lss;
	_mailBoxBase[1] = adr;
	FDCAN1->XIDFC = (lse<< 16) |	// LSE = 0; List size extended: number of message filter IDs is 0
					(adr<<  2) ;	// FLESA = 0; The filter list extended start address is at the beginning of the message RAM.

	FDCAN1->XIDAM =  0x1FFFFFFF;	// EIDM = 0x1FFFFFFF; The extended ID mask is not used to filter any extended messages

	//NOTE: Not using FIFO at this time; too difficult to set up and use.
	adr += 2 * lse;
	unsigned char ffo = SUPPORTED_RX_FIFOS;
	FDCAN1->RXF0C = (0  << 31) |	// F0OM = 0; FIFO 0 operates in blocking mode
					(1  << 24) |	// F0WM = 1; Watermark level for FIFO 0 is 1 message
					(ffo<< 16) |	// F0S = 16; Size for FIFO 0 is 0 messages
					(adr<<  2) ;	// F0SA = 16; Starting address for RX FIFO 0 in message RAM is right after the standard message filters

	unsigned char elementSize = 2 + (DATA_BYTES >> 2);
	adr += ffo * elementSize; // No FIFOs used
	_rxBufferBase = adr;
	FDCAN1->RXBC = 	(adr<<  2) ;	// RBSA = 80; The RX buffers start after RX FIFO.
					// This is computed based on the size of the FIFO, which is 16 messages long
					// and the number of data bytes, which is 8 in this case, requiring 4 32-bit words.

	adr += (lss + lse) * elementSize;
	FDCAN1->RXF1C = (0  << 31) |	// F0OM = 0; FIFO 1 operates in blocking mode
					(0  << 24) |	// F0WM = 0; Watermark level for FIFO 1 is 0 messages
					(0  << 16) |	// F0S = 0; Size for FIFO 1 is 0 messages
					(adr<<  2) ;	// F0SA = 16; Starting address for RX FIFO 1 in message RAM is right after the standard message filters

	unsigned char tbs = 0;
	switch(DATA_BYTES)
	{
		case 8:
		default:
		{
			tbs = 0;
			break;
		}
		case 12:
		{
			tbs = 1;
			break;
		}
		case 16:
		{
			tbs = 2;
			break;
		}
		case 20:
		{
			tbs = 3;
			break;
		}
		case 24:
		{
			tbs = 4;
			break;
		}
		case 32:
		{
			tbs = 5;
			break;
		}
		case 48:
		{
			tbs = 6;
			break;
		}
		case 64:
		{
			tbs = 7;
			break;
		}
	}
	FDCAN1->RXESC = (tbs<<  8) |	// RBDS = 0; The CAN message buffer expects 8 bytes in each CAN message (No FD supported)
					(tbs<<  4) |	// F1DS = 0; The RX FIFO 1 expects 8 bytes of data (No support for CAN FD)
					(tbs<<  0) ;	// F0DS = 0; The RX FIFO 0 expects 8 bytes of data (No support for CAN FD)

	ffo = SUPPORTED_TX_FIFOS;
	unsigned char tqf = SUPPORTED_HANDLES;
	_txBufferBase = adr;
	FDCAN1->TXBC = 	(1  << 30) |	// TFQM = 0; The message memory acts as a TX FIFO (0 = FIFO, 1 = queue)
					(ffo<< 24) |	// TFQS = 16; The transmit FIFO size is 16 messages
					(tqf<< 16) |	// NDTB = 0; The number of dedicated transmit buffers is 0
					(adr<<  2) ;	// TBSA = 80; The transmit FIFO starts immediately after the RX FIFO

	FDCAN1->TXESC = (tbs<<  0) ;	// TBDS = 0; The transmit FIFO expects 8 Bytes per CAN message.

	// Clear Message RAM
	unsigned long *messageRam = (unsigned long *)((unsigned long)MESSAGE_RAM_LOC);
	for(long x = 48; x; x--)
	{
		*(messageRam++) = 0;
	}

	// Initialization is done, clear the CCE bit and the INIT bit to disable configuration
	FDCAN1->CCCR &= ~(3<<0);
}

void BspCan::SetupDevice(long baudRate, unsigned char device)
{
	FDCAN_GlobalTypeDef *can = FDCAN1;
	if(device)
	{
		can = FDCAN2;
	}

	// Begin Initialization, set the CCE bit and the INIT bit to enable configuration
	can->CCCR = (3<<0);

	// Nothing here for now.

	// Initialization is done, clear the CCE bit and the INIT bit to disable configuration
	can->CCCR &= ~(3<<0);
}

// We are only using buffers for this test code. Maybe we'll go down a different
// path at a later date, but the FIFOs seem rather complicated.
//char BspCan::Subscribe(unsigned long messageId, unsigned long **address, bool extended)
char BspCan::Subscribe(unsigned long messageId, bool extended)
{
	unsigned char bank = (unsigned char)extended;
	if(_nextBuffer[bank] >= SUPPORTED_BUFFERS)
	{
		return -1;
	}
	if(!extended) // standard
	{
		unsigned long writeLocation = _mailBoxBase[0] + _nextBuffer[0];
		unsigned long *messageRam = (unsigned long *)((unsigned long)MESSAGE_RAM_LOC);
		messageRam += writeLocation;
		messageId &= 0x7FF;
		unsigned char ofs = _nextBuffer[0];
		*messageRam = 	(0  << 30) |	// SFT = 0; NOTE: Ignored due to SFEC setting below (0 = range filter, 1 = Dual ID filter, 2 = Classic Filter (filter and mask), 3 = filter disabled)
						(7  << 27) |	// SFEC = 7; Stores the message into an RX buffer
				(messageId  << 16) |	// SFID1 = messageId; Stores the messageId for matching later
						(0  << 10) |	// Reserved = 0; Filter for RX buffers
						(0  <<  9) |	// SFID2[10:9] = 0; Store message into an RX buffer
						(0  <<  6) |	// SFID2[8:6] = 0; Set no Extension Interface registers
						(ofs<<  0) ;	// SFID2[5:0] = addr; offset to the Rx buffer start address for storage of a matching message
//		unsigned char elementSize = 2 + (DATA_BYTES >> 2);
//		*address = (unsigned long *)((unsigned long)MESSAGE_RAM_LOC + ((_rxBufferBase + ofs * elementSize) << 2));
	}
	else // extended
	{
		unsigned short writeLocation = _mailBoxBase[1] + (_nextBuffer[1] << 1);
		unsigned long *messageRam = (unsigned long *)((unsigned long)MESSAGE_RAM_LOC);
		messageRam += writeLocation;
		messageId &= 0x1FFFFFFF;
		*messageRam = 	((unsigned long)7 << 29) |	// SFEC = 7; Stores the message into an RX buffer
						(messageId  << 0) ;	// SFID1 = messageId; Stores the messageId for matching later
		messageRam++;
		unsigned char ofs = _nextBuffer[1] + SUPPORTED_BUFFERS;
		*messageRam = 	((unsigned long)0 << 29) |	// EFT = 0; NOTE: Ignored due to SFEC setting below (0 = range filter, 1 = Dual ID filter, 2 = Classic Filter (filter and mask), 3 = filter disabled)
						(0  << 10) |	// Reserved = 0; Filter for RX buffers
						(0  <<  9) |	// EFID2[10:9] = 0; Store message into an RX buffer
						(0  <<  6) |	// EFID2[8:6] = 0; Set no Extension Interface registers
						(ofs<<  0) ;	// EFID2[5:0] = addr; offset to the Rx buffer start address for storage of a matchign message
//		unsigned char elementSize = 2 + (DATA_BYTES >> 2);
//		*address = (unsigned long *)((unsigned long)MESSAGE_RAM_LOC + ((_rxBufferBase + ofs * elementSize) << 2));
	}
	char buffer = _nextBuffer[bank];
	_nextBuffer[bank]++;
	return buffer + bank * SUPPORTED_BUFFERS;
}

void BspCan::GetData(char handle, unsigned long *identifier, unsigned char *length, unsigned long *data, bool *extended, bool *error, unsigned short *timestamp)
{
	unsigned char elementSize = 2 + (DATA_BYTES >> 2);
	unsigned long *address = (unsigned long *)((unsigned long)MESSAGE_RAM_LOC + ((_rxBufferBase + handle * elementSize) << 2));
	*error = (*address & ((unsigned long)1 << 31));
	*extended = (*address & ((unsigned long)1 << 30));
	*identifier = *address & 0x1FFFFFFF;
	address++;
	unsigned char dlc = (*address >> 16) & 0xF;
	*length = _bytesInMessage[dlc];
	*timestamp = *address & 0xFFFF;
	address++;
	for(char x = _dwordsToCopy[dlc]; x; x--)
	{
		*(data++) = *(address++);
	}
	// Update the word to indicate that the message was received.
	unsigned long *newDat = (unsigned long *)&FDCAN1->NDAT1;
	newDat += (handle >> 5);
	handle &= 0x1F;
	*newDat |= (1 << handle);
}

void BspCan::GetData(char handle, unsigned long *identifier, unsigned char *length, unsigned long *data, bool *extended)
{
	unsigned char elementSize = 2 + (DATA_BYTES >> 2);
	unsigned long *address = (unsigned long *)((unsigned long)MESSAGE_RAM_LOC + ((_rxBufferBase + handle * elementSize) << 2));
	*extended = (*address & ((unsigned long)1 << 30));
	*identifier = *address & 0x1FFFFFFF;
	address++;
	unsigned char dlc = (*address >> 16) & 0xF;
	*length = _bytesInMessage[dlc];
	address++;
	for(char x = _dwordsToCopy[dlc]; x; x--)
	{
		*(data++) = *(address++);
	}
	// Update the word to indicate that the message was received.
	unsigned long *newDat = (unsigned long *)&FDCAN1->NDAT1;
	newDat += (handle >> 5);
	handle &= 0x1F;
	*newDat |= (1 << handle);
}

bool BspCan::CheckForNewData(char handle)
{
	if(handle < 0)
	{
		return false;
	}
	if(handle > 2 * SUPPORTED_BUFFERS)
	{
		return false;
	}
	//unsigned long *newLoc = (unsigned long *)((unsigned long)&FDCAN1->NDAT1 + (handle >> 5));
	unsigned long *newLoc = (unsigned long *)&FDCAN1->NDAT1;
	newLoc += (handle >> 5);
	handle &= 0x1F;
	unsigned long mask = (1 << handle);
	return(*newLoc & mask);
}

char BspCan::GetTxHandle(void)//bool extended)
{
	//unsigned char bank = (unsigned char)extended;
	if(_nextHandle[0] >= SUPPORTED_HANDLES)
	{
		return -1;
	}
	char handle = _nextHandle[0];
	_nextHandle[0]++;
	return handle;
}

bool BspCan::Transmit(char handle, unsigned long identifier, unsigned long *data, unsigned char len, bool extended)
{
	if(handle < 0)
	{
		return false;
	}
	if(handle > 2 * SUPPORTED_BUFFERS)
	{
		return false;
	}
	unsigned char elementSize = 2 + (DATA_BYTES >> 2);
	unsigned long writeLocation = _txBufferBase + handle * elementSize;
	unsigned long *messageRam = (unsigned long *)((unsigned long)MESSAGE_RAM_LOC);
	messageRam	+= writeLocation;
	if(!extended) // Standard
	{
		identifier &= 0x7FF;
		identifier <<= 18;
	}
	else // Extended
	{
		identifier &= 0x1FFFFFFF;
	}
	len &= 0xF;
	*(messageRam++) = 	((unsigned long)1 << 31) |	// ESI = 1; Error state indicator is always transmitted recessive
						((unsigned char)extended << 30) |	// XTD = configured; Extended Identifier
						((unsigned char)0 << 30) |	// RTR = 0; (0 = transmit data frame, 1 = transmit remote frame)
						(identifier << 0) ;	// In this case, the identifier has already been filtered.
	*(messageRam++) = 	(handle << 24) |	// MM = handle; this identifies the message.
						(0  << 23) |	// EFC = 0; Event FIFO Control (0 = don't store TX events, 1 = store TX events)
						(0  << 21) |	// FDF = 0; FD Format (0 = classic CAN format, 1 = CAN FD format)
						(0  << 20) |	// BRS = 0; Bitrate Switching (0 = CAN FD frames sent without bitrate switching, 1 = CAN FD frames sent with bitrate switching)
						(len<< 16) ;	// DLC = configured; Data length code (anything over 8 requires CAN FD)
	for(char x = _dwordsToCopy[len]; x; x--)
	{
		*(messageRam++) = *(data++);
	}

	FDCAN1->TXBAR |= (1 << handle);
	return true;
}

void BspCan::PutInTestMode(void)
{
	// Initialize
	FDCAN1->CCCR |= (1<<0);
	for(long x = 0; x< 200; x++)
	{
	}
	FDCAN1->CCCR |= (1<<1);
	for(long x = 0; x< 200; x++)
	{
	}
	FDCAN1->CCCR |= (1<<7);

	// Initialization is done, clear the CCE bit and the INIT bit to disable configuration
	//FDCAN1->CCCR &= ~(3<<0);
}

void BspCan::SetTxRegister(bool set)
{
	 FDCAN1->TEST = ((unsigned char)set) << 6;
}
