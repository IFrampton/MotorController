// BspAnalog.h
// Header file for simplified Board support Analog features.
// Includes templates for Analog functions and inlined functions

#ifndef BSPANALOG_H
#define BSPANALOG_H

#include "stm32h7xx.h"
#include "BspSpi.h"

#ifdef __cplusplus
class BspAnalog
{
	public: static const long SamplesToAverage = 1;
	public: static const long ExternalSamplesToAverage = 10;

	public: struct AnalogConfig
	{
		long Offset[3][20];
		float ScaleFactor[3][20];
		long ExternalOffset[3];
		float ExternalScaleFactor[3];
	};
	public: struct AnalogDigitalConfig
	{
		bool Spare;
	};
	public: struct AnalogInputs
	{
		short RawData[32];
	};
	public: struct AnalogDigitalInputs
	{
		bool Spare;
	};
	public: struct AnalogOutputs
	{
		float ScaledData[32];
	};
	public: struct AnalogDigitalOutputs
	{
		bool Spare;
	};
	private: static AnalogConfig *_config;
	//private: static AnalogDigitalConfig *_digitalConfig;
	private: static AnalogInputs *_analogIn;
	//private: static AnalogDigitalInputs *_digitalIn;
	private: static AnalogOutputs *_analogOut;
	//private: static AnalogDigitalOutputs *_digitalOut;
	public: struct AnalogType
	{
			unsigned long *BaseLocation;
			long *Offset;
			float *ScaleFactor;
	};
	public: struct ExternalAnalogType
	{
			volatile unsigned short *BaseLocation;
			volatile unsigned char *DataReady;
			unsigned short *ReadComplete;
			long *Offset;
			float *ScaleFactor;
	};
	private: static long _analogDataBuffer[3][20];
	private: static bool _initialized;
	private: static bool _dataLinked;
	private: static unsigned char _nextChannel[3];
	private: static unsigned char _dmaRxChannel[3];
	private: static unsigned char _dmaTxChannel;
	public:  static void InitializeAdc(void);
	public:  static unsigned char SetupChannel(char converter, char channel, AnalogType *channelData);
	public:  static _inline_ void StartConversion(void) {ADC1->CR |= (1 << 2); ADC2->CR |= (1 << 2);}
	public:  static _inline_ void UpdateRawValues()
	{
		_analogIn->RawData[0] = _analogDataBuffer[0][0];
		_analogIn->RawData[1] = _analogDataBuffer[0][1];
		_analogIn->RawData[2] = _analogDataBuffer[0][2];
		_analogIn->RawData[3] = _analogDataBuffer[0][3];
		_analogIn->RawData[4] = _analogDataBuffer[0][4];
		_analogIn->RawData[5] = _analogDataBuffer[1][0];
		_analogIn->RawData[6] = _analogDataBuffer[1][1];
		_analogIn->RawData[7] = _analogDataBuffer[1][2];
		_analogIn->RawData[8] = _analogDataBuffer[1][3];
	}

	//private: static volatile unsigned short *_spiData[3];
	//private: static volatile unsigned char *_spiDataReady[3];
	//private: static unsigned short *_spiReadComplete[3];
	public:  static long DummyVariable;
	private: static bool _externalInitialized;
	public:  static void InitializeExternal(void);
	public:  static unsigned char SetupExternalChannel(char channel, ExternalAnalogType *channelData);

	public:  static void InitializeDac(void);
	public:  static _inline_ float GetFastSingleSample(AnalogType *channelData)
	{
		long value = *channelData->BaseLocation;
		value -= *channelData->Offset;
		return (float)value * *channelData->ScaleFactor;
	}
	public:  static _inline_ float GetFastExternalSample(ExternalAnalogType *channelData)
	{
		volatile unsigned short *readLoc = channelData->BaseLocation;
		long value = 0;
		long count = 0;
		while(BspSpi::IsDataAvailable(channelData->DataReady))
		{
			long temp = *readLoc;
			value += (temp & 0xFFFF);
			value += (temp >> 16);
			count++;
		}
		value -= *channelData->Offset * count;
		BspSpi::SetReadComplete(channelData->ReadComplete);
		return (float)value * *channelData->ScaleFactor / (float)count;
	}

	public:  static void LinkData(AnalogConfig *config, AnalogInputs *analogIn, AnalogOutputs *analogOut )
	{
		_config = config;
		_analogIn = analogIn;
		_analogOut = analogOut;
		_dataLinked = true;
	}
};
#endif

#endif //BSPANALOG_H
