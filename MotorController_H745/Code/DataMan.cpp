#include "DataMan.h"
#include "BspCan.h"

//#define KLUDGED_CONFIGURATION
#define EXPECT_REAL_DATA

DataMan::ConfigMan DataMan::_config;
DataMan::VariableMan DataMan::_variables;
char DataMan::_rxHndl = -2;
char DataMan::_txHndl = -2;
Fccp::CanData DataMan::_receiveData;
unsigned long DataMan::_txData[2] = {0,0};
unsigned char DataMan::_canMessage = 0;
long DataMan::_defaultPacketCounter = 0;


void DataMan::Initialize()
{
	// Point to Flash Storage Buffer
	_config.Analog = (AnalogConfigMan *)BspFlash::GetAnalogBufferLocation();
	_config.Digital = (DigitalConfigMan *)BspFlash::GetDigitalBufferLocation();

	BspAnalog::LinkData(&_config.Analog->Analog, &_variables.AnalogIn.Analog, &_variables.AnalogOut.Analog);
	MotorControl::LinkData(&_config.Analog->Motor, &_config.Digital->Motor, &_variables.AnalogIn.Motor, &_variables.AnalogOut.Motor, &_variables.DigitalOut.Motor);
	ProcLoading::LinkData(&_config.Analog->Loading, &_variables.AnalogIn.Loading, &_variables.AnalogOut.Loading);
#ifdef KLUDGED_CONFIGURATION
	//<KLUDGE> Setup parameters until an interface is operational.
	_config.Analog->Analog.Offset[0][7] = 30;
	_config.Analog->Analog.ScaleFactor[0][7] = 30.2f / 1978.0f;//1000.0f/(1.5f * 32768.0f);
	// Full scale is 49151 counts.
	_config.Analog->Analog.ExternalOffset[0] = 25640;
	_config.Analog->Analog.ExternalScaleFactor[0] = 100.0f/(1.024f * 20156.0f);//600.0f/(1.024f * 20156.0f);
	_config.Analog->Analog.ExternalOffset[1] = 25640;
	_config.Analog->Analog.ExternalScaleFactor[1] = 100.0f/(1.024f * 20156.0f);//600.0f/(1.024f * 20156.0f);
	_config.Analog->Analog.ExternalOffset[2] = 25640;
	_config.Analog->Analog.ExternalScaleFactor[2] = 100.0f/(1.024f * 20156.0f);//600.0f/(1.024f * 20156.0f);
	_config.Analog->Motor.MotorVoltsPerHz = 19.0f;
	_config.Analog->Motor.FrequencyRampRate = 1.0f;
	_config.Analog->Motor.FrequencyTarget = 0.5f;//10.0f;
	_config.Analog->Motor.StoppedVoltage = 0.002f;
#endif
	_config.Analog->Loading.CountsPerSecond = 200000000;
	_config.Analog->Loading.IsrOverhead = 5;
	_config.Analog->Loading.MaximumIdleTaskCounts = 1182000;
//#ifdef KLUDGED_CONFIGURATION
	_config.Digital->Loading.SendDefaultPackets = false;
	_config.Analog->Loading.DefaultPacketRate = 6;
//#endif
	Fccp::Initialize();
	_rxHndl = BspCan::Subscribe(0x7E1, false);
	_txHndl = BspCan::GetTxHandle();
	BspTimer::Setup(333333, Logic, 11, false);
}

// Handles
void DataMan::Logic()
{
	ProcLoading::BeginTask(ProcLoading::DataMan_Task);
	Fccp::Logic();
	if(_config.Digital->Loading.SendDefaultPackets)
	{
		if(++_defaultPacketCounter >= _config.Analog->Loading.DefaultPacketRate)
		{
			_defaultPacketCounter = 0;
			SendDefaultCanPackets();
		}
	}
	ProcLoading::EndTask(ProcLoading::DataMan_Task);
}

unsigned long DataMan::_relativeVariableLookup[NUM_MODULES][4] =
{
	{(unsigned long)&_variables.AnalogIn.Analog - (unsigned long)&_variables, (unsigned long)&_variables.DigitalIn.Analog - (unsigned long)&_variables, (unsigned long)&_variables.AnalogOut.Analog - (unsigned long)&_variables, (unsigned long)&_variables.DigitalOut.Analog - (unsigned long)&_variables},
	{(unsigned long)&_variables.AnalogIn.Motor - (unsigned long)&_variables, (unsigned long)&_variables.DigitalIn.Motor - (unsigned long)&_variables, (unsigned long)&_variables.AnalogOut.Motor - (unsigned long)&_variables, (unsigned long)&_variables.DigitalOut.Motor - (unsigned long)&_variables},
	{(unsigned long)&_variables.AnalogIn.Loading - (unsigned long)&_variables, (unsigned long)&_variables.DigitalIn.Loading - (unsigned long)&_variables, (unsigned long)&_variables.AnalogOut.Loading - (unsigned long)&_variables, (unsigned long)&_variables.DigitalOut.Loading - (unsigned long)&_variables}
};

unsigned long DataMan::_relativeConfigLookup[NUM_MODULES][2] =
{
	{(unsigned long)&_config.Analog->Analog - (unsigned long)_config.Analog, (unsigned long)&_config.Digital->Analog - (unsigned long)_config.Digital},
	{(unsigned long)&_config.Analog->Motor - (unsigned long)_config.Analog, (unsigned long)&_config.Digital->Motor - (unsigned long)_config.Digital},
	{(unsigned long)&_config.Analog->Loading - (unsigned long)_config.Analog, (unsigned long)&_config.Digital->Loading - (unsigned long)_config.Digital}
};

void *DataMan::GetConfigAddress(unsigned long address, bool relative, unsigned char module, unsigned char type)
{
	// NOTE: There is no protection on the address; it can be as big as desired (which can cause a read past the end of memory)
	// prevent overflow
	if(module >= NUM_MODULES)
	{
		module = NUM_MODULES;
	}
	if(relative)
	{
		if(type == 0)
		{
			// Return entire 32-bit word
			unsigned long baseLocation = (unsigned long)_config.Digital;
			return (void *)((baseLocation + _relativeConfigLookup[module][1] + address) & 0xFFFFFFFC);
		}
		unsigned long baseLocation = (unsigned long)_config.Analog;
		return (void *)((baseLocation + _relativeConfigLookup[module][0] + address) & 0xFFFFFFFC);
	}
	if(type == 0)
	{
		// Return entire 32-bit word
		unsigned long baseLocation = (unsigned long)_config.Digital;
		return (void *)((baseLocation + address) & 0xFFFFFFFC);
	}
	unsigned long baseLocation = (unsigned long)_config.Analog;
	return (void *)((baseLocation + address) & 0xFFFFFFFC);
}

void *DataMan::GetVariableAddress(unsigned long address, unsigned char module, unsigned char type)
{
	// NOTE: There is no protection on the address; it can be as big as desired (which can cause a read past the end of memory)
	// prevent overflow
	if(module >= NUM_MODULES)
	{
		module = NUM_MODULES;
	}
	// prevent overflow
	type &= 0x3;
	unsigned long baseLocation = (unsigned long)&_variables;
	unsigned long offset = _relativeVariableLookup[module][type];
	return (void *)((baseLocation + offset + address) & 0xFFFFFFFC);
}

unsigned char DataMan::WriteData(unsigned long address, unsigned char dataType, bool nvm, bool relative, unsigned long data)
{
	switch(dataType)
	{
		case Fccp::DataType_Bool:
		case Fccp::DataType_Int8:
		{
			if(relative)
			{
				unsigned short addr = address & 0xFFFF;
				address >>= 16;
				unsigned char type = address & 0xFF;
				unsigned char module = address >> 8;
				if(nvm)
				{
					register char offset = addr & 0x3;
					register unsigned long location = (unsigned long)GetConfigAddress(addr, 1, module, dataType);
					*(unsigned char *)(location + offset) = (char)data;
					break;
				}
				else
				{
					register char offset = addr & 0x3;
					register unsigned long location = (unsigned long)GetVariableAddress(addr, module, type);
					*(unsigned char *)(location + offset) = (char)data;
				}
			}
			else
			{
				if(nvm)
				{
					register char offset = address & 0x3;
					register unsigned long location = (unsigned long)GetConfigAddress(address, 0, 0, dataType);
					*(unsigned char *)(location + offset) = (char)data;
				}
				else
				{
					register char offset = address & 0x3;
					*(unsigned char *)(address + offset) = (char)data;
				}
			}
			break;
		}
		case Fccp::DataType_Int16:
		{
			if(relative)
			{
				unsigned short addr = address & 0xFFFF;
				address >>= 16;
				unsigned char type = address & 0xFF;
				unsigned char module = address >> 8;
				if(nvm)
				{
					register char offset = addr & 0x2;
					register unsigned long location = (unsigned long)GetConfigAddress(addr, 1, module, dataType);
					*(unsigned short *)(location + offset) = (short)data;
				}
				else
				{
					register char offset = addr & 0x2;
					register unsigned long location = (unsigned long)GetVariableAddress(addr, module, type);
					*(unsigned short *)(location + offset) = (short)data;
				}
			}
			else
			{
				if(nvm)
				{
					register char offset = address & 0x2;
					register unsigned long location = (unsigned long)GetConfigAddress(address, 0, 0, dataType);
					*(unsigned short *)(location + offset) = (short)data;
				}
				else
				{
					register char offset = address & 0x2;
					*(unsigned short *)(address + offset) = (short)data;
				}
			}
			break;
		}
		case Fccp::DataType_Int32:
		case Fccp::DataType_Float:
		default:
		{
			if(relative)
			{
				unsigned short addr = address & 0xFFFF;
				address >>= 16;
				unsigned char type = address & 0xFF;
				unsigned char module = address >> 8;
				if(nvm)
				{
					*(unsigned long *)GetConfigAddress(addr, 1, module, dataType) = data;
				}
				else
				{
					*(unsigned long *)GetVariableAddress(addr, module, type) = data;
				}
			}
			else
			{
				if(nvm)
				{
					*(unsigned long *)GetConfigAddress(address, 0, 0, dataType) = data;
				}
				else
				{
					*(unsigned long *)address = data;
				}
			}
			break;
		}
	}
	// Note: No error reporting for now
	return 0;
}

unsigned long DataMan::GetData(unsigned long address, unsigned char dataType, bool nvm, bool relative)
{
	if(relative)
	{
		unsigned short addr = address & 0xFFFF;
		address >>= 16;
		unsigned char type = address & 0xFF;
		unsigned char module = address >> 8;
		if(nvm)
		{
			return *(unsigned long *)GetConfigAddress(addr, 1, module, dataType);
		}
		else
		{
			return *(unsigned long *)GetVariableAddress(addr, module, type);
		}
	}
	else
	{
		if(nvm)
		{
			// Definition Data is handled separately (this is encoded into the firmware)
			if(dataType == Fccp::DataType_Definition)
			{
				return(BspFlash::GetDefinition(address));
			}
			return *(unsigned long *)GetConfigAddress(address, 0, 0, dataType);
		}
		else
		{
			return *(unsigned long *)address;
		}
	}
}

unsigned long *DataMan::GetAddress(unsigned long address, unsigned char dataType, bool nvm, bool relative)
{
	if(relative)
	{
		unsigned short addr = address & 0xFFFF;
		address >>= 16;
		unsigned char type = address & 0xFF;
		unsigned char module = address >> 8;
		if(nvm)
		{
			return (unsigned long *)GetConfigAddress(addr, 1, module, dataType);
		}
		else
		{
			return (unsigned long *)GetVariableAddress(addr, module, type);
		}
	}
	else
	{
		if(nvm)
		{
			return (unsigned long *)GetConfigAddress(address, 0, 0, dataType);
		}
		else
		{
			return (unsigned long *)address;
		}
	}
}

void DataMan::SendDefaultCanPackets()
{
	if(BspCan::CheckForNewData(_rxHndl))
	{
		BspCan::GetData(_rxHndl, &_receiveData.Identifier, &_receiveData.Length, _receiveData.Data, &_receiveData.Extended);
		// Note: The subscription to the channel already requires an ID match
		//if(((_receiveData.Identifier >> 18) == 0x7E1) && (_receiveData.Extended == false) && (_receiveData.Length == 8))
		if(_receiveData.Length == 8)
		{
			unsigned short data = _receiveData.Data[0] & 0xFFFF;
			if(data < 0xFFFF)
			{
				DataMan::_config.Analog->Motor.FrequencyTarget = (float)data * 0.1f;
			}
			data = _receiveData.Data[0] >> 16;
			if(data < 0xFFFF)
			{
				DataMan::_config.Analog->Motor.FrequencyRampRate[1] = (float)data * 0.01f;
			}
			data = _receiveData.Data[1] & 0xFFFF;
			if(data < 0xFFFF)
			{
				DataMan::_config.Analog->Motor.MotorVoltsPerHz[1] = (float)data * 0.001f;
			}
			data = _receiveData.Data[1] >> 16;
			if(data < 0xFFFF)
			{
				DataMan::_config.Analog->Motor.StoppedVoltage[1] = (float)data * 0.0001f;
			}
		}
		//else if()
		//{
		// Only one packet at this time
		//}
	}
	switch(_canMessage)
	{
		// Motor Voltages
		case 0:
		{
			unsigned short data = (unsigned short)(DataMan::_variables.AnalogIn.Motor.BusVoltage * 50.0f);
			_txData[1] = data;
			data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.Voltage[0] * 25.0f + 32767.0f);
			_txData[1] <<= 16;
			_txData[1] += data;
			data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.Voltage[1] * 25.0f + 32767.0f);
			_txData[0] = data;
			data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.Voltage[2] * 25.0f + 32767.0f);
			_txData[0] <<= 16;
			_txData[0] += data;
			BspCan::Transmit(_txHndl, 0x7F0, &_txData[0], 8, false);
			_canMessage++;
			break;
		}
		// Motor Currents
		case 1:
		{
			unsigned short data = 0xFFFF;
			_txData[1] = data;
			data = (unsigned short)(DataMan::_variables.AnalogIn.Motor.Current[0] * 50.0f + 32767.0f);
			_txData[1] <<= 16;
			_txData[1] += data;
			data = (unsigned short)(DataMan::_variables.AnalogIn.Motor.Current[1] * 50.0f + 32767.0f);
			_txData[0] = data;
			data = (unsigned short)(DataMan::_variables.AnalogIn.Motor.Current[2] * 50.0f + 32767.0f);
			_txData[0] <<= 16;
			_txData[0] += data;
			BspCan::Transmit(_txHndl, 0x7F1, &_txData[0], 8, false);
			_canMessage++;
			break;
		}
		// Other Information
		case 2:
		default:
		{
			unsigned short data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.Amplitude * 10000.0f + 32767.0f);
			_txData[1] = data;
			data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.Frequency * 10.0f);
			_txData[1] <<= 16;
			_txData[1] += data;
			data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.RealCurrent * 50.0f + 32767.0f);
			_txData[0] = data;
			data = (unsigned short)(DataMan::_variables.AnalogOut.Motor.ReactiveCurrent * 50.0f + 32767.0f);
			_txData[0] <<= 16;
			_txData[0] += data;
			BspCan::Transmit(_txHndl, 0x7F2, &_txData[0], 8, false);
			_canMessage = 0;
			break;
		}
	}
}
