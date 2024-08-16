// Motor.h
// Header file for simplified Board support Motor operating logic
// Includes templates for motor programs and inlined functions

#ifndef DATAMAN_H
#define DATAMAN_H

#include "BspFlash.h"
#include "BspAnalog.h"
#include "TempSensor.h"
#include "VectorControl.h"
#include "Motor.h"
#include "Loading.h"
#include "Fccp.h"

#ifdef __cplusplus
class DataMan
{
	enum Modules
	{
		Analog,
		Temp,
		Vector,
		Motor,
		Loading,
		NUM_MODULES
	};
	struct AnalogConfigMan
	{
		BspAnalog::AnalogConfig Analog;
		TempSensor::TempSensorConfig Temp;
		VectorControl::VectorConfig Vector;
		MotorControl::MotorConfig Motor;
		ProcLoading::LoadingConfig Loading;
		long BookEnd;
	};
	struct DigitalConfigMan
	{
		BspAnalog::AnalogDigitalConfig Analog;
		bool Temp;
		VectorControl::VectorDigitalConfig Vector;
		MotorControl::MotorDigitalConfig Motor;
		ProcLoading::LoadingDigitalConfig Loading;
		bool BookEnd;
	};
	struct ConfigMan
	{
		AnalogConfigMan *Analog;
		DigitalConfigMan *Digital;
	};
	struct AnalogInputMan
	{
		BspAnalog::AnalogInputs Analog;
		TempSensor::TempSensorInputs Temp;
		VectorControl::VectorInputs Vector;
		MotorControl::MotorInputs Motor;
		ProcLoading::LoadingInputs Loading;
		long BookEnd;
	};
	struct DigitalInputMan
	{
		BspAnalog::AnalogDigitalInputs Analog;
		bool Temp;
		VectorControl::VectorDigitalInputs Vector;
		MotorControl::MotorDigitalInputs Motor;
		ProcLoading::LoadingDigitalInputs Loading;
		bool BookEnd;
	};
	struct AnalogOutputMan
	{
		BspAnalog::AnalogOutputs Analog;
		TempSensor::TempSensorOutputs Temp;
		VectorControl::VectorOutputs Vector;
		MotorControl::MotorOutputs Motor;
		ProcLoading::LoadingOutputs Loading;
		long BookEnd;
	};
	struct DigitalOutputMan
	{
		BspAnalog::AnalogDigitalOutputs Analog;
		bool Temp;
		VectorControl::VectorDigitalOutputs Vector;
		MotorControl::MotorDigitalOutputs Motor;
		ProcLoading::LoadingDigitalOutputs Loading;
		bool BookEnd;
	};
	struct VariableMan
	{
		AnalogInputMan AnalogIn;
		DigitalInputMan DigitalIn;
		AnalogOutputMan AnalogOut;
		DigitalOutputMan DigitalOut;
	};
	//<KLUDGE> These should be private
	public:  static ConfigMan _config;
	public:  static VariableMan _variables;

	private: static unsigned long _relativeVariableLookup[NUM_MODULES][4];
	private: static unsigned long _relativeConfigLookup[NUM_MODULES][2];

	private: static char _rxHndl;
	private: static char _txHndl;
	private: static Fccp::CanData _receiveData;
	private: static unsigned long _txData[2];
	private: static unsigned char _canMessage;
	private: static long _defaultPacketCounter;
	private: static unsigned long _dummyData[2];
	private: static unsigned long _dataLength;
	private: static unsigned long _configLength[2];

	public:  static void Initialize();
	public:  static void Logic();
	public:  static void *GetConfigAddress(unsigned long address, bool relative, unsigned char module, unsigned char type);
	public:  static void *GetVariableAddress(unsigned long address, unsigned char module, unsigned char type);
	public:  static unsigned char WriteData(unsigned long address, unsigned char dataType, bool nvm, bool relative, unsigned long data);
	public:  static unsigned long GetData(unsigned long address, unsigned char dataType, bool nvm, bool relative);
	public:  static unsigned long *GetAddress(unsigned long address, unsigned char dataType, bool nvm, bool relative);
	public:  static void SendDefaultCanPackets();
	public:  static void SaveToNonVolatile() {if(MotorControl::OkToSave()){BspFlash::Write();}}
};
#endif

#endif // DATAMAN_H

