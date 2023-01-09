#include "BspPwm.h"

void (*BspPwm::_callback)(void) = DummyFunction;
bool BspPwm::_initialized = false;

void BspPwm::Initialize(long frequency, long antiShootThrough)
{
	// Enable clocks
	SYSCON->PRESETCTRL |= (1 << 8); // Configure the PWM to be driven by the main processor clock
	SYSCON->SYSAHBCLKCTRL |= (1 << 8); // Enable the Clock to the PWM

	// Configure the PWM
	SCT0->CONFIG = 	(0 << 18)	| // AUTOLIMIT_H = 1 (Matches on Register 0 Reset the High Counter (This is not used in UNIFY mode))
					(0 << 17)	| // AUTOLIMIT_L = 1 (Matches On Register 0 Reset the Counter)
					(0 << 9)	| // INSYNC = 0 (The Inputs are not Synchronized to the clock)
					(0 << 8)	| // NORELOAD_H = 0 (Allow Reloading of high match registers from high reload registers (This is not used in UNIFY mode))
					(0 << 7)	| // NORELOAD_L = 0 (Allow Reloading of match registers from reload registers)
					(0 << 3)	| // CKSEL = 0 (Rising Edges on Input 0 clock the module (This is disabled by the CLKMODE below)
					(0 << 1)	| // CLKMODE = 0 (Clock the Module from the system clock)
					(1 << 0)	; // UNIFY = 0 (The entire module operates as a single 32-bit counter)
	SCT0->CTRL = 	(0 << 21)	| // PRE_H = 0 (No pre-scaling for high counter)
					(0 << 20)	| // BIDIR_H = 0 (The high counter reset to 0 at the limit)
					(0 << 19)	| // CLRCTR_H = 1 (Clear the high counter)
					(0 << 18)	| // HALT_H = 1 (Halt the high counter (No events possible))
					(0 << 17)	| // STOP_H = 0 (Don't stop the high counter (Events are possible, counter does not count))
					(0 << 5)	| // PRE_L = 0 (No pre-scaling for low counter)
					(0 << 4)	| // BIDIR_L = 0 (The low counter reset to 0 at the limit)
					(1 << 3)	| // CLRCTR_L = 1 (Clear the low counter)
					(1 << 2)	| // HALT_L = 1 (Halt the low counter (No events possible))
					(0 << 1)	; // STOP_L = 0 (Don't stop the low counter (Events are possible, counter does not count))
	SCT0->LIMIT = 	(1 << (16 + 12))	| // Event 12 acts as a limit for the high counter
					(1 << 12)	; // Event 12 acts as a limit for the low counter
	SCT0->HALT = 	(0 << 16)	| // No Event acts as a halt for the high counter
					(0 << 0)	; // No Event acts as a halt for the low counter
	SCT0->STOP = 	(0 << 16)	| // No Event acts as a stop for the high counter
					(0 << 0)	; // No Event acts as a stop for the low counter
	// If the two processors are to be synched, this will be the mechanism
	// Using the start instead of the limit will prevent the risk of cycle
	// completion before match condition is reached.
	SCT0->START =   (0 << 16)	| // No Event acts as a start for the high counter
					(0 << 0)	; // No Event acts as a start for the low counter

	SCT0->COUNT = 0; // Note: This is already handled by the CLRCTR_H and CLRCTR_L above.

	SCT0->STATE = (0 << 16)	| // STATE_H = 0 (The state variable for the high counter is 0 (This feature is not used)
				  (0 << 0)	; // STATE_L = 0 (The state variable for the low counter is 0 (This feature is not used)

	SCT0->REGMODE = (0 << 16)	| //REGMODE_H = 0 (All Registers are used as match registers for the high counter
					(0 << 0)	; //REGMODE_l = 0 (All Registers are used as match registers for the low counter

	SCT0->OUTPUT = (0 << 0)		; // OUT = 0 (Default outputs to off)

	SCT0->OUTPUTDIRCTRL = 0;	// The bi-directional functionality is not being used
	SCT0->RES =	(2 << 30)	| // O15RES = 2 (Clear if conflicting events occur)
				(2 << 28)	| // O14RES = 2 (Clear if conflicting events occur)
				(2 << 26)	| // O13RES = 2 (Clear if conflicting events occur)
				(2 << 24)	| // O12RES = 2 (Clear if conflicting events occur)
				(2 << 22)	| // O11RES = 2 (Clear if conflicting events occur)
				(2 << 20)	| // O10RES = 2 (Clear if conflicting events occur)
				(2 << 18)	| // O9RES = 2 (Clear if conflicting events occur)
				(2 << 16)	| // O8RES = 2 (Clear if conflicting events occur)
				(2 << 14)	| // O7RES = 2 (Clear if conflicting events occur)
				(2 << 12)	| // O6RES = 2 (Clear if conflicting events occur)
				(2 << 10)	| // O5RES = 2 (Clear if conflicting events occur)
				(2 << 8)	| // O4RES = 2 (Clear if conflicting events occur)
				(2 << 6)	| // O3RES = 2 (Clear if conflicting events occur)
				(2 << 4)	| // O2RES = 2 (Clear if conflicting events occur)
				(2 << 2)	| // O1RES = 2 (Clear if conflicting events occur)
				(2 << 0)	; // O0RES = 2 (Clear if conflicting events occur)

	SCT0->DMAREQ0 = 0;	// DMA is not used.
	SCT0->DMAREQ1 = 0;	// DMA is not used.
	SCT0->EVEN = (1 << 12); // Event 12 (rollover) causes an interrupt

	long counts = (SystemCoreClock / frequency) - 1;
	// Setup Match Registers with defaults
	SCT0->MATCH[0] = antiShootThrough;
	// This gives a 180° signal
	SCT0->MATCH[1] = counts;
	// Output 1 = High Side Switch for Phase A
	SCT0->MATCH[2] = 0; // Turn On
	SCT0->MATCH[3] = 0; // Turn Off
	// Output 2 = High Side Switch for Phase B
	SCT0->MATCH[4] = 0; // Turn On
	SCT0->MATCH[5] = 0; // Turn Off
	// Output 3 = High Side Switch for Phase C
	SCT0->MATCH[6] = 0; // Turn On
	SCT0->MATCH[7] = 0; // Turn Off


	// Three Channels (outputs 0, 2, and 4), are enabled at AST time
	SCT0->MATCHREL[0] = antiShootThrough;
	// Three Channels (outputs 1, 3, and 5) are disabled at Rollover
	SCT0->MATCHREL[1] = counts;
	// Outputs 0,1 = Isolated Side of DAB
	SCT0->MATCHREL[2] = 0; // Turn 0 Off and 1 On
	SCT0->MATCHREL[3] = 0; // Turn On
	SCT0->MATCHREL[4] = 0; // Turn Off
	SCT0->MATCHREL[5] = 0; // Turn On
	// Outputs 2,3 = Local Side of DAB
	SCT0->MATCHREL[6] = 0; // Turn 2 Off and 3 On
	// Outputs 4,5 = Boost Converter
	SCT0->MATCHREL[7] = 0; // Turn 4 Off and 5 On

	// Setup Events
	SCT0->EV[0].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[0].CTRL = (0 << 21)	| // DIRECTION = 0 (The behavior is independent of direction)
					   (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					   (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					   (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					   (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					   (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					   (0 << 6)		| // IOSEL = 0 (Output SCT_PWM0 is Output 1)
					   (1 << 5)		| // OUTSEL = 1 (Select Outputs (the PWM is driving 6 outputs))
					   (0 << 4)		| // HEVENT = 0 (Use the unified or low side match)
					   (2 << 0)		; // MATCHSEL = 2 (Select Match Register 2)
	SCT0->EV[1].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[1].CTRL = (0 << 21)	| // DIRECTION = 0 (The behavior is independent of direction)
					   (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					   (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					   (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					   (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					   (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					   (0 << 6)		| // IOSEL = 0 (Output SCT_PWM0 is Output 1)
					   (1 << 5)		| // OUTSEL = 1 (Select Outputs (the PWM is driving 6 outputs))
					   (0 << 4)		| // HEVENT = 0 (Use the unified or low side match)
					   (3 << 0)		; // MATCHSEL = 3 (Select Match Register 3)
	SCT0->EV[2].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[2].CTRL = (0 << 21)	| // DIRECTION = 0 (The behavior is independent of direction)
					   (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					   (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					   (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					   (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					   (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					   (1 << 6)		| // IOSEL = 0 (Output SCT_PWM1 is Output 2)
					   (1 << 5)		| // OUTSEL = 1 (Select Outputs (the PWM is driving 6 outputs))
					   (0 << 4)		| // HEVENT = 0 (Use the unified or low side match)
					   (4 << 0)		; // MATCHSEL = 4 (Select Match Register 4)
	SCT0->EV[3].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[3].CTRL = (0 << 21)	| // DIRECTION = 0 (The behavior is independent of direction)
					   (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					   (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					   (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					   (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					   (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					   (1 << 6)		| // IOSEL = 0 (Output SCT_PWM1 is Output 2)
					   (1 << 5)		| // OUTSEL = 1 (Select Outputs (the PWM is driving 6 outputs))
					   (0 << 4)		| // HEVENT = 0 (Use the unified or low side match)
					   (5 << 0)		; // MATCHSEL = 5 (Select Match Register 5)
	SCT0->EV[4].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[4].CTRL = (0 << 21)	| // DIRECTION = 0 (The behavior is independent of direction)
					   (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					   (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					   (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					   (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					   (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					   (2 << 6)		| // IOSEL = 0 (Output SCT_PWM2 is Output 3)
					   (1 << 5)		| // OUTSEL = 1 (Select Outputs (the PWM is driving 6 outputs))
					   (0 << 4)		| // HEVENT = 0 (Use the unified or low side match)
					   (6 << 0)		; // MATCHSEL = 6 (Select Match Register 6)
	SCT0->EV[5].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[5].CTRL = (0 << 21)	| // DIRECTION = 0 (The behavior is independent of direction)
					   (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					   (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					   (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					   (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					   (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					   (2 << 6)		| // IOSEL = 0 (Output SCT_PWM2 is Output 3)
					   (1 << 5)		| // OUTSEL = 1 (Select Outputs (the PWM is driving 6 outputs))
					   (0 << 4)		| // HEVENT = 0 (Use the unified or low side match)
					   (7 << 0)		; // MATCHSEL = 7 (Select Match Register 7)
	SCT0->EV[6].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[6].CTRL = (0 << 21)	| // DIRECTION = 0 (The behavior is independent of direction)
					   (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					   (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					   (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					   (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					   (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					   (3 << 6)		| // IOSEL = 0 (Output SCT_PWM3 is Output 4)
					   (1 << 5)		| // OUTSEL = 1 (Select Outputs (the PWM is driving 6 outputs))
					   (0 << 4)		| // HEVENT = 0 (Use the unified or low side match)
					   (8 << 0)		; // MATCHSEL = 8 (Select Match Register 8)
	SCT0->EV[7].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[7].CTRL = (0 << 21)	| // DIRECTION = 0 (The behavior is independent of direction)
					   (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					   (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					   (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					   (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					   (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					   (3 << 6)		| // IOSEL = 0 (Output SCT_PWM3 is Output 4)
					   (1 << 5)		| // OUTSEL = 1 (Select Outputs (the PWM is driving 6 outputs))
					   (0 << 4)		| // HEVENT = 0 (Use the unified or low side match)
					   (9 << 0)		; // MATCHSEL = 9 (Select Match Register 9)
#if 0
	SCT0->EV[8].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[8].CTRL = (0 << 21)	| // DIRECTION = 0 (The behavior is independent of direction)
					   (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					   (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					   (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					   (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					   (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					   (4 << 6)		| // IOSEL = 0 (Output SCT_PWM4 is Output 5)
					   (1 << 5)		| // OUTSEL = 1 (Select Outputs (the PWM is driving 6 outputs))
					   (0 << 4)		| // HEVENT = 0 (Use the unified or low side match)
					   (10 << 0)	; // MATCHSEL = 10 (Select Match Register 10)
	SCT0->EV[9].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[9].CTRL = (0 << 21)	| // DIRECTION = 0 (The behavior is independent of direction)
					   (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					   (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					   (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					   (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					   (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					   (4 << 6)		| // IOSEL = 0 (Output SCT_PWM4 is Output 5)
					   (1 << 5)		| // OUTSEL = 1 (Select Outputs (the PWM is driving 6 outputs))
					   (0 << 4)		| // HEVENT = 0 (Use the unified or low side match)
					   (11 << 0)	; // MATCHSEL = 11 (Select Match Register 11)
	SCT0->EV[10].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[10].CTRL = (0 << 21)	| // DIRECTION = 0 (The behavior is independent of direction)
					    (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					    (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					    (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					    (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					    (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					    (5 << 6)	| // IOSEL = 0 (Output SCT_PWM5 is Output 6)
					    (1 << 5)	| // OUTSEL = 1 (Select Outputs (the PWM is driving 6 outputs))
					    (0 << 4)	| // HEVENT = 0 (Use the unified or low side match)
					    (12 << 0)	; // MATCHSEL = 12 (Select Match Register 12)
	SCT0->EV[11].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[11].CTRL = (0 << 21)| // DIRECTION = 0 (The behavior is independent of direction)
					    (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					    (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					    (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					    (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					    (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					    (5 << 6)	| // IOSEL = 5 (Output SCT_PWM5 is Output 6)
					    (1 << 5)	| // OUTSEL = 1 (Select Outputs (the PWM is driving 6 outputs))
					    (0 << 4)	| // HEVENT = 0 (Use the unified or low side match)
					    (13 << 0)	; // MATCHSEL = 13 (Select Match Register 13)

	SCT0->EV[12].STATE = 0xFFFFFFF;	  // Enable in all States
	SCT0->EV[12].CTRL = (0 << 21)	| // DIRECTION = 0 (The behavior is independent of direction)
					    (0 << 20)	| // MATCHMEM = 0 (The event only occurs when the counter matches the match value exactly)
					    (0 << 15)	| // STATEEV = 0 (States are not used for this logic)
					    (0 << 14)	| // STATELD = 0 (States are not used for this logic)
					    (1 << 12)	| // COMBMODE = 1 (Only the match event is used)
					    (0 << 10)	| // IOCOND = 0 (LOW (this is unused))
					    (6 << 6)	| // IOSEL = 0 (Input 0 doesn't really do anything)
					    (1 << 5)	| // OUTSEL = 6 (Select Outputs (This is just for the interrupt))
					    (0 << 4)	| // HEVENT = 0 (Use the unified or low side match)
					    (0 << 0)	; // MATCHSEL = 0 (Select Match Register 0)
#endif

	// Setup Outputs
	SCT0->OUT[0].SET = (1 << 0);
	SCT0->OUT[0].CLR = (1 << 1);
	SCT0->OUT[1].SET = (1 << 2);
	SCT0->OUT[1].CLR = (1 << 3);
	SCT0->OUT[2].SET = (1 << 4);
	SCT0->OUT[2].CLR = (1 << 5);
	SCT0->OUT[3].SET = (1 << 6);
	SCT0->OUT[3].CLR = (1 << 7);
	SCT0->OUT[4].SET = (1 << 8);
	SCT0->OUT[4].CLR = (1 << 9);
	SCT0->OUT[5].SET = (1 << 10);
	SCT0->OUT[5].CLR = (1 << 11);

	SCT0->CTRL = 	(0 << 21)	| // PRE_H = 0 (No pre-scaling for high counter)
					(0 << 20)	| // BIDIR_H = 0 (The high counter reset to 0 at the limit)
					(0 << 19)	| // CLRCTR_H = 1 (Clear the high counter)
					(0 << 18)	| // HALT_H = 1 (Halt the high counter (No events possible))
					(0 << 17)	| // STOP_H = 0 (Don't stop the high counter (Events are possible, counter does not count))
					(0 << 5)	| // PRE_L = 0 (No pre-scaling for low counter)
					(0 << 4)	| // BIDIR_L = 0 (The low counter reset to 0 at the limit)
					(0 << 3)	| // CLRCTR_L = 1 (Clear the low counter)
					(0 << 2)	| // HALT_L = 1 (Halt the low counter (No events possible))
					(0 << 1)	; // STOP_L = 0 (Don't stop the low counter (Events are possible, counter does not count))

	NVIC_EnableIRQ(SCT0_IRQn);
	NVIC_SetPriority(SCT0_IRQn, 9);

	// Update Initialized Status for other function calls
	_initialized = true;
}

void BspPwm::DummyFunction(void)
{
	//__asm("NOP");
}

extern "C"
{
void SCT0_IRQHandler(void)
{
	(*BspPwm::_callback)();
	// Clear Interrupt
	SCT0->EVFLAG = 0xFFFFFFFF;
}
}
