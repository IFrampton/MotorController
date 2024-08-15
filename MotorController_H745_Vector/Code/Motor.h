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
	public: struct ControllerSettings
	{
		float PGain;
		float IGain;
		float DGain;
		float TDGain;
		float MaxIntegrator;
		float MinIntegrator;
		float MaxOutput;
		float MinOutput;
	};
	public: struct ControllerOutputs
	{
		float Pterm;
		float Iterm;
		float Dterm;
		float TDterm;
		float Error;
		float Integrator;
		float ControlOutput;
	};
	public: struct MotorConfig
	{
		float MotorVoltsPerHz[2];
		float FrequencyRampRate[2];
		float StoppedVoltage[2];
		float FrequencyTarget;
		float ClosedLoopFrequency;
		float CurrentFault;
		float Speed_Target;
		ControllerSettings Speed;
		float Reactive_Target;
		ControllerSettings Reactive;
		ControllerSettings Real;
		float DefaultMaxFeedbackAmplitude;
		float FeedbackFactor;
		float PhaseOffset;
		float CosinePhaseOffset;
		float DeltaT;
		float FrequencyToSpeedFactor;
		float FilterCoefficient;
		float Resistance;
		float InductorCoefficient;
		long Speedtimeout;
		long Mode;
	};
	public: struct MotorDigitalConfig
	{
		bool Reset;
		bool UpdateMinMax;
	};
	public: struct MotorInputs
	{
		float Current[3];
		float Feedback[2];
		float BusVoltage;
		float BusCurrent;
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
		float Point[6];
		float Voltage[3];
		float MotorSpeed;
		ControllerOutputs Speed;
		float ReactiveCurrent;
		ControllerOutputs Reactive;
		float RealCurrent;
		ControllerOutputs Real;
		float Angles[3];
		float MaxFeedbackAmplitude[2];
		float LastFeedbackAmplitude[2];
		float OldPhase;
		float FilteredSine;
		float MotorBackEmf;
		float CurrentTargets[2];
		float AppliedVoltages[2];
		long PWM[3];
		long TimeoutCounter;
		long Samples;
	};
	public: struct MotorDigitalOutputs
	{
		bool Faulted;
		bool PrevReset;
		bool PrevHighAngle;
		bool Trigger;
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
	private: static float _analogData[10];
	public:  static void Initialize(void);
	public:  static void Logic(void);

	private: static void MeasureCurrent();
	private: static void CalculatePosition();
	private: static void MeasureBus();
	private: static void ComputeVectorCurrents();
	private: static void ComputeOutputSines();
	private: static void SpeedGovernor();
	private: static void SimpleVector();
	private: static void SetDutyCycles();

	public:  static float GetResolverAngle();

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

