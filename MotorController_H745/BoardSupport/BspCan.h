// BspCan.h
// Header file for simplified Board support CAN features.
// Includes templates for CAN functions and inlined functions

#ifndef BSPCAN_H
#define BSPCAN_H

#define SUPPORTED_BUFFERS 16
#define SUPPORTED_HANDLES 16
#define SUPPORTED_RX_FIFOS 0
#define SUPPORTED_TX_FIFOS 32
#define DATA_BYTES 8

#define MESSAGE_RAM_LOC 0x4000AC00

#ifdef __cplusplus
class BspCan
{
	private: static unsigned char _nextBuffer[2];
	private: static unsigned char _nextHandle[2];
	private: static unsigned short _mailBoxBase[2];
	private: static unsigned short _rxBufferBase;
	private: static unsigned short _txBufferBase;
	private: static char _dwordsToCopy[16];
	private: static char _bytesInMessage[16];


	public: static void Initialize(void);
	public: static void SetupDevice(long baudRate, unsigned char device);
	public: static void PutInTestMode(void);
	public: static void SetTxRegister(bool set);
//	public: static char Subscribe(unsigned long messageId, unsigned long **address, bool extended);
	public: static char Subscribe(unsigned long messageId, bool extended);
	public: static bool CheckForNewData(char handle);
	public: static void GetData(char handle, unsigned long *identifier, unsigned char *length, unsigned long *data, bool *extended, bool *error, unsigned short *timestamp);
	public: static void GetData(char handle, unsigned long *identifier, unsigned char *length, unsigned long *data, bool *extended);
	public: static char GetTxHandle(void);
	public: static bool Transmit(char handle, unsigned long identifier, unsigned long *data, unsigned char len, bool extended);
};
#endif

#endif //BSPCAN_H
