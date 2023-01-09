#include "LPC822.h"

#ifndef BSP_DMA_H
#define BSP_DMA_H

#if defined (__cplusplus)
class BspDma
{
	/* Define Structures */
	enum Channels
	{
		UART0_RX,
		UART0_TX,
		RX_CHARACTER_TIMEOUT,
		SPARE,
		NUMBER_OF_CHANNELS
	};
	public: struct DmaChannelData
	{
		unsigned long *Location;
		unsigned long Data;
	};
	/* Define Variables */
	private: static unsigned char _nextChannel;
	private: static unsigned long _descriptorTable[NUMBER_OF_CHANNELS][4];
	private: static bool _initialized;
	/* Define Functions */
	public:  static void Initialize(void);
	public:  static void SetupReceiveFromPeripheral(DmaChannelData *data, unsigned char channel, unsigned char pri, unsigned char *source, unsigned char *dest, unsigned char dataBytes, unsigned char length, bool reArm = false);
	public:  static void InitiateTransferToPeripheral(DmaChannelData *data, unsigned char channel, unsigned char pri, unsigned char *source, unsigned char *dest, unsigned char dataBytes, unsigned char length, bool reArm = false);
	public:  static void LinkAdditionalTransferToPeripheral(DmaChannelData *data, unsigned char channel, unsigned char pri, unsigned char *source, unsigned char *dest, unsigned char dataBytes, unsigned char length, bool reArm);
	public:  static void inline ReEnable(unsigned char channel, unsigned char length) {DMA0->CHANNEL[channel].XFERCFG |= ((length - 1) << 16);}
	public:  static void inline FastReEnable(DmaChannelData *channel) { *channel->Location = channel->Data;}
};
#endif

#endif //BSP_DMA_H
