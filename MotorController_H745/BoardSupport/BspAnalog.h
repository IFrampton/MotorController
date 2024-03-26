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
		long Offset[3][19];
		float ScaleFactor[3][19];
		long ExternalOffset[3];
		float ExternalScaleFactor[3];
	};
	private: static AnalogConfig *_configuration;
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
	private: static long AnalogDataBuffer[3][19];
	private: static bool _initialized;
	private: static unsigned char _nextChannel[3];
	public:  static void InitializeAdc(void);
	public:  static unsigned char SetupChannel(char converter, char channel, AnalogType *channelData);

	//private: static volatile unsigned short *_spiData[3];
	//private: static volatile unsigned char *_spiDataReady[3];
	//private: static unsigned short *_spiReadComplete[3];
	public:  static long DummyVariable;
	private: static bool _externalInitialized;
	public:  static void InitializeExternal(void);
	public:  static unsigned char SetupExternalChannel(char channel, ExternalAnalogType *channelData);

	public:  static void InitializeDac(void);
	public:  static void InitializePointer(AnalogConfig *configuration) {_configuration = configuration;}
	public:  static inline float GetFastSingleSample(AnalogType *channelData)
	{
		long value = *channelData->BaseLocation;
		value -= *channelData->Offset;
		return (float)value * *channelData->ScaleFactor;
	}
	public:  static inline float GetFastExternalSample(ExternalAnalogType *channelData)
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
};
#endif

#endif //BSPANALOG_H
