#include "Motor.h"
#include "BspAnalog.h"
#include "BspPwm.h"
#include "DataMan.h"
#include "SineTable.h"
#include "Loading.h"

#define EXPECT_REAL_DATA

BspAnalog::AnalogType MotorControl::_analogChannels[NUM_ANALOGS];
BspAnalog::ExternalAnalogType MotorControl::_externalChannels[NUM_EXTERNAL_ANALOGS];
MotorControl::MotorConfig *MotorControl::_config;
MotorControl::MotorInputs *MotorControl::_analogIn;
MotorControl::MotorOutputs *MotorControl::_analogOut;
bool MotorControl::_dataLinked = false;
float MotorControl::_deltatFactor = 36.0f / 10000.0f;
float MotorControl::_deltaT = 1.0f / 10000.0f;
float MotorControl::_periodFactor = 24000.0f;
short MotorControl::_halfPeriod = 24000;
bool MotorControl::_loggingInput[32];
unsigned long MotorControl::_logInputIndex = 0;

void MotorControl::Initialize(void)
{
#ifdef METERING_BOARD_REV2
	BspAnalog::SetupChannel(0, 14, &_analogChannels[ANA_V_BUS]);
	BspAnalog::SetupChannel(0, 15, &_analogChannels[ANA_V_A]);
	BspAnalog::SetupChannel(0, 19, &_analogChannels[ANA_V_B]);
	BspAnalog::SetupChannel(0, 3,  &_analogChannels[ANA_V_C]);
	BspAnalog::SetupChannel(0, 7,  &_analogChannels[ANA_I_IN]);
#else
	BspAnalog::SetupChannel(0, 7, &_analogChannels[ANA_V_BUS]);
	BspAnalog::SetupChannel(0, 3, &_analogChannels[ANA_V_A]);
	BspAnalog::SetupChannel(0, 19, &_analogChannels[ANA_V_B]);
	BspAnalog::SetupChannel(0, 15,  &_analogChannels[ANA_V_C]);
	BspAnalog::SetupChannel(0, 14,  &_analogChannels[ANA_I_IN]);
#endif
	BspAnalog::SetupChannel(0, 4,  &_analogChannels[ANA_T_1]);
	BspAnalog::SetupChannel(0, 8,  &_analogChannels[ANA_T_2]);
	BspAnalog::SetupChannel(0, 9,  &_analogChannels[ANA_RSLV_SIN]);
	BspAnalog::SetupChannel(0, 5,  &_analogChannels[ANA_RSLV_COS]);
	BspAnalog::SetupExternalChannel(0, &_externalChannels[ANA_I_A]);
	BspAnalog::SetupExternalChannel(1, &_externalChannels[ANA_I_B]);
	BspAnalog::SetupExternalChannel(2, &_externalChannels[ANA_I_C]);

	//Only compute once (switching frequency does not change)
	_deltatFactor = 360.0f / 10000.0f;
	_deltaT = 1.0f / 10000.0f;
	unsigned short pwmPeriod = BspPwm::GetSwitchPeriod();
	_periodFactor = (float)pwmPeriod * 0.5f;
	_halfPeriod = pwmPeriod >> 1;
	BspPwm::SetupSwitchPwm(10000, 300, Logic, 6);

	BspAnalog::StartConversion();
}

void MotorControl::Logic()
{
	ProcLoading::BeginTask(ProcLoading::Motor_Task);
	_loggingInput[_logInputIndex] = (GPIOC->IDR & 0x4) > 0;
	_logInputIndex++;
	_logInputIndex &= 31;
	_analogIn->Current[0] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_A]);
	_analogIn->Current[1] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_B]);
	_analogIn->Current[2] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_C]);
	//<KLUDGE> For now, SPI2 only reads 0 (even with all the right signals), so calculate i2.
	//_motorInputs.Current[1] = -(_motorInputs.Current[0] + _motorInputs.Current[2]);
	float busVoltage = BspAnalog::GetFastSingleSample(&_analogChannels[ANA_V_BUS]);
	_analogIn->BusVoltage = busVoltage;
	float motorBackEmf = _analogOut->Frequency * _config->MotorVoltsPerHz;
	float amplitude = motorBackEmf / busVoltage + _config->Offset;
	if(amplitude > 1.0f)
	{
		amplitude = 1.0f;
	}
	else if (amplitude < -1.0f)
	{
		amplitude = -1.0f;
	}
	_analogOut->Amplitude = amplitude;
	// Ramping Up
	if(_analogOut->Frequency < _config->FrequencyTarget)
	{
		float increase = _config->FrequencyRampRate * _deltaT;
		if(_analogOut->Frequency + increase > _config->FrequencyTarget)
		{
			_analogOut->Frequency = _config->FrequencyTarget;
		}
		else
		{
			_analogOut->Frequency += increase;
		}
	}
	// Ramping down or steady
	else
	{
		float decrease = _config->FrequencyRampRate * _deltaT;
		if(_analogOut->Frequency - decrease < _config->FrequencyTarget)
		{
			_analogOut->Frequency = _config->FrequencyTarget;
		}
		else
		{
			_analogOut->Frequency -= decrease;
		}
	}
	// calculate phase now
	_analogOut->Phase += _analogOut->Frequency * _deltatFactor;
	if(_analogOut->Phase >= 360.0f)
	{
		_analogOut->Phase -= 360.0f;
	}
	SineTable::Sine_3Phase(_analogOut->Phase, _analogOut->Point);
	_analogOut->Voltage[0] = _analogOut->Point[0] * motorBackEmf;
	_analogOut->Voltage[1] = _analogOut->Point[2] * motorBackEmf;
	_analogOut->Voltage[2] = _analogOut->Point[1] * motorBackEmf;
	_analogOut->RealCurrent = _analogOut->Point[0] * _analogIn->Current[0] +
								_analogOut->Point[2] * _analogIn->Current[1] +
								_analogOut->Point[1] * _analogIn->Current[2];
	_analogOut->ReactiveCurrent = ((_analogOut->Point[0] - _analogOut->Point[2]) *  _analogIn->Current[2] +
									 (_analogOut->Point[2] - _analogOut->Point[1]) *  _analogIn->Current[0] +
									 (_analogOut->Point[1] - _analogOut->Point[0]) *  _analogIn->Current[1]) * (1.0f / 1.73205f);
	float ampFactor =  _analogOut->Amplitude * _periodFactor;
	unsigned short period = (_analogOut->Point[0] * ampFactor) + _halfPeriod;
	BspPwm::SetSwitchDutyCycle(0, period);
	period = (_analogOut->Point[2] * ampFactor) + _halfPeriod;
	BspPwm::SetSwitchDutyCycle(1, period);
	period = (_analogOut->Point[1] * ampFactor) + _halfPeriod;
	BspPwm::SetSwitchDutyCycle(2, period);
	ProcLoading::EndTask(ProcLoading::Motor_Task);
}

