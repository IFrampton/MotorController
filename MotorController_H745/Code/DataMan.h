// Motor.h
// Header file for simplified Board support Motor operating logic
// Includes templates for motor programs and inlined functions

#ifndef DATAMAN_H
#define DATAMAN_H

#include "BspAnalog.h"
#include "BspFlash.h"
#include "Motor.h"
#include "Loading.h"
#include "Fccp.h"

#ifdef __cplusplus
class DataMan
{
	enum Modules
	{
		Analog,
		Motor,
		Loading,
		NUM_MODULES
	};
	struct AnalogConfigMan
	{
		BspAnalog::AnalogConfig Analog;
		MotorControl::MotorConfig Motor;
		ProcLoading::LoadingConfig Loading;
	};
	struct DigitalConfigMan
	{
		BspAnalog::AnalogDigitalConfig Analog;
		MotorControl::MotorDigitalConfig Motor;
		ProcLoading::LoadingDigitalConfig Loading;
	};
	struct ConfigMan
	{
		AnalogConfigMan *Analog;
		DigitalConfigMan *Digital;
	};
	struct AnalogInputMan
	{
		BspAnalog::AnalogInputs Analog;
		MotorControl::MotorInputs Motor;
		ProcLoading::LoadingInputs Loading;
	};
	struct DigitalInputMan
	{
		BspAnalog::AnalogDigitalInputs Analog;
		MotorControl::MotorDigitalInputs Motor;
		ProcLoading::LoadingDigitalInputs Loading;
	};
	struct AnalogOutputMan
	{
		BspAnalog::AnalogOutputs Analog;
		MotorControl::MotorOutputs Motor;
		ProcLoading::LoadingOutputs Loading;
	};
	struct DigitalOutputMan
	{
		BspAnalog::AnalogDigitalOutputs Analog;
		MotorControl::MotorDigitalOutputs Motor;
		ProcLoading::LoadingDigitalOutputs Loading;
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

