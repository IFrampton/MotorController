#include "Motor.h"
#include "BspAnalog.h"
#include "BspPwm.h"
#include "SineTable.h"

#define KLUDGED_CONFIGURATION
#define EXPECT_REAL_DATA

BspAnalog::AnalogType Motor::_analogChannels[NUM_ANALOGS];
BspAnalog::ExternalAnalogType Motor::_externalChannels[NUM_EXTERNAL_ANALOGS];
BspAnalog::AnalogConfig Motor::_analogConfig;
Motor::MotorConfig Motor::_motorConfig;
Motor::MotorInputs Motor::_motorInputs;
Motor::MotorOutputs Motor::_motorOutputs;
float Motor::_deltatFactor = 36.0f / 10000.0f;
float Motor::_deltaT = 1.0f / 10000.0f;
float Motor::_periodFactor = 24000.0f;
short Motor::_halfPeriod = 24000;

void Motor::Initialize(void)
{
#ifdef KLUDGED_CONFIGURATION
	//<KLUDGE> Setup parameters until an interface is operational.
	BspAnalog::InitializePointer(&_analogConfig);
	_analogConfig.Offset[0][14] = -32767;
	_analogConfig.ScaleFactor[0][14] = 1000.0f/(1.5f * 32768.0f);
#ifdef EXPECT_REAL_DATA
	_analogConfig.ExternalOffset[0] = 25640;
	_analogConfig.ExternalScaleFactor[0] = 100.0f/(1.024f * 20156.0f);//600.0f/(1.024f * 20156.0f);
	_analogConfig.ExternalOffset[1] = 25640;
	_analogConfig.ExternalScaleFactor[1] = 100.0f/(1.024f * 20156.0f);//600.0f/(1.024f * 20156.0f);
	_analogConfig.ExternalOffset[2] = 25640;
	_analogConfig.ExternalScaleFactor[2] = 100.0f/(1.024f * 20156.0f);//600.0f/(1.024f * 20156.0f);
#else
	_analogConfig.ExternalOffset[0] = 0;
	_analogConfig.ExternalScaleFactor[0] = 1.0f;
	_analogConfig.ExternalOffset[1] = 0;
	_analogConfig.ExternalScaleFactor[1] = 1.0f;
	_analogConfig.ExternalOffset[2] = 0;
	_analogConfig.ExternalScaleFactor[2] = 1.0f;
#endif
	_motorConfig.MotorVoltsPerHz = 60.0f;
	_motorConfig.FrequencyRampRate = 10.0f;
	_motorConfig.FrequencyTarget = 100.0f;
#endif

	BspAnalog::SetupChannel(0, 14, &_analogChannels[ANA_V_BUS]);
	//BspAnalog::SetupChannel(0, 15, &_analogChannels[ANA_V_A]);
	//BspAnalog::SetupChannel(0, 19, &_analogChannels[ANA_V_B]);
	//BspAnalog::SetupChannel(0, 3,  &_analogChannels[ANA_V_C]);
	//BspAnalog::SetupChannel(0, 7,  &_analogChannels[ANA_I_IN]);
	//BspAnalog::SetupChannel(0, 4,  &_analogChannels[ANA_T_1]);
	//BspAnalog::SetupChannel(0, 8,  &_analogChannels[ANA_T_2]);
	//BspAnalog::SetupChannel(0, 9,  &_analogChannels[ANA_RSLV_SIN]);
	//BspAnalog::SetupChannel(0, 5,  &_analogChannels[ANA_RSLV_COS]);
	BspAnalog::SetupExternalChannel(0, &_externalChannels[ANA_I_A]);
	BspAnalog::SetupExternalChannel(1, &_externalChannels[ANA_I_B]);
	BspAnalog::SetupExternalChannel(2, &_externalChannels[ANA_I_C]);

	//Only compute once (switching frequency does not change)
	_deltatFactor = 360.0f / 10000.0f;
	_deltaT = 1.0f / 10000.0f;
	unsigned short pwmPeriod = BspPwm::GetSwitchPeriod();
	_periodFactor = (float)pwmPeriod * 0.5f;
	_halfPeriod = pwmPeriod >> 1;
}

void Motor::Logic()
{
	_motorInputs.Current[0] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_A]);
	//_motorInputs.Current[1] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_B]);
	_motorInputs.Current[2] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_C]);
	//<KLUDGE> For now, SPI2 only reads 0 (even with all the right signals), so calculate i2.
	_motorInputs.Current[1] = -(_motorInputs.Current[0] + _motorInputs.Current[2]);
	float busVoltage = BspAnalog::GetFastSingleSample(&_analogChannels[ANA_V_BUS]);
	_motorInputs.BusVoltage = busVoltage;
	float motorBackEmf = _motorOutputs.Frequency * _motorConfig.MotorVoltsPerHz;
	float amplitude = motorBackEmf / busVoltage;
	if(amplitude > 1.0f)
	{
		amplitude = 1.0f;
	}
	else if (amplitude < -1.0f)
	{
		amplitude = -1.0f;
	}
	_motorOutputs.Amplitude = amplitude;
	// Ramping Up
	if(_motorOutputs.Frequency < _motorConfig.FrequencyTarget)
	{
		float increase = _motorConfig.FrequencyRampRate * _deltaT;
		if(_motorOutputs.Frequency + increase > _motorConfig.FrequencyTarget)
		{
			_motorOutputs.Frequency = _motorConfig.FrequencyTarget;
		}
		else
		{
			_motorOutputs.Frequency += increase;
		}
	}
	// Ramping down or steady
	else
	{
		float decrease = _motorConfig.FrequencyRampRate * _deltaT;
		if(_motorOutputs.Frequency - decrease < _motorConfig.FrequencyTarget)
		{
			_motorOutputs.Frequency = _motorConfig.FrequencyTarget;
		}
		else
		{
			_motorOutputs.Frequency -= decrease;
		}
	}
	// calculate phase now
	_motorOutputs.Phase += _motorOutputs.Frequency * _deltatFactor;
	if(_motorOutputs.Phase >= 360.0f)
	{
		_motorOutputs.Phase -= 360.0f;
	}
	SineTable::Sine_3Phase(_motorOutputs.Phase, _motorOutputs.Point);
	_motorOutputs.Voltage[0] = _motorOutputs.Point[0] * motorBackEmf;
	_motorOutputs.Voltage[1] = _motorOutputs.Point[1] * motorBackEmf;
	_motorOutputs.Voltage[1] = _motorOutputs.Point[2] * motorBackEmf;
	_motorOutputs.RealCurrent = _motorOutputs.Point[0] * _motorInputs.Current[0] +
								_motorOutputs.Point[1] * _motorInputs.Current[1] +
								_motorOutputs.Point[2] * _motorInputs.Current[2];
	_motorOutputs.ReactiveCurrent = ((_motorOutputs.Point[0] - _motorOutputs.Point[1]) *  _motorInputs.Current[2] +
									 (_motorOutputs.Point[1] - _motorOutputs.Point[2]) *  _motorInputs.Current[0] +
									 (_motorOutputs.Point[2] - _motorOutputs.Point[0]) *  _motorInputs.Current[1]) * (1.0f / 1.73205f);
	float ampFactor =  _motorOutputs.Amplitude * _periodFactor;
	unsigned short period = (_motorOutputs.Point[0] * ampFactor) + _halfPeriod;
	BspPwm::SetSwitchDutyCycle(0, period);
	period = (_motorOutputs.Point[1] * ampFactor) + _halfPeriod;
	BspPwm::SetSwitchDutyCycle(1, period);
	period = (_motorOutputs.Point[2] * ampFactor) + _halfPeriod;
	BspPwm::SetSwitchDutyCycle(2, period);
}

