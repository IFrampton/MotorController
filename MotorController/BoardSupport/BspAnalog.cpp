#include "BspAnalog.h"

BspAnalog::AnalogConfig *BspAnalog::_config = 0;
bool BspAnalog::_initialized = false;

void BspAnalog::Initialize(void)
{
	// Enable clocks
	SYSCON->ADCCLKSEL = 0; // Use System Clock for ADC
	SYSCON->AHBCLKCTRLX[0] |= (1 << 27); // Enable ADC Clock
	// Update Initialized Status for other function calls
	// Note: This is only valid if the configuration is pointed to the correct location in NVM
	if(_config)
	{
		_initialized = true;
	}
}
