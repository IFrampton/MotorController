#include "LPC5502.h"

#ifndef BSP_FLASH_H
#define BSP_FLASH_H

#if defined (__cplusplus)
class BspFlash
{
	/* Define Structures */
	/* Define Variables */
	//private: static TimerCallBackInfo _timers[3];
	private: static bool _initialized;
	private: static const unsigned long FlashLocation = 0x0FE00; // This is 512 Bytes (one page) short of the end of flash for an LPC5502.
	private: static const unsigned long FlashRoot = 0x00000000; // Not using protected flash at the moment
	/* Define Functions */
	public:  static void Initialize(void);
	public:  static void WriteConfig(void);
	private: static unsigned char WritePage(unsigned long startAddress, unsigned long length, unsigned long *data);
	//public:  static void SetupFreeRunningCounter(void);
	//public:  static unsigned long inline GetFreeRunningCounter() {return 2;}
};
#endif

#endif //BSP_FLASH_H
