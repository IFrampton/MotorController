#include "LPC5502.h"

#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#if defined (__cplusplus)
class BspGpio
{
	/* Define Enumerated Types */
	/* Define Structures */
	public: struct GpioRegisters
	{
		unsigned long Mask;
		//unsigned long volatile *DirectionSet;
		unsigned long volatile *Set;
		unsigned long volatile *Clear;
		unsigned long volatile *Get;
	};

	/* Define Variables */
	private: static GpioRegisters _gpio[8];
	private: static unsigned char _nextIo;
	private: static bool _initialized;
	/* Define Functions */
	public:  static void Initialize(void);
	public:  static unsigned char SetupDigitalInput(unsigned char port, unsigned char pin);
	public:  static unsigned char SetupDigitalOutput(unsigned char port, unsigned char pin);
	public:  static void SetupGeneric(unsigned char port, unsigned char pin, unsigned char mux, bool pullup = false, bool pulldown = false, bool analog = false);
	public:  static void On(unsigned char index) {*_gpio[index].Set = _gpio[index].Mask;}
	public:  static void Off(unsigned char index) {*_gpio[index].Clear = _gpio[index].Mask;}
	public:  static bool Read(unsigned char index) {return (*_gpio[index].Get & _gpio[index].Mask);}
};
extern "C"
{
	int main(void);
}
#endif

#endif //BSP_GPIO_H
