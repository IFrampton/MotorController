// Motor.h
// Header file for simplified Board support Motor operating logic
// Includes templates for motor programs and inlined functions

#ifndef MOTOR_H
#define MOTOR_H

#include "BspAnalog.h"

#ifdef __cplusplus
class Motor
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
	struct MotorConfig
	{
		float MotorVoltsPerHz;
		float FrequencyRampRate;
		float FrequencyTarget;
		float Offset;
	};
	struct MotorInputs
	{
		float Current[3];
		float BusVoltage;
	};
	struct MotorOutputs
	{
		float Amplitude;
		float Frequency;
		float Phase;
		float Point[3];
		float Voltage[3];
		float RealCurrent;
		float ReactiveCurrent;
	};
	private: static BspAnalog::AnalogType _analogChannels[NUM_ANALOGS];
	private: static BspAnalog::ExternalAnalogType _externalChannels[NUM_EXTERNAL_ANALOGS];
	private: static BspAnalog::AnalogConfig _analogConfig;
	//<KLUDGE> (Should be private)
	//private: static MotorConfig _motorConfig;
	//private: static MotorInputs _motorInputs;
	//private: static MotorOutputs _motorOutputs;
	public: static MotorConfig _motorConfig;
	public: static MotorInputs _motorInputs;
	public: static MotorOutputs _motorOutputs;
	private: static float _deltatFactor;
	private: static float _deltaT;
	private: static float _periodFactor;
	private: static short _halfPeriod;
	private: static bool _loggingInput[32];
	private: static unsigned long _logInputIndex;
	public:  static void Initialize(void);
	public:  static void Logic(void);
};
#endif

#endif // MOTOR_H

