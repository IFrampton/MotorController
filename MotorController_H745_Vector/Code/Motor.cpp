#include <math.h>
#include "Motor.h"
#include "BspAnalog.h"
#include "BspPwm.h"
#include "DataMan.h"
#include "SineTable.h"
#include "Loading.h"
#include "VectorControl.h"
extern "C"
{
#include "P2319ASW01.h"
}

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
float MotorControl::_analogData[10] = {25.0f, 25.0f, 32.0f, 25.0f, 25.0f, 25.0f, 25.0f, 25.0f, 25.0f, 25.0f,};

void MotorControl::Initialize(void)
{
	// Note: These two channels must use different converters to be sampled at the same time
	BspAnalog::SetupChannel(0, 9,  &_analogChannels[ANA_RSLV_SIN]);
	BspAnalog::SetupChannel(1, 5,  &_analogChannels[ANA_RSLV_COS]);
#ifdef METERING_BOARD_REV2
	BspAnalog::SetupChannel(0, 14, &_analogChannels[ANA_V_BUS]);
	BspAnalog::SetupChannel(0, 15, &_analogChannels[ANA_V_A]);
	BspAnalog::SetupChannel(0, 19, &_analogChannels[ANA_V_B]);
	BspAnalog::SetupChannel(0, 3,  &_analogChannels[ANA_V_C]);
	BspAnalog::SetupChannel(1, 7,  &_analogChannels[ANA_I_IN]);
#else
	BspAnalog::SetupChannel(1, 7, &_analogChannels[ANA_V_BUS]);
	BspAnalog::SetupChannel(0, 3, &_analogChannels[ANA_V_A]);
	BspAnalog::SetupChannel(0, 19, &_analogChannels[ANA_V_B]);
	BspAnalog::SetupChannel(0, 15,  &_analogChannels[ANA_V_C]);
	BspAnalog::SetupChannel(1, 14,  &_analogChannels[ANA_I_IN]);
#endif
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
	_analogOut->MaxFeedbackAmplitude[0] = _config->DefaultMaxFeedbackAmplitude;
	_analogOut->MaxFeedbackAmplitude[1] = _config->DefaultMaxFeedbackAmplitude;
	_analogOut->LastFeedbackAmplitude[0] = _config->DefaultMaxFeedbackAmplitude;
	_analogOut->LastFeedbackAmplitude[1] = _config->DefaultMaxFeedbackAmplitude;

	BspAnalog::StartConversion();
}

void MotorControl::Logic()
{
	//<KLUDGE> Once enabled, this will stay enabled
	BspTimer::StartLpTimer();

	ProcLoading::BeginTask(ProcLoading::Motor_Task);
	//<KLUDGE>
	BspAnalog::UpdateRawValues();

	Fccp::SnapshotHandler();
	_loggingInput[_logInputIndex] = (GPIOC->IDR & 0x4) > 0;
	_logInputIndex++;
	_logInputIndex &= 31;

	MeasureCurrent();

	MeasureBus();

	ComputeVectorCurrents();

	switch(_config->Mode)
	{
		case 1:
		{
			float busVoltage = _analogIn->BusVoltage;
			if(busVoltage < 2.0f)
			{
				busVoltage = 2.0f;
			}
			float freqTarget = _config->FrequencyTarget;
			float motorBackEmf = 0.0f;
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

				float error = _config->Reactive_Target - _analogOut->ReactiveCurrent;
				_analogOut->Reactive.Pterm = _config->Reactive.PGain * error;
				_analogOut->Reactive.Iterm = _config->Reactive.IGain * error;
				float d_error = error - _analogOut->Reactive.Error;
				_analogOut->Reactive.Dterm = _config->Reactive.DGain * d_error;
				_analogOut->Reactive.TDterm = _config->Reactive.TDGain * d_error;
				_analogOut->Reactive.Error = error;
				float integrator = _analogOut->Reactive.Integrator + _analogOut->Reactive.Iterm + _analogOut->Reactive.TDterm;
				// Limit Integrator
				if(integrator > _config->Reactive.MaxIntegrator)
				{
					integrator = _config->Reactive.MaxIntegrator;
				}
				else if(integrator < _config->Reactive.MinIntegrator)
				{
					integrator = _config->Reactive.MinIntegrator;
				}
				_analogOut->Reactive.Integrator = integrator;
				_analogOut->Reactive.ControlOutput = _analogOut->Reactive.Pterm + _analogOut->Reactive.Integrator + _analogOut->Reactive.Dterm;

				motorBackEmf = fabsf(_analogOut->Frequency) * _config->MotorVoltsPerHz[1];

				float amplitude = (motorBackEmf + _config->StoppedVoltage[1] + _analogOut->Reactive.ControlOutput) / busVoltage;
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
			SineTable::Sine_3Phase(_analogOut->Phase, _analogOut->Point);
			_analogOut->Voltage[0] = _analogOut->Point[0] * motorBackEmf;
			_analogOut->Voltage[1] = _analogOut->Point[2] * motorBackEmf;
			_analogOut->Voltage[2] = _analogOut->Point[1] * motorBackEmf;

			SetDutyCycles();
			break;
		}
		case 2:
		{
			CalculatePosition();

			// Control Speed
			SpeedGovernor();

			ComputeOutputSines();

			SimpleVector();

			SetDutyCycles();
			break;
		}
		case 3:
		{
			//_analogData[3] = BspAnalog::GetFastSingleSample(&_analogChannels[ANA_V_BUS]);
			//_analogData[4] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_A]);
			//_analogData[5] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_B]);
			//_analogData[6] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_C]);
			//_analogData[7] = BspAnalog::GetFastSingleSample(&_analogChannels[ANA_I_IN]);
			//_analogData[8] = BspAnalog::GetFastSingleSample(&_analogChannels[ANA_RSLV_SIN]);
			//_analogData[9] = BspAnalog::GetFastSingleSample(&_analogChannels[ANA_RSLV_COS]);
			VectorControl::UpdateInputsToXcp();//_analogData);
			P2319ASW01_step0();
			VectorControl::UpdateOutputsFromXcp();
			unsigned short period = ASWOUT_PhaAPwmDc << 1;
			_analogOut->PWM[0] = period;
			BspPwm::SetSwitchDutyCycle(0, period);
			period = ASWOUT_PhaBPwmDc << 1;
			_analogOut->PWM[1] = period;
			BspPwm::SetSwitchDutyCycle(1, period);
			period = ASWOUT_PhaCPwmDc << 1;
			_analogOut->PWM[2] = period;
			BspPwm::SetSwitchDutyCycle(2, period);
			break;
		}
	}

	ProcLoading::EndTask(ProcLoading::Motor_Task);
}

void MotorControl::MeasureCurrent()
{
	//_analogIn->Current[0] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_A]);
	_analogIn->Current[1] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_B]);
	_analogIn->Current[2] = BspAnalog::GetFastExternalSample(&_externalChannels[ANA_I_C]);
	_analogIn->Current[0] = -(_analogIn->Current[1] + _analogIn->Current[2]);
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
}

void MotorControl::CalculatePosition()
{
	_analogIn->Feedback[0] = BspAnalog::GetFastSingleSample(&_analogChannels[ANA_RSLV_SIN]);
	if(_analogOut->MaxFeedbackAmplitude[0] < fabsf(_analogIn->Feedback[0]))
	{
		_analogOut->MaxFeedbackAmplitude[0] = fabsf(_analogIn->Feedback[0]);
	}
	_analogIn->Feedback[1] = BspAnalog::GetFastSingleSample(&_analogChannels[ANA_RSLV_COS]);
	if(_analogOut->MaxFeedbackAmplitude[1] < fabsf(_analogIn->Feedback[1]))
	{
		_analogOut->MaxFeedbackAmplitude[1] = fabsf(_analogIn->Feedback[1]);
	}
	float ampl = _analogIn->Feedback[0] / _analogOut->LastFeedbackAmplitude[0];
	if(ampl > 1.0f)
	{
		ampl = 1.0f;
	}
	else if(ampl < -1.0f)
	{
		ampl = -1.0f;
	}
	_analogOut->Angles[0] = SineTable::ArcSine(ampl);
	ampl = _analogIn->Feedback[1] / _analogOut->LastFeedbackAmplitude[1];
	if(ampl > 1.0f)
	{
		ampl = 1.0f;
	}
	else if(ampl < -1.0f)
	{
		ampl = -1.0f;
	}
	_analogOut->Angles[1] = SineTable::ArcCosine(ampl);
	_analogOut->Angles[2] = GetResolverAngle();
	// Must have seen an angle greater than 270 before seeing one less than 90 will trigger
	bool trig = false;
	_analogOut->FilteredSine = (_analogOut->FilteredSine * _config->FilterCoefficient + _analogIn->Feedback[0]) / (_config->FilterCoefficient + 1.0f);
	bool highAngle = false;
	if(_digitalOut->PrevHighAngle)
	{
		highAngle = (_analogOut->FilteredSine >= -0.5f);
	}
	else
	{
		highAngle = (_analogOut->FilteredSine >= 0.5f);
	}
	trig = ((highAngle && !_digitalOut->PrevHighAngle) || (++_analogOut->TimeoutCounter >= _config->Speedtimeout));
	if(trig)
	{
		_analogOut->TimeoutCounter = 0;
		if(_digitalConfig->UpdateMinMax)
		{
			_analogOut->LastFeedbackAmplitude[0] = _analogOut->MaxFeedbackAmplitude[0] * _config->FeedbackFactor;
			_analogOut->LastFeedbackAmplitude[1] = _analogOut->MaxFeedbackAmplitude[1] * _config->FeedbackFactor;
			_analogOut->MaxFeedbackAmplitude[0] = 0;
			_analogOut->MaxFeedbackAmplitude[1] = 0;
		}
	}
	_digitalOut->PrevHighAngle = highAngle;
	_digitalOut->Trigger = trig;

	_analogOut->Phase = _analogOut->Angles[2] + _config->PhaseOffset;
	if(_analogOut->Phase >= 360.0f)
	{
		_analogOut->Phase -= 360.0f;
	}
	if(_analogOut->Phase < 0.0f)
	{
		_analogOut->Phase += 360.0f;
	}
}

void MotorControl::MeasureBus()
{
	float busVoltage = BspAnalog::GetFastSingleSample(&_analogChannels[ANA_V_BUS]);
	_analogIn->BusVoltage = busVoltage;
	_analogIn->BusCurrent = BspAnalog::GetFastSingleSample(&_analogChannels[ANA_I_IN]);
}

void MotorControl::ComputeVectorCurrents()
{
	_analogOut->RealCurrent = (_analogOut->Point[0] * _analogIn->Current[0] +
							   _analogOut->Point[2] * _analogIn->Current[1] +
							   _analogOut->Point[1] * _analogIn->Current[2]) * (1.0f / 1.73205f);
	_analogOut->ReactiveCurrent = (_analogOut->Point[3] * _analogIn->Current[0] +
								   _analogOut->Point[5] * _analogIn->Current[1] +
								   _analogOut->Point[4] * _analogIn->Current[2]) * (1.0f / 1.73295f);
}

void MotorControl::ComputeOutputSines()
{
	// Establish Direct Axis points
	SineTable::Sine_3Phase(_analogOut->Phase, _analogOut->Point);

	// Establish Quadrature Axis Points
	// Note:
	// * Phase A = Point[0]
	// * Phase B = Point[2] = A + 240 (-120)
	// * Phase C = Point[1] = A + 120 (-240)
	// iaq lies in phase with VBC
	_analogOut->Point[3] = (_analogOut->Point[2] - _analogOut->Point[1]) * (1.0f / 1.73206f);
	// ibq lies in phase with VCA
	_analogOut->Point[4] = (_analogOut->Point[1] - _analogOut->Point[0]) * (1.0f / 1.73206f);
	// icq lies in phase with VAB
	_analogOut->Point[5] = (_analogOut->Point[0] - _analogOut->Point[1]) * (1.0f / 1.73206f);
}

void MotorControl::SpeedGovernor()
{
	_analogOut->Samples++;
	if(_digitalOut->Trigger)
	{
		_analogOut->Frequency = (_analogOut->Phase - _analogOut->OldPhase + 360.0f) / (360.0f * _config->DeltaT * (float)_analogOut->Samples);
		_analogOut->OldPhase = _analogOut->Phase;
		_analogOut->Samples = 0;
		_analogOut->MotorSpeed = (_analogOut->Frequency * _config->FrequencyToSpeedFactor);
		float error = _config->Speed_Target - _analogOut->MotorSpeed;
		_analogOut->Speed.Pterm = _config->Speed.PGain * error;
		_analogOut->Speed.Iterm = _config->Speed.IGain * error;
		float d_error = error - _analogOut->Speed.Error;
		_analogOut->Speed.Dterm = _config->Speed.DGain * d_error;
		_analogOut->Speed.TDterm = _config->Speed.TDGain * d_error;
		_analogOut->Speed.Error = error;
		float integrator = _analogOut->Speed.Integrator + _analogOut->Speed.Iterm + _analogOut->Speed.TDterm;
		// Limit Integrator
		if(integrator > _config->Speed.MaxIntegrator)
		{
			integrator = _config->Speed.MaxIntegrator;
		}
		else if(integrator < _config->Speed.MinIntegrator)
		{
			integrator = _config->Speed.MinIntegrator;
		}
		_analogOut->Speed.Integrator = integrator;
		float controlOutput = _analogOut->Speed.Pterm + _analogOut->Speed.Integrator + _analogOut->Speed.Dterm;
		// Limit Control Output
		if(controlOutput > _config->Speed.MaxOutput)
		{
			controlOutput = _config->Speed.MaxOutput;
		}
		else if(controlOutput < _config->Speed.MinOutput)
		{
			controlOutput = _config->Speed.MinOutput;
		}
		_analogOut->Speed.ControlOutput = controlOutput;
	}
}

void MotorControl::SimpleVector()
{
	_analogOut->MotorBackEmf = fabsf(_analogOut->Frequency) * _config->MotorVoltsPerHz[1];

	// <KLUDGE> Does not allow for field weakening
	// Direct Axis Current
	_analogOut->CurrentTargets[0] = _config->Reactive_Target;
	// Quadrature Axis Current
	_analogOut->CurrentTargets[1] = _analogOut->Speed.ControlOutput;

	// Direct Axis
	float error =_analogOut->CurrentTargets[0] - _analogOut->ReactiveCurrent;
	_analogOut->Reactive.Pterm = _config->Reactive.PGain * error;
	_analogOut->Reactive.Iterm = _config->Reactive.IGain * error;
	float d_error = error - _analogOut->Reactive.Error;
	_analogOut->Reactive.Dterm = _config->Reactive.DGain * d_error;
	_analogOut->Reactive.TDterm = _config->Reactive.TDGain * d_error;
	_analogOut->Reactive.Error = error;
	float integrator = _analogOut->Reactive.Integrator + _analogOut->Reactive.Iterm + _analogOut->Reactive.TDterm;
	// Limit Integrator
	if(integrator > _config->Reactive.MaxIntegrator)
	{
		integrator = _config->Reactive.MaxIntegrator;
	}
	else if(integrator < _config->Reactive.MinIntegrator)
	{
		integrator = _config->Reactive.MinIntegrator;
	}
	_analogOut->Reactive.Integrator = integrator;
	float controlOutput = _analogOut->Reactive.Pterm + _analogOut->Reactive.Integrator + _analogOut->Reactive.Dterm;
	// Limit Control Output
	if(controlOutput > _config->Reactive.MaxOutput)
	{
		controlOutput = _config->Reactive.MaxOutput;
	}
	else if(controlOutput < _config->Reactive.MinOutput)
	{
		controlOutput = _config->Reactive.MinOutput;
	}
	_analogOut->Reactive.ControlOutput = controlOutput;

	// Quadrature Axis
	error =_analogOut->CurrentTargets[1] - _analogOut->RealCurrent;
	_analogOut->Real.Pterm = _config->Real.PGain * error;
	_analogOut->Real.Iterm = _config->Real.IGain * error;
	d_error = error - _analogOut->Real.Error;
	_analogOut->Real.Dterm = _config->Real.DGain * d_error;
	_analogOut->Real.TDterm = _config->Real.TDGain * d_error;
	_analogOut->Real.Error = error;
	integrator = _analogOut->Real.Integrator + _analogOut->Real.Iterm + _analogOut->Real.TDterm;
	// Limit Integrator
	if(integrator > _config->Real.MaxIntegrator)
	{
		integrator = _config->Real.MaxIntegrator;
	}
	else if(integrator < _config->Real.MinIntegrator)
	{
		integrator = _config->Real.MinIntegrator;
	}
	_analogOut->Real.Integrator = integrator;
	controlOutput = _analogOut->Real.Pterm + _analogOut->Real.Integrator + _analogOut->Real.Dterm;
	// Limit Control Output
	if(controlOutput > _config->Real.MaxOutput)
	{
		controlOutput = _config->Real.MaxOutput;
	}
	else if(controlOutput < _config->Real.MinOutput)
	{
		controlOutput = _config->Real.MinOutput;
	}
	_analogOut->Real.ControlOutput = controlOutput;


	_analogOut->AppliedVoltages[0] = controlOutput;
	_analogOut->AppliedVoltages[1] = controlOutput;

	// Calculate the necessary voltages
	// Direct Axis Amplitude
	_analogOut->AppliedVoltages[0] = _config->Resistance * _analogOut->CurrentTargets[0] - _analogOut->Frequency * _config->InductorCoefficient * _analogOut->CurrentTargets[1] + _config->StoppedVoltage[1];
	// Quadrature Axis Amplitude
	_analogOut->AppliedVoltages[1] = _config->Resistance * _analogOut->CurrentTargets[1] + _analogOut->Frequency * _config->InductorCoefficient * _analogOut->CurrentTargets[0] + _config->StoppedVoltage[1] + _analogOut->MotorBackEmf;

	_analogOut->Voltage[0] = _analogOut->Point[0] * _analogOut->AppliedVoltages[0] + _analogOut->Point[3] * _analogOut->AppliedVoltages[1];
	_analogOut->Voltage[1] = _analogOut->Point[2] * _analogOut->AppliedVoltages[0] + _analogOut->Point[4] * _analogOut->AppliedVoltages[1];
	_analogOut->Voltage[2] = _analogOut->Point[1] * _analogOut->AppliedVoltages[0] + _analogOut->Point[5] * _analogOut->AppliedVoltages[1];
}

void MotorControl::SetDutyCycles()
{
	float busVoltage = _analogIn->BusVoltage;
	if(busVoltage < 0.2f)
	{
		busVoltage = 0.2f;
	}

	float amplitude =  _analogOut->Voltage[0] / busVoltage;
	if(amplitude > 1.0f)
	{
		amplitude = 1.0f;
	}
	else if (amplitude < -1.0f)
	{
		amplitude = -1.0f;
	}
	unsigned short period = (amplitude * _periodFactor) + _halfPeriod;
	_analogOut->PWM[0] = period;
	BspPwm::SetSwitchDutyCycle(0, period);
	amplitude =  _analogOut->Voltage[1] / busVoltage;
	if(amplitude > 1.0f)
	{
		amplitude = 1.0f;
	}
	else if (amplitude < -1.0f)
	{
		amplitude = -1.0f;
	}
	period = (amplitude * _periodFactor) + _halfPeriod;
	_analogOut->PWM[1] = period;
	BspPwm::SetSwitchDutyCycle(1, period);
	amplitude =  _analogOut->Voltage[2] / busVoltage;
	if(amplitude > 1.0f)
	{
		amplitude = 1.0f;
	}
	else if (amplitude < -1.0f)
	{
		amplitude = -1.0f;
	}
	period = (amplitude * _periodFactor) + _halfPeriod;
	_analogOut->PWM[2] = period;
	BspPwm::SetSwitchDutyCycle(2, period);
}

float MotorControl::GetResolverAngle()
{
	float cosAngle = _analogOut->Angles[1];
	float sineAngle = _analogOut->Angles[0];
	float angle = cosAngle * 2.0f;
	if(angle < 90.0f)
	{
		angle = (180.0f - sineAngle)  * 2.0f + _config->CosinePhaseOffset;
	}
	else if(angle >= 270.0f)
	{
		angle = sineAngle * 2.0f + _config->CosinePhaseOffset;
	}
	else
	{
		if(sineAngle >= 0.0f)
		{
			angle = (180.0f - cosAngle) * 2.0f;
		}
	}
	if(angle >= 360.0f)
	{
		angle -= 360.0f;
	}
	else if(angle < 0.0f)
	{
		angle += 360.0f;
	}
	return angle;
}

bool MotorControl::OkToSave()
{
	return ((_analogIn->BusVoltage < 10.0f) && (_analogOut->Frequency < 1));
}
