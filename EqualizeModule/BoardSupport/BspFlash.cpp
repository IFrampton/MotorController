#include "BspFlash.h"
#include "MemoryStructure.h"

bool BspFlash::_initialized = false;
// Provide a data structure to pass data in and out of the flash write routine in ROM
unsigned long BspFlash::_flashData[5];
unsigned long BspFlash::_flashResponse[5];
// Locate the function to actually reference the flash routines
void (*BspFlash::FlashFunction)(unsigned long *, unsigned long *) = (void (*)(unsigned long *, unsigned long *))0x1FFF1FF1;

void BspFlash::Initialize(void)
{
	// Read Data
	long *flashLocation = (long *)FlashLocation;
	long *memoryLocation = (long *)&MemoryStructure::_nvmStruct;
	unsigned int x;
	for(x = 0; x < sizeof(MemoryStructure::_nvmStruct); x += 4)
	{
		*(memoryLocation++) = *(flashLocation++);
	}
	// finalize the transfer (the total data length may not be a multiple of 4
	// bytes)
	//unsigned char *flash = (unsigned char *)flashLocation;
	//unsigned char *memory = (unsigned char *)memoryLocation;
	//if((x - 4) < sizeof(MemoryStructure::_nvmStruct))
	//{
	//	for(char fin = x - 4; fin < sizeof(MemoryStructure::_nvmStruct); fin++)
	//	{
	//		*(memory++) = *(flash++);
	//	}
	//}
	// Make sure that the ROM is powered up for use.
	SYSCON->SYSAHBCLKCTRL |= (1 << 1);
	SYSCON->PDRUNCFG &= ~(1 << 1);
	FLASH_CTRL->FLASHCFG = (1 << 0); // FLASHTIM = 1 (2 wait states)
	// Update Initialized Status for other function calls
	_initialized = true;
}

void BspFlash::WriteConfig()
{
	//Disable Interrupts
	NVIC_DisableIRQ(MRT0_IRQn);
	NVIC_DisableIRQ(ADC0_SEQA_IRQn);
	NVIC_DisableIRQ(SCT0_IRQn);
	// Write to flash
	WritePage(FlashLocation, sizeof(MemoryStructure::_nvmStruct), (unsigned long *)&MemoryStructure::_nvmStruct);
	//Enable Interrupts
	NVIC_EnableIRQ(SCT0_IRQn);
	NVIC_EnableIRQ(ADC0_SEQA_IRQn);
	NVIC_EnableIRQ(MRT0_IRQn);
}

unsigned char BspFlash::WritePage(unsigned long startAddress, unsigned long length, unsigned long *data)
{
	// Ignore LSB
	unsigned long truncatedLength = length & 0xFFFFFFFC;
	// if some bits in a word are used, all must be written
	if(length > truncatedLength)
		length += 4;
	unsigned long startPage = startAddress >> 6;
	unsigned long startSector = startAddress >> 10;
	// We care about page length, not byte length
	unsigned short pages = length >> 6;
	// Prepare sector
	// Address passed to function is flash relative (128-bit word width)
	_flashData[0] = 50; // Erase Flash Page
	_flashData[1] = startSector; // First Sector
	_flashData[2] = _flashData[1] + (pages >> 4); // Last Sector (one sector will still be erased if this matches Start sector)
	_flashData[3] = 0; // Defined to be empty
	// Prepare Flash Sector
	FlashFunction(_flashData, _flashResponse);
	//Check for success
	if(_flashResponse[0])
		return 0xFF;
	// Erase Page
	// Address passed to function is flash relative (128-bit word width)
	_flashData[0] = 59; // Erase Flash Page
	_flashData[1] = startPage; // First Page
	_flashData[2] = _flashData[1] + (pages); // Last Page(one sector will still be erased if this matches Start sector)
	_flashData[3] = 0; // Defined to be empty
	// Erase Flash Page
	FlashFunction(_flashData, _flashResponse);
	//Check for success
	if(_flashResponse[0])
		return 0xFF;
	// Prepare sector
	// Address passed to function is flash relative (128-bit word width)
	_flashData[0] = 50; // Erase Flash Page
	_flashData[1] = startSector; // First Sector
	_flashData[2] = _flashData[1] + (pages >> 4); // Last Sector (one sector will still be erased if this matches Start sector)
	_flashData[3] = 0; // Defined to be empty
	// Prepare Flash Sector
	FlashFunction(_flashData, _flashResponse);
	//Check for success
	if(_flashResponse[0])
		return 0xFF;
	// Write Data
	for(unsigned short x = 0; x < (length - 1); x += 64)
	{
		_flashData[0] = 51; // Copy RAM to flash
		_flashData[1] = x + (startAddress & 0xFFFFFFC0); // Beginning location must be on a 64-byte boundary
		_flashData[2] = x + (unsigned long)data; // The data location
		_flashData[3] = (((length - x) + 63) & 0xFFFFFFC0); // Length must be at least 64
		_flashData[4] = 0; // Defined to be empty
		// Write Flash Data
		FlashFunction(_flashData, _flashResponse);
		//Check for success
		if(_flashData[0])
			return 0xFF;
	}
	return 0;
}
