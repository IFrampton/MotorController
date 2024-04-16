// Motor.h
// Header file for simplified Board support Motor operating logic
// Includes templates for motor programs and inlined functions

#ifndef MOTOR_H
#define MOTOR_H

#include "BspAnalog.h"

#ifdef __cplusplus
class MotorControl
{
	enum AnalogChannels
	{
		ANA_V_BUS,
		ANA_V_A,
		ANA_V_B,
		ANA_V_C,
		ANA_I_IN,
		ANA_T_1,
		ANA_T_2,
		ANA_RSLV_SIN,
		ANA_RSLV_COS,
		NUM_ANALOGS
	};
	enum ExternalChannels
	{
		ANA_I_A,
		ANA_I_B,
		ANA_I_C,
		NUM_EXTERNAL_ANALOGS
	};
	public: struct MotorConfig
	{
		float MotorVoltsPerHz[2];
		float FrequencyRampRate[2];
		float StoppedVoltage[2];
		float FrequencyTarget;
		float ClosedLoopFrequency;
		float ReactivePower_Target;
		float ReactivePower_PGain;
		float ReactivePower_IGain;
		float ReactivePower_DGain;
		float ReactivePower_TDGain;
		float ReactivePower_MaxIntegrator;
		float ReactivePower_MinIntegrator;
		float CurrentFault;
	};
	public: struct MotorDigitalConfig
	{
		bool Reset;
	};
	public: struct MotorInputs
	{
		float Current[3];
		float BusVoltage;
	};
	public: struct MotorDigitalInputs
	{
		bool Spare;
	};
	public: struct MotorOutputs
	{
		float Amplitude;
		float Frequency;
		float Phase;
		float Point[3];
		float Voltage[3];
		float RealCurrent;
		float ReactiveCurrent;
		float ReactivePower_Pterm;
		float ReactivePower_Iterm;
		float ReactivePower_Dterm;
		float ReactivePower_TDterm;
		float ReactivePower_Error;
		float ReactivePower_Integrator;
		float ReactivePower_Adjustment;
	};
	public: struct MotorDigitalOutputs
	{
		bool Faulted;
		bool PrevReset;
	};
	private: static BspAnalog::AnalogType _analogChannels[NUM_ANALOGS];
	private: static BspAnalog::ExternalAnalogType _externalChannels[NUM_EXTERNAL_ANALOGS];
	private: static MotorConfig *_config;
	private: static MotorDigitalConfig *_digitalConfig;
	private: static MotorInputs *_analogIn;
	private: static MotorOutputs *_analogOut;
	private: static MotorDigitalOutputs *_digitalOut;
	private: static bool _dataLinked;
	private: static float _deltatFactor;
	private: static float _deltaT;
	private: static float _periodFactor;
	private: static short _halfPeriod;
	private: static bool _loggingInput[32];
	private: static unsigned long _logInputIndex;
	public:  static void Initialize(void);
	public:  static void Logic(void);

	public:  static bool OkToSave();
	public:  static void LinkData(MotorConfig *config, MotorDigitalConfig *digitalConfig, MotorInputs *analogIn, MotorOutputs *analogOut, MotorDigitalOutputs *digitalOut )
	{
		_config = config;
		_digitalConfig = digitalConfig;
		_analogIn = analogIn;
		_analogOut = analogOut;
		_digitalOut = digitalOut;
		_dataLinked = true;
	}
};
#endif

#endif // MOTOR_H

