#include "main.h"
#include "BspTimer.h"
#include "BspIo.h"
#include "BspPwm.h"
#include "BspCan.h"
#include "BspClock.h"
#include "BspSpi.h"
#include "Motor.h"

//#define SEND_GIBBERISH
#define EXPECT_REAL_DATA

unsigned long _dummyVariable[4] = {0, 0, 0, 0};
unsigned long _gibberish[16] =
{
		0xDEADBEEF, 0xDEADBEEF, 0xC8, 0xDEADBEEF,
		0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF,
		0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF,
		0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF
};
unsigned long *_canLoc = _dummyVariable;
char _hndl = -2;
unsigned long _identifier = 0;
char _length = 0;
unsigned long _data[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned long _txData[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char _canMessage = 0;
bool _extended = false;
bool _error = false;
unsigned short _timeStamp = 0;
bool _toggle = false;
unsigned short _currents[3][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
unsigned char _currentLoc[3] = {0, 0, 0};
unsigned long _updatePeriod = 100000;
bool _tggle = false;

char _txHnd = -2;


int main(void)
{
	//unsigned long long counts = 0;
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

	// Setup SPI for Phase A
	BspAnalog::InitializeAdc();
	BspAnalog::InitializeExternal();

	// Setup the switch PWM
	BspPwm::SetupSwitchPwm(10000, 300, Main::PwmFunct, 6);

	Motor::Initialize();

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

	//while (1)
	//{
	//	counts++;
	//}

	#ifdef FORCE_TOGGLE
	bool bit = false;
	#endif
	unsigned long oldSysTick = (SysTick->VAL << 8);
	unsigned long sysTick;
	unsigned long elapsedTime = 0;
#ifdef SEND_GIBBERISH
	unsigned long elapsedTime2 = 0;
	unsigned long counter = 0;
#endif
	while (1)
	{
		sysTick = (SysTick->VAL << 8);
		unsigned long intervalTime = ((oldSysTick - sysTick) >> 8);
		elapsedTime += intervalTime;
		// 333us update
		if(elapsedTime > _updatePeriod)
		{
			elapsedTime -= _updatePeriod;
			if(BspCan::CheckForNewData(_hndl))
			{
				BspCan::GetData(_hndl, &_identifier, &_length, _data, &_extended, &_error, &_timeStamp);
				if((_identifier == (0x101 << 18)) && (_extended == false) && (_length == 8))
				{
					unsigned short data = _data[0] & 0xFFFF;
					if(data < 0xFFFF)
					{
						Motor::_motorConfig.FrequencyTarget = (float)data * 0.1f;
					}
					data = _data[0] >> 16;
					if(data < 0xFFFF)
					{
						Motor::_motorConfig.FrequencyRampRate = (float)data * 0.01f;
					}
					data = _data[1] & 0xFFFF;
					if(data < 0xFFFF)
					{
						Motor::_motorConfig.MotorVoltsPerHz = (float)data * 0.001f;
					}
					data = _data[1] >> 16;
					if(data < 0xFFFF)
					{
						//Motor::_motorConfig.FrequencyRampRate = (float)data * 0.01f;
					}
				}
				//else if()
				//{
					// Only one packet at this time
				//}
			}
			switch(_canMessage)
			{
				// Motor Voltages
				case 0:
				{
					unsigned short data = (unsigned short)(Motor::_motorInputs.BusVoltage * 50.0f);
					_txData[1] = data;
					data = (unsigned short)(Motor::_motorOutputs.Voltage[0] * 50.0f);
					_txData[1] <<= 16;
					_txData[1] += data;
					data = (unsigned short)(Motor::_motorOutputs.Voltage[1] * 50.0f);
					_txData[0] += data;
					data = (unsigned short)(Motor::_motorOutputs.Voltage[2] * 50.0f);
					_txData[0] <<= 16;
					_txData[0] += data;
					BspCan::Transmit(_txHnd, 0x200, &_txData[0], 8, false);
					_canMessage++;
					break;
				}
				// Motor Currents
				case 1:
				{
					unsigned short data = 0xFFFF;
					_txData[1] = data;
#ifdef EXPECT_REAL_DATA
					data = (unsigned short)(Motor::_motorInputs.Current[0] * 50.0f + 32767.0f);
					_txData[1] <<= 16;
					_txData[1] += data;
					data = (unsigned short)(Motor::_motorInputs.Current[1] * 50.0f + 32767.0f);
					_txData[0] += data;
					data = (unsigned short)(Motor::_motorInputs.Current[2] * 50.0f + 32767.0f);
					_txData[0] <<= 16;
					_txData[0] += data;
#else
					data = (unsigned short)(Motor::_motorInputs.Current[0] * 1.0f + 0.0f);
					_txData[1] <<= 16;
					_txData[1] += data;
					data = (unsigned short)(Motor::_motorInputs.Current[1] * 1.0f + 0.0f);
					_txData[0] += data;
					data = (unsigned short)(Motor::_motorInputs.Current[2] * 1.0f + 0.0f);
					_txData[0] <<= 16;
					_txData[0] += data;
#endif
					BspCan::Transmit(_txHnd, 0x201, &_txData[0], 8, false);
					_canMessage++;
					break;
				}
				// Other Information
				case 2:
				default:
				{
					unsigned short data = (unsigned short)(Motor::_motorOutputs.Amplitude * 10000.0f + 32767.0f);
					_txData[1] = data;
					data = (unsigned short)(Motor::_motorOutputs.Frequency * 10.0f);
					_txData[1] <<= 16;
					_txData[1] += data;
					data = (unsigned short)(Motor::_motorOutputs.RealCurrent * 50.0f + 32767.0f);
					_txData[0] += data;
					data = (unsigned short)(Motor::_motorOutputs.ReactiveCurrent * 50.0f + 32767.0f);
					_txData[0] <<= 16;
					_txData[0] += data;
					BspCan::Transmit(_txHnd, 0x202, &_txData[0], 8, false);
					_canMessage = 0;
					break;
				}
			}
		}
#ifdef SEND_GIBBERISH
#ifdef FORCE_TOGGLE
		// 1us update
		if(elapsedTime2 > (240 >> 3))
		{
			BspCan::SetTxRegister(bit);
			elapsedTime = 0;
			bit = !bit;
		}
#else
		elapsedTime2 += intervalTime;
		// 100us update
		if(elapsedTime2 > (36000))// >> 3))
		{
			elapsedTime2 -= 36000;
			if(BspCan::CheckForNewData(_hndl))
			{
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
				if(_tggle)
				{
					BspCan::Transmit(_txHnd, 123, _gibberish, 8, false);
					_tggle = false;
				}
				else
				{
					_gibberish[8] = (_currents[0][0] << 16) + _currents[1][0];
					_gibberish[9] = (_currents[2][0] << 16) + _currents[2][1];
					BspCan::Transmit(_txHnd, 1234, &_gibberish[8], 6, false);
					_tggle = true;
				}
			}
		}
#endif
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
	Motor::Logic();
#if 0
	for(unsigned char idx = 0; idx < 3; idx++)
	{
#ifdef TRY_TO_USE_FEEDBACK
		if(BspSpi::IsDataAvailable(_spiDataReady[idx]))
		{
			_currents[idx][_currentLoc[idx]] = BspSpi::ReadData(_spiData[idx]);
			_currentLoc[idx]++;
			_currentLoc[idx] &= ((sizeof(_currents[idx]) / sizeof(unsigned short)) - 1);
		}
		else
		{
			BspSpi::SetReadComplete(_spiReadComplete[idx]);
		}
#else
		unsigned short *loc = _currents[idx];
		for(char x = 8; x; x--)
		{
			*(loc++) = BspSpi::ReadData(_spiData[idx]);
		}
		BspSpi::SetReadComplete(_spiReadComplete[idx]);
#endif
	}
#endif
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
