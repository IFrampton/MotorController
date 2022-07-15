#include "BspPwm.h"

bool BspPwm::_initialized = false;

void BspPwm::Initialize(void)
{
	// Enable clocks
	SYSCON->SCTCLKSEL = 0; // Configure the PWM to be driven by the main processor clock
	SYSCON->AHBCLKCTRLX[1] |= (1 << 20); // Enable the Clock to the PWM
	// Update Initialized Status for other function calls
	_initialized = true;
}
