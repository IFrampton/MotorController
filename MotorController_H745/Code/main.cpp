/**
  ******************************************************************************
  * @file    BSP/CM7/Src/main.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the STM32H747I-DISCO BSP Drivers
  *          This is the main program for Cortex-M7.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "BspTimer.h"
#include "BspIo.h"
#include "BspPwm.h"
#include "BspCan.h"
#include "BspClock.h"

unsigned long _dummyVariable[4] = {0, 0, 0, 0};
unsigned long _gibberish[16] =
{
		0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF,
		0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF,
		0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF,
		0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF
};
unsigned long *_canLoc = _dummyVariable;
char _hndl = -2;
unsigned long _identifier = 0;
char _length = 0;
unsigned long _data[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool _extended = false;
bool _error = false;
unsigned short _timeStamp = 0;
bool _toggle = false;

char _txHnd = -2;


int main(void)
{
  // Setup the clocks
  BspClock::Initialize(8000000, 240000000);

  // Setup the timers
  BspTimer::Initialize();

  // Setup the I/O
  BspIo::Initialize();

  // Initial PWM setup
  BspPwm::Initialize();

  // Setup the fixed PWM
  BspPwm::SetupFixedPwm(2, 2000000, 20);
  BspPwm::SetupFixedPwm(3, 2000000, 20);
  BspPwm::SetupFixedPwm(4, 2000000, 20);
  BspPwm::SetupFixedPwm(5, 2000000, 20);

  // Setup the switch PWM
  BspPwm::SetupSwitchPwm(20000, Main::PwmFunct, 6);

  BspCan::Initialize();
  //BspCan::SetupDevice(500000, 0);
#ifdef FORCE_TOGGLE
  BspCan::PutInTestMode();
#else
  _hndl = BspCan::Subscribe(1234, &_canLoc, false);
  _txHnd = BspCan::GetTxHandle();
#endif

  SysTick->CTRL = 5;//1;// bit 2 uses CPU clock vs. CPU / 8
  SysTick->LOAD = 0xFFFFFF;

#ifdef FORCE_TOGGLE
  bool bit = false;
#endif
  unsigned long oldSysTick = (SysTick->VAL << 8);
  unsigned long sysTick;
  unsigned long elapsedTime = 0;
  unsigned long counter = 0;
  while (1)
  {
	  sysTick = (SysTick->VAL << 8);
	  elapsedTime = elapsedTime + ((oldSysTick - sysTick) >> 8);
#ifdef FORCE_TOGGLE
	  // 1us update
	  if(elapsedTime > (240 >> 3))
	  {
		  BspCan::SetTxRegister(bit);
		  elapsedTime = 0;
		  bit = !bit;
	  }
#else
	  // 100us update
	  if(elapsedTime > (36000))// >> 3))
	  {
		  elapsedTime -= 36000;
		  if(BspCan::CheckForNewData(_hndl))
		  {
			  BspCan::GetData(_hndl, &_identifier, &_length, _data, &_extended, &_error, &_timeStamp);
			  _gibberish[0] = _data[0];
			  _gibberish[2] = _data[1];
			  if(_gibberish[2] < 10)
			  {
				  _gibberish[2] = 10;
			  }
	  	  }
		  if(++counter > _gibberish[2])
		  {
			  counter = 0;
			  BspCan::Transmit(_txHnd, 123, _gibberish, 8, false);
		  }
	  }
#endif
	  oldSysTick = sysTick;
  }

}

void Main::PwmFunct(void)
{
	if(_toggle)
	{
		BspIo::SetIoPin(&BspIo::_pinInfo[BspIo::LED_RED]);
		BspIo::SetIoPin(&BspIo::_pinInfo[BspIo::LED_YELLOW]);
		BspIo::SetIoPin(&BspIo::_pinInfo[BspIo::LED_GREEN]);
		_toggle = false;
	}
	else
	{
		BspIo::ClearIoPin(&BspIo::_pinInfo[BspIo::LED_RED]);
		BspIo::ClearIoPin(&BspIo::_pinInfo[BspIo::LED_YELLOW]);
		BspIo::ClearIoPin(&BspIo::_pinInfo[BspIo::LED_GREEN]);
		_toggle = true;
	}
}

extern "C"
{
void HardFault_Handler(void)
{
	while(1)
	{
	}
}
void MemManage_Handler(void)
{
	while(1)
	{
	}
}
void  BusFault_Handler(void)
{
	while(1)
	{
	}
}

void  UsageFault_Handler(void)
{
	while(1)
	{
	}
}
}
