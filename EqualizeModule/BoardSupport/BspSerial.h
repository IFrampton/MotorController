#include "LPC822.h"
#include "BspDma.h"

#ifndef BSP_SERIAL_H
#define BSP_SERIAL_H

#if defined (__cplusplus)
class BspSerial
{
	/* Define Structures */

	/* Define Variables */
	private: static bool _initialized;
	private: static unsigned char _transmitBuffer[11];
	private: static unsigned char _receiveBuffer[10];
	private: static unsigned char _receiveLookup[16];
	private: static unsigned char _transmitLookup[8];
	public:  static BspDma::DmaChannelData _fastReference[2];
	private: static unsigned long _characterTimeout;

	/* Define Functions */
	public:  static void Initialize(void);

	public:  static void PrepareTransmission(void);
	public:  static void Transmit6Bytes(void);

	// Decode receive information (K.28 zero DC encoded) to real data
	// Input = 8 bits in a received byte
	// Output = 6 bits of decoded information
	private: static unsigned char InterpretReceivedByte(unsigned char incomingByte)
	{
		register unsigned char *lookup = _receiveLookup;
		unsigned char workingNibble = incomingByte >> 4;
		unsigned char result = *(lookup + workingNibble) << 3;
		// the second nibble is always inverted
		workingNibble = ~incomingByte & 0xF;
		result += *(lookup + workingNibble);
		return result;
	}
	// Decode receive information (K.28 zero DC offset encoded) to real data
	// Input = 16 bits in two received bytes
	// Output = 12 bits of decoded information in a word
	private: static unsigned short InterpretReceivedWord(unsigned short incomingWord)
	{
		register unsigned char *lookup = _receiveLookup;
		unsigned char workingNibble = incomingWord >> 12;
		unsigned char result = *(lookup + workingNibble) << 9;
		// the second nibble is always inverted
		workingNibble = (~incomingWord >> 8) & 0xF;
		result += *(lookup + workingNibble) << 6;
		workingNibble = (incomingWord >> 4) & 0xF;
		result += *(lookup + workingNibble) << 3;
		// the second nibble is always inverted
		workingNibble = ~incomingWord & 0xF;
		result += *(lookup + workingNibble);
		return result;
	}
	// Encode internal information to K.28 (zero DC offset) for transmission
	// Input = 6 bits of information
	// Output = 6 bits of encoded information
	private: static unsigned char PrepareTransmitByte(unsigned char outgoingByte)
	{
		register unsigned char *lookup = _transmitLookup;
		unsigned char working3bits = (outgoingByte >> 3) & 0x7;
		unsigned char result = *(lookup + working3bits) << 4;
		working3bits = outgoingByte & 0x7;
		// the second nibble is always inverted
		result += ~(*(lookup + working3bits)) & 0xF;
		return result;
	}
	// Encode internal information to K.28 (zero DC offset) for transmission
	// Input = 12 bits of information
	// Output = 16 bits of encoded information
	private: static unsigned short PrepareTransmitWord(unsigned short outgoingWord)
	{
		register unsigned char *lookup = _transmitLookup;
		unsigned char working3bits = (outgoingWord >> 9) & 0x7;
		unsigned short result = *(lookup + working3bits) << 12;
		working3bits = (outgoingWord >> 6) & 0x7;
		// the second nibble is always inverted
		result += ~(*(lookup + working3bits) & 0xF) << 8;
		working3bits = (outgoingWord >> 3) & 0x7;
		result += *(lookup + working3bits) << 4;
		working3bits = outgoingWord & 0x7;
		// the second nibble is always inverted
		result += ~(*(lookup + working3bits)) & 0xF;
		return result;
	}
	public:  static void EnableInterrupt(void)
	{
		USART0->STAT = (1 << 12);
		USART0->INTENSET = (1 << 12);
	}
	private: static void DummyFunction(void);
};
#endif

#endif //BSP_SERIAL_H
