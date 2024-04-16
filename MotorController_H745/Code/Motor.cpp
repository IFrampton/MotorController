#include <math.h>
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
MotorControl::MotorDigitalConfig *MotorControl::_digitalConfig;
MotorControl::MotorInputs *MotorControl::_analogIn;
MotorControl::MotorOutputs *MotorControl::_analogOut;
MotorControl::MotorDigitalOutputs *MotorControl::_digitalOut;
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
	BspPwm::SetupSwitchPwm(10000, 300, Logic, 6);
	unsigned short pwmPeriod = BspPwm::GetSwitchPeriod();
	_periodFactor = (float)pwmPeriod * 0.5f;
	_halfPeriod = pwmPeriod >> 1;

	BspAnalog::StartConversion();
}

void MotorControl::Logic()
{
	ProcLoading::BeginTask(ProcLoading::Motor_Task);
	Fccp::SnapshotHandler();
	_loggingInput[_logInputIndex] = (GPIOC->IDR & 0x4) > 0;
	_logInputIndex++;
	_logInputIndex &= 31;
	_analogIn->Current[0] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_A]);
	_analogIn->Current[1] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_B]);
	_analogIn->Current[2] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_C]);
	bool fault = false;
	if(_analogIn->Current[0] > _config->CurrentFault)
	{
		fault = true;
	}
	else if(_analogIn->Current[0] < -_config->CurrentFault)
	{
		fault = true;
	}
	if(_analogIn->Current[1] > _config->CurrentFault)
	{
		fault = true;
	}
	else if(_analogIn->Current[1] < -_config->CurrentFault)
	{
		fault = true;
	}
	if(_analogIn->Current[2] > _config->CurrentFault)
	{
		fault = true;
	}
	else if(_analogIn->Current[2] < -_config->CurrentFault)
	{
		fault = true;
	}
	if(fault && !_digitalOut->Faulted)
	{
		BspPwm::DisablePWM();
		_digitalOut->Faulted = true;
		_analogOut->Frequency = 0.0f;
	}
	if((_digitalConfig->Reset == 1) && (_digitalOut->PrevReset != 1))
	{
		BspPwm::EnablePWM();
		_digitalOut->Faulted = false;
	}
	_digitalOut->PrevReset = _digitalConfig->Reset;
	float busVoltage = BspAnalog::GetFastSingleSample(&_analogChannels[ANA_V_BUS]);
	_analogIn->BusVoltage = busVoltage;
	_analogOut->RealCurrent = (_analogOut->Point[0] * _analogIn->Current[0] +
								_analogOut->Point[2] * _analogIn->Current[1] +
								_analogOut->Point[1] * _analogIn->Current[2]) * (1.0f / 1.73205f);
	_analogOut->ReactiveCurrent = ((_analogOut->Point[0] - _analogOut->Point[2]) *  _analogIn->Current[2] +
									 (_analogOut->Point[2] - _analogOut->Point[1]) *  _analogIn->Current[0] +
									 (_analogOut->Point[1] - _analogOut->Point[0]) *  _analogIn->Current[1]) * (1.0f / 3.0f);
	float motorBackEmf = 0.0f;
	if(!_digitalOut->Faulted)
	{
#ifdef FLUX_ESTIMATION
#else
		if(busVoltage < 2.0f)
		{
			busVoltage = 2.0f;
		}
		float freqTarget = _config->FrequencyTarget;
		if(_analogOut->Frequency < _config->ClosedLoopFrequency)
		{
			float allowableFrequency = (busVoltage - _config->StoppedVoltage[0]) /  _config->MotorVoltsPerHz[0];
			if(freqTarget > allowableFrequency)
			{
				if(allowableFrequency > 0)
				{
					freqTarget = allowableFrequency;
				}
				else
				{
					freqTarget = 0;
				}
			}
			if(_analogOut->Frequency < freqTarget)
			{
				float increase = _config->FrequencyRampRate[0] * _deltaT;
				if(_analogOut->Frequency + increase > freqTarget)
				{
					_analogOut->Frequency = freqTarget;
				}
				else
				{
					_analogOut->Frequency += increase;
				}
			}
			// Ramping down or steady
			else
			{
				float decrease = _config->FrequencyRampRate[0] * _deltaT;
				if(_analogOut->Frequency - decrease < freqTarget)
				{
					_analogOut->Frequency = freqTarget;
				}
				else
				{
					_analogOut->Frequency -= decrease;
				}
			}

			motorBackEmf = fabsf(_analogOut->Frequency) * _config->MotorVoltsPerHz[0];

			float amplitude = (motorBackEmf + _config->StoppedVoltage[0]) / busVoltage;
			if(amplitude > 1.0f)
			{
				amplitude = 1.0f;
			}
			else if (amplitude < -1.0f)
			{
				amplitude = -1.0f;
			}
			_analogOut->Amplitude = amplitude;
		}
		else // Normal Operation
		{
			float allowableFrequency = (busVoltage - _config->StoppedVoltage[1]) /  _config->MotorVoltsPerHz[1];
			if(freqTarget > allowableFrequency)
			{
				if(allowableFrequency > 0)
				{
					freqTarget = allowableFrequency;
				}
				else
				{
					freqTarget = 0;
				}
			}
			if(_analogOut->Frequency < freqTarget)
			{
				float increase = _config->FrequencyRampRate[1] * _deltaT;
				if(_analogOut->Frequency + increase > freqTarget)
				{
					_analogOut->Frequency = freqTarget;
				}
				else
				{
					_analogOut->Frequency += increase;
				}
			}
			// Ramping down or steady
			else
			{
				float decrease = _config->FrequencyRampRate[1] * _deltaT;
				if(_analogOut->Frequency - decrease < freqTarget)
				{
					_analogOut->Frequency = freqTarget;
				}
				else
				{
					_analogOut->Frequency -= decrease;
				}
			}

			float error = _config->ReactivePower_Target - _analogOut->ReactiveCurrent;
			_analogOut->ReactivePower_Pterm = _config->ReactivePower_PGain * error;
			_analogOut->ReactivePower_Iterm = _config->ReactivePower_IGain * error;
			float d_error = error - _analogOut->ReactivePower_Error;
			_analogOut->ReactivePower_Dterm = _config->ReactivePower_DGain * d_error;
			_analogOut->ReactivePower_TDterm = _config->ReactivePower_TDGain * d_error;
			_analogOut->ReactivePower_Error = error;
			float integrator = _analogOut->ReactivePower_Integrator +  _analogOut->ReactivePower_Iterm + _analogOut->ReactivePower_TDterm;
			// Limit Integrator
			if(integrator > _config->ReactivePower_MaxIntegrator)
			{
				integrator = _config->ReactivePower_MaxIntegrator;
			}
			else if(integrator < _config->ReactivePower_MinIntegrator)
			{
				integrator = _config->ReactivePower_MinIntegrator;
			}
			_analogOut->ReactivePower_Integrator = integrator;
			_analogOut->ReactivePower_Adjustment = _analogOut->ReactivePower_Pterm + _analogOut->ReactivePower_Integrator + _analogOut->ReactivePower_Dterm;

			motorBackEmf = fabsf(_analogOut->Frequency) * _config->MotorVoltsPerHz[1];

			float amplitude = (motorBackEmf + _config->StoppedVoltage[1] + _analogOut->ReactivePower_Adjustment) / busVoltage;
			if(amplitude > 1.0f)
			{
				amplitude = 1.0f;
			}
			else if (amplitude < -1.0f)
			{
				amplitude = -1.0f;
			}
			_analogOut->Amplitude = amplitude;
		}
		// calculate phase now
		_analogOut->Phase += _analogOut->Frequency * _deltatFactor;
		if(_analogOut->Phase >= 360.0f)
		{
			_analogOut->Phase -= 360.0f;
		}
		if(_analogOut->Phase < 0.0f)
		{
			_analogOut->Phase += 360.0f;
		}
#endif
	}
	SineTable::Sine_3Phase(_analogOut->Phase, _analogOut->Point);
	_analogOut->Voltage[0] = _analogOut->Point[0] * motorBackEmf;
	_analogOut->Voltage[1] = _analogOut->Point[2] * motorBackEmf;
	_analogOut->Voltage[2] = _analogOut->Point[1] * motorBackEmf;
	float ampFactor =  _analogOut->Amplitude * _periodFactor;
	unsigned short period = (_analogOut->Point[0] * ampFactor) + _halfPeriod;
	BspPwm::SetSwitchDutyCycle(0, period);
	period = (_analogOut->Point[2] * ampFactor) + _halfPeriod;
	BspPwm::SetSwitchDutyCycle(1, period);
	period = (_analogOut->Point[1] * ampFactor) + _halfPeriod;
	BspPwm::SetSwitchDutyCycle(2, period);
	ProcLoading::EndTask(ProcLoading::Motor_Task);
}

bool MotorControl::OkToSave()
{
	return ((_analogIn->BusVoltage < 10.0f) && (_analogOut->Frequency < 1));
}
