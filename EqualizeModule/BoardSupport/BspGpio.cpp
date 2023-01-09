#include "BspGpio.h"

//The awesome layout of this processor does not require this
BspGpio::GpioRegisters BspGpio::_gpio[8];
unsigned char BspGpio::_nextIo;
bool BspGpio::_initialized = false;

void BspGpio::Initialize(void)
{
	// Enable clocks
	SYSCON->SYSAHBCLKCTRL |= (1 << 6); // Enable GPIO Clock
	// Update Initialized Status for other function calls
	// Note: This is only valid if the configuration is pointed to the correct location in NVM
}

unsigned char BspGpio::SetupDigitalInput(unsigned char port, unsigned char pin)
{
	// Make sure that we aren't out of IO
	if(_nextIo >= sizeof(_gpio) / sizeof(GpioRegisters))
		return 0xFF;
	port &= 1;
	pin &= 31;
	// Configure the pin as a GPIO
	SetupGeneric(port, pin, 0xFF);
	_gpio[_nextIo].Mask = 1 << pin;
	_gpio[_nextIo].Set = GPIO->SET + port;
	_gpio[_nextIo].Clear = GPIO->CLR + port;
	_gpio[_nextIo].Get = GPIO->CLR + port;
	// Set as input
	GPIO->DIR[port] &= ~_gpio[_nextIo].Mask;
	unsigned char io = _nextIo;
	_nextIo++;
	return io;
}

unsigned char BspGpio::SetupDigitalOutput(unsigned char port, unsigned char pin)
{
	// Make sure that we aren't out of IO
	if(_nextIo >= sizeof(_gpio) / sizeof(GpioRegisters))
		return 0xFF;
	port &= 1;
	pin &= 31;
	// Configure the pin as a GPIO
	SetupGeneric(port, pin, 0xFF);
	_gpio[_nextIo].Mask = 1 << pin;
	_gpio[_nextIo].Set = GPIO->SET + port;
	_gpio[_nextIo].Clear = GPIO->CLR + port;
	_gpio[_nextIo].Get = GPIO->CLR + port;
	// Set as output
	GPIO->DIR[port] |= _gpio[_nextIo].Mask;
	unsigned char io = _nextIo;
	_nextIo++;
	return io;
}
void BspGpio::SetupGeneric(unsigned char port, unsigned char pin, unsigned char mux, bool pullup, bool pulldown, bool analog, unsigned char anInput)
{
	port &= 1;
	pin &= 31;
	mux &= 63;
	unsigned long *location = (unsigned long *)IOCON;
	location += port * 32 + pin;
	//Note: If an input that does not support analog is selected as analog, results will be undetermined
	unsigned long infoToWrite = (0 << 13)		| //CLK_DIV = 0 (No clock divider)
								(0 << 11)		| //S_MODE = 0 (Ignore Input Filter)
								(0 << 10)		| //OD = 0 (Open Drain mode is disabled)
								(0 << 6)		| //INVERT = 0 (Do not invert pin)
								(0 << 5)		| //HYS = 0 (No Hysteresis)
								(pullup << 4)	| //MODEHb = ? (pull up resistor is enabled)
								(pulldown << 3)	| //MODE = ? (pull down resistor is enabled)
								(0 << 0)		; //FUNC = ? (pin function is set above)
	// Handle the case where the pins require extra information (port 0, pin 13 and pin 14)
	//if(!port && ((pin == 13) || (pin == 14)))
	//{
	//	infoToWrite |= (1 << 12) + (1 << 14);
	//}
	if(analog)
	{
		unsigned long mask = 1 << (13 + anInput);
		SWM0->PINENABLE0 &= ~mask;
	}
	else
	{
		SWM0->PINASSIGN_DATA[mux>>2] &= ~(0xFF << ((mux & 0x3) << 3));
		SWM0->PINASSIGN_DATA[mux>>2] |= (pin << ((mux & 0x3) << 3));
	}
	*location = infoToWrite;

}
