#include "BspFlash.h"
#include "MemoryStructure.h"

bool BspFlash::_initialized = false;

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
	unsigned char *flash = (unsigned char *)flashLocation;
	unsigned char *memory = (unsigned char *)memoryLocation;
	for(char fin = x - 4; fin < sizeof(MemoryStructure::_nvmStruct); fin++)
	{
		*(memory++) = *(flash++);
	}
	// Update Initialized Status for other function calls
	_initialized = true;
}

void BspFlash::WriteConfig()
{
	//Disable Interrupts
	NVIC_DisableIRQ(CTIMER0_IRQn);
	NVIC_DisableIRQ(CTIMER1_IRQn);
	NVIC_DisableIRQ(CTIMER2_IRQn);
	NVIC_DisableIRQ(CTIMER3_IRQn);
	NVIC_DisableIRQ(CTIMER4_IRQn);
	// Write to flash
	WritePage(FlashLocation, sizeof(MemoryStructure::_nvmStruct), (unsigned long *)&MemoryStructure::_nvmStruct);
	//Enable Interrupts
	NVIC_EnableIRQ(CTIMER0_IRQn);
	NVIC_EnableIRQ(CTIMER1_IRQn);
	NVIC_EnableIRQ(CTIMER2_IRQn);
	NVIC_EnableIRQ(CTIMER3_IRQn);
	NVIC_EnableIRQ(CTIMER4_IRQn);
}

unsigned char BspFlash::WritePage(unsigned long startAddress, unsigned long length, unsigned long *data)
{
	// Ignore LSB
	unsigned long truncatedLength = length & 0xFFFFFFF0;
	// if some bits in a word are used, all must be written
	if(length > truncatedLength)
		length += 16;
	// Address passed to function is flash relative (128-bit word width)
	FLASH->STARTA = ((startAddress - FlashRoot) >> 4);
	FLASH->STOPA = FLASH->STARTA + (length >> 4) - 1;
	// Erase Flags
	FLASH->INT_CLR_STATUS = 0xF;
	// Execute Command
	FLASH->CMD = 4; // Erase Range
	// Wait for complete (or any other flag)
	while(!FLASH->INT_STATUS)
	{
		__asm("NOP");
	}
	//Check for success
	if(!(FLASH->INT_STATUS & 0x4))
		return 0xFF;
	// Write Data
	for(unsigned char x = 0; x < ((length >> 2) - 1); x += 4)
	{
		FLASH->DATAW[0] = *(data++);
		FLASH->DATAW[1] = *(data++);
		FLASH->DATAW[2] = *(data++);
		FLASH->DATAW[3] = *(data++);
		// Erase Flags
		FLASH->INT_CLR_STATUS = 0xF;
		// Execute Command
		FLASH->CMD = 10; // Write and Program
		while(!FLASH->INT_STATUS)
		{
			__asm("NOP");
		}
		//Check for success
		if(!(FLASH->INT_STATUS & 0x4))
			return 0xFF;
		// Point to next word
		FLASH->STARTA++;
	}
	// Write Rest of Block
	for(unsigned char x = ((length >> 2) - 1); x < 128; x += 4)
	{
		FLASH->DATAW[0] = 0xFFFFFFFF;
		FLASH->DATAW[1] = 0xFFFFFFFF;
		FLASH->DATAW[2] = 0xFFFFFFFF;
		FLASH->DATAW[3] = 0xFFFFFFFF;
		// Erase Flags
		FLASH->INT_CLR_STATUS = 0xF;
		// Execute Command
		FLASH->CMD = 10; // Write and Program
		while(!FLASH->INT_STATUS)
		{
			__asm("NOP");
		}
		//Check for success
		if(!(FLASH->INT_STATUS & 0x4))
			return 0xFF;
		// Point to next word
		FLASH->STARTA++;
	}
	return 0;
}
