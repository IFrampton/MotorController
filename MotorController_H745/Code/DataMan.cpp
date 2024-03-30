#include "DataMan.h"

#define KLUDGED_CONFIGURATION
#define EXPECT_REAL_DATA

DataMan::ConfigMan DataMan::_config;
DataMan::VariableMan DataMan::_variables;

void DataMan::Initialize()
{
	BspAnalog::LinkData(&_config.Analog.Analog, &_variables.AnalogIn.Analog, &_variables.AnalogOut.Analog);
	MotorControl::LinkData(&_config.Analog.Motor, &_variables.AnalogIn.Motor, &_variables.AnalogOut.Motor);
	ProcLoading::LinkData(&_config.Analog.Loading, &_variables.AnalogIn.Loading, &_variables.AnalogOut.Loading);
#ifdef KLUDGED_CONFIGURATION
	//<KLUDGE> Setup parameters until an interface is operational.
	_config.Analog.Analog.Offset[0][7] = 30;
	_config.Analog.Analog.ScaleFactor[0][7] = 30.2f / 1978.0f;//1000.0f/(1.5f * 32768.0f);
#ifdef EXPECT_REAL_DATA
	_config.Analog.Analog.ExternalOffset[0] = 25640;
	_config.Analog.Analog.ExternalScaleFactor[0] = 100.0f/(1.024f * 20156.0f);//600.0f/(1.024f * 20156.0f);
	_config.Analog.Analog.ExternalOffset[1] = 25640;
	_config.Analog.Analog.ExternalScaleFactor[1] = 100.0f/(1.024f * 20156.0f);//600.0f/(1.024f * 20156.0f);
	_config.Analog.Analog.ExternalOffset[2] = 25640;
	_config.Analog.Analog.ExternalScaleFactor[2] = 100.0f/(1.024f * 20156.0f);//600.0f/(1.024f * 20156.0f);
#else
	_config.Analog.Analog.ExternalOffset[0] = 0;
	_config.Analog.Analog.ExternalScaleFactor[0] = 1.0f;
	_config.Analog.Analog.ExternalOffset[1] = 0;
	_config.Analog.Analog.ExternalScaleFactor[1] = 1.0f;
	_config.Analog.Analog.ExternalOffset[2] = 0;
	_config.Analog.Analog.ExternalScaleFactor[2] = 1.0f;
#endif
	_config.Analog.Motor.MotorVoltsPerHz = 19.0f;
	_config.Analog.Motor.FrequencyRampRate = 1.0f;
	_config.Analog.Motor.FrequencyTarget = 10.0f;
	_config.Analog.Motor.Offset = 0.002f;
	_config.Analog.Loading.CountsPerSecond = 200000000;
	_config.Analog.Loading.IsrOverhead = 5;
	_config.Analog.Loading.MaximumIdleTaskCounts = 1182000;
#endif
}

// Handles
void DataMan::Logic()
{

}

void *DataMan::GetConfigAddress(unsigned long address, bool relative, unsigned char module, unsigned char type)
{
	return (void *)&_config;
}

void *DataMan::GetVariableAddress(unsigned long address, bool relative, unsigned char module, unsigned char type)
{
	return (void *)&_variables;
}
