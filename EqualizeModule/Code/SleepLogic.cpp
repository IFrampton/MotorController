#include "SleepLogic.h"

unsigned char SleepLogic::_wakeupReason = 0;
bool SleepLogic::_lowBatteryCondition = false;

void SleepLogic::Initialize()
{
	_wakeupReason = RecentPowerup;
}

// Determines if the processor should go to sleep. This is called once per second from the low priority timer.
// The sleeping criteria are:
// * The cell state received from the main processor is none of the following:
//   - Discharging
//   - Charging
// * The main processor equalize current demand is 0
// * The main processor has not called for equalize current for a configurable time delay
// * The processor has been awake for a configurable time
// * The battery voltage is below a configurable threshold
void SleepLogic::CheckSleep()
{
}

// NOTE: This routine is called from the CheckWake function, which is called in 2 places:
// * The Self Wakeup Timer (WKT)
// * The USART Receive routine
// The reason for two means to wake up is that there are two different conditions for the board to wake up:

void SleepLogic::Wake( unsigned char wakeReason)
{
}

